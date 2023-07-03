#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>  
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <algorithm>

#include <WS2tcpip.h>  
#include <cassert>

#pragma comment(lib, "Ws2_32.lib")  

class Server
{
private:
	std::string ip;
	std::string host;
	SOCKET server;
	ADDRINFO hints{};
	ADDRINFO* addrResult = nullptr;

	std::map<SOCKET, char> users;

	std::vector<std::vector<char>> field;
	char currentPlayer;

	std::string msg;

	std::vector<std::thread> threads;
	static std::mutex mutex;
	static std::condition_variable conditionVariable;


public:
	Server(const std::string& ip, const std::string& host)
		:ip(ip),
		host(host),
		server(INVALID_SOCKET),
		users(),
		field({
			{' ', ' ', ' '},
			{' ', ' ', ' '},
			{' ', ' ', ' '}
			}),
		msg(),
		currentPlayer('X'),
		threads()
	{
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		Init();
	}

	~Server()
	{
		if (shutdown(server, SD_SEND) == SOCKET_ERROR)
		{
			std::cout << "shutdown failed:" << WSAGetLastError() << std::endl;
		}

		/*for (auto& elem : users)
		{
			shutdown(elem, SD_SEND);
			closesocket(elem);
		}*/

		closesocket(server);
	}

private:
	void Init()
	{
		std::cout << "Starting getaddrinfo ...";
		assert(!getaddrinfo(ip.c_str(), host.c_str(), &hints, &addrResult) && "\rgetaddrinfo() failed");
		std::cout << "\rStarting getaddrinfo: SUCCESS" << std::endl;

		std::cout << "Starting socket ...";
		assert(!((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) && "\rsocket() failed");
		std::cout << "\rStarting socket: SUCCESS" << std::endl;

		std::cout << "Starting bind ...";
		assert(!bind(server, addrResult->ai_addr, static_cast<int>(addrResult->ai_addrlen)) && "\rbind() failed");
		std::cout << "\rStarting bind: SUCCESS" << std::endl;

		freeaddrinfo(addrResult);

		std::cout << "Starting listen ...";
		assert(!(listen(server, SOMAXCONN)) && "\rlisten() failed");
		std::cout << "\rStarting listen: SUCCESS" << std::endl;

		while (true)
		{
			if (users.size() != 2)
			{
				SOCKET user;

				std::cout << "Starting accept ...";
				sockaddr_in addrin{};
				int size = sizeof(addrin);
				assert((user = accept(server, reinterpret_cast<sockaddr*>(&addrin), &size)) != INVALID_SOCKET && "\raccept() failed");
				std::cout << "\n\t\tIP:   " << inet_ntoa(addrin.sin_addr) << std::endl;
				std::cout << "\t\tPort: " << addrin.sin_port << std::endl;
				std::cout << "\rStarting accept: SUCCESS" << std::endl;

				
				if (users.empty())
				{
					users.emplace(user, 'X');
				}
				else
				{
					users.emplace(user, 'O');
				}

				if (send(user, std::string(1, users[user]).data(), 1, 0) == SOCKET_ERROR)  // Sending user who he is.
				{
					std::cout << "Send failed with code: " << WSAGetLastError() << std::endl;
					std::exit(-1);
				}
				
				if (users.size() == 2)
				{
					std::cout << "Number of user is 2" << std::endl;
					for (auto& item : users)
					{
						threads.push_back(std::thread{ Start, std::ref(users), item.first, std::ref(field), std::ref(currentPlayer) });
					}

					std::pair<bool, char> gameState = std::make_pair(true, 'n');

					while (gameState.first)
					{
						std::unique_lock<std::mutex> lock(mutex);
						gameState = IsGame(field);
						if (!gameState.first)
						{
							std::cout << "Somebode has won a game" << std::endl;
							auto sendWinner = [&](const std::string& msg)
							{
								for (auto& elem : users)
								{
									Send(elem.first, msg);
								}
							};

							currentPlayer = 'n'; // no-one
							if (gameState.second == 'd')  // draw.
							{
								sendWinner("Draw");
							}
							else
							{
								sendWinner(gameState.second + std::string(" Won"));
							}

						}
						conditionVariable.notify_all();
					}

					for (auto& item : threads)
					{
						item.join();
					}

					for (auto& item : users)
					{
						shutdown(item.first, SD_SEND);
						closesocket(item.first);
					}
					users.clear(); 
					threads.clear();
				}
			}
		}
	}

private:
	static void Start(std::map<SOCKET, char>& users, SOCKET user, std::vector<std::vector<char>>& field, char& currentPlayer)
	{
		auto parseStr = [](std::string str) -> std::tuple<int, int, char>
		{
			size_t index = 0;

			return std::tuple<int, int, char> {
				std::stoi(str.substr(0, index = str.find(' '))),			// cord x
				std::stoi(str.substr(index + 1, str.find(' ', index + 1))), // cord y
				str[str.size() - 1]											// type
			};
		};

		while(currentPlayer != 'n')
		{
			std::unique_lock<std::mutex> lock(mutex);
			conditionVariable.wait(lock);

			if (currentPlayer == 'n')
			{
				std::cout << "The thtead #" << std::this_thread::get_id() << " has ended." << std::endl;
				break;
			}

			if (users[user] == currentPlayer)
			{
				std::string resivedStr = Recive(user);
				Proccess(resivedStr);

				auto parsedStr = parseStr(resivedStr);

				if (field[std::get<1>(parsedStr)][std::get<0>(parsedStr)] == ' ')
				{
					field[std::get<1>(parsedStr)][std::get<0>(parsedStr)] = std::get<2>(parsedStr);
					currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
					Send(user, "1");

					[&user, &resivedStr, &users]() 
					{
						for (auto& elem : users)
						{
							if (elem.first == user)
							{
								continue;
							}

							Send(elem.first, resivedStr);
						}
					}();
				}
				else
				{
					Send(user, "0");
				}
			}
		}
	}
	
	// bool - returned value true if we can continue the game.
	// char - returned which palyer was won the game, when we continue the value will be 'n' - no-one won, 'd' - draw.
	static std::pair<bool, char> IsGame(const std::vector<std::vector<char>>& field)
	{
		if (field[0][0] == field[1][1] && field[1][1] == field[2][2]
			&& (field[0][0] == 'X' || field[0][0] == 'O'))
		{
			return std::make_pair(false, field[0][0]);
		}

		if (field[0][2] == field[1][1] && field[1][1] == field[2][0]
			&& (field[0][2] == 'X' || field[0][2] == 'O'))
		{
			return std::make_pair(false, field[0][2]);
		}

		for (size_t i = 0; i < field.size(); i++)
		{
			if (field[i][0] == field[i][1] && field[i][1] == field[i][2]
				&& (field[i][0] == 'X' || field[i][0] == 'O'))
			{
				return std::make_pair(false, field[i][0]);
			}

			if (field[0][i] == field[1][i] && field[1][i] == field[2][i]
				&& (field[0][i] == 'X' || field[0][i] == 'O'))
			{
				return std::make_pair(false, field[0][i]);
			}
		}

		int countOfSpace = 0;
		std::for_each(field.begin(), field.end(), [&countOfSpace](const std::vector<char>& item) {
			countOfSpace += std::count(item.begin(), item.end(), ' '); });

		return countOfSpace == 0 ? std::make_pair(false, 'd') : std::make_pair(true, 'n');
	}

	static std::string Recive(SOCKET client)
	{
		const int SIZE = 1024;
		char receiveBuff[SIZE]{};
		
		if (recv(client, receiveBuff, SIZE, 0) == SOCKET_ERROR)
		{
			std::cout << "recv failed: " << WSAGetLastError() << std::endl;
			closesocket(client);
		}

		return std::string(receiveBuff);
	}

	static void Proccess(const std::string& recvBuff)
	{
		std::cout << "\nMessage: " << recvBuff << std::endl;
	}

	static void Send(const SOCKET& user, const std::string& msg)
	{
		if (send(user, msg.data(), msg.size(), 0) == SOCKET_ERROR)
		{
			std::cout << "Send failed with code: " << WSAGetLastError() << std::endl;
			std::exit(-1);
		}
	}
};

std::mutex Server::mutex;
std::condition_variable Server::conditionVariable;

int main()
{
	WSADATA wsaData{};

	std::cout << "WSAData\n\tStatus: ECECUTING ... ";
	assert(!WSAStartup(MAKEWORD(2, 2), &wsaData) && std::cout << "\r\tStatus: FAILED." << std::endl);
	std::cout << "\r\tStatus: SECCESS." << std::endl;

	Server server("localhost", "666");

	WSACleanup();


	return 0;
}