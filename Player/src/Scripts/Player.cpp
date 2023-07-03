#include "Player.h"

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <conio.h>

#include "ResultMenu.h"


Player::Player(const std::string& ip, const std::string& port)
	: ip(ip), port(port), client(INVALID_SOCKET), wsaData()
{
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	field =
	{
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	assert(!WSAStartup(MAKEWORD(2, 2), &wsaData));

	Init();
	while (MainLoop());
}

Player::~Player()
{	}


void Player::Init()
{
	std::cout << "getaddrinfo\n\tStatus: ECECUTING ... ";
	assert(!getaddrinfo(ip.data(), port.data(), &hints, &addrResult) && std::cout << "\r\tStatus: FAILED." << std::endl);
	std::cout << "\r\tStatus: SUCCESS." << std::endl;

	std::cout << "socket\n\tStatus: ECECUTING ... ";
	assert(!((client = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol)) == INVALID_SOCKET)
		&& std::cout << "\r\tStatus: FAILED." << std::endl);
	std::cout << "\r\tStatus: SUCCESS." << std::endl;

	std::cout << "connect\n\tStatus: ECECUTING ... ";
	assert((connect(client, addrResult->ai_addr, static_cast<int>(addrResult->ai_addrlen)) != SOCKET_ERROR) && std::cout << "\r\tStatus: FAILED." << std::endl);
	std::cout << "\r\tStatus: SUCCESS." << std::endl;

	typePlayer = Recive().at(0);
	curentMove = (typePlayer == 'X' ? true : false);

	// --------------------- UI INITIALIZATION --------------------- 
	this->user = Core::Color::DARK_RED;
	this->application = Core::Color::GREEN;

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);


	Core::Console::Clear();
	Core::Console::SetTitle(L"X AND O");
	Core::Console::ConsoleSize(25, 15);
	Core::Console::CursorVisible(false);
	Core::Console::ScrollbarVisible(false);
	Core::Console::SetCursorPosition(0, 0);


	for (size_t i = 0; i < field.size(); i++)
	{
		Core::BuildButton build;
		std::vector<Core::Button> button;
		for (size_t j = 0; j < field[0].size(); j++)
		{
			build.CreateButton();
			build.SetX(j * 5 + 6).SetY(i * 4 + 2);
			build.SetText({
				{u"████"},
				{u"████"},
				{u"████"}
				});

			build.SetCommand([&]()
				{
					if (field[ySelect][xSelect] == ' ' && curentMove)
					{
						Send(std::to_string(xSelect) + " " + std::to_string(ySelect) + " " + typePlayer);
						Recive();
						if (recivedMsg[0] == '1' && !IsGameEnded(recivedMsg))
						{
							curentMove = false;
							field[ySelect][xSelect] = typePlayer;
							buttonsField[ySelect][xSelect].SetText(std::string(1, typePlayer), Core::Fonts::FULL);
						}
					}
				});

			button.push_back(*build.GetButton().release());
		}
		buttonsField.push_back(button);
		button.clear();
	}
}

void Player::CheckUserInput(Core::Event& e)
{
	if (e.GetType() != Core::Event::EventType::NONE)
	{

		auto key = Core::EventManager::ParseKeyEvent(e);
		if (key->GetIsPressed())
		{
			switch (key->GetKey())
			{
			case Core::KeyBoard::Key::ENTER:
			{
				buttonsField[ySelect][xSelect].SetIsPressed(true);
				break;
			}

			case Core::KeyBoard::Key::RIGHT:
			{
				if (xSelect < field.size() - 1)
				{
					xSelect++;
				}
				else if (ySelect < field.size() - 1)
				{
					ySelect++;
					xSelect = 0;
				}
				else
				{
					ySelect = 0;
					xSelect = 0;
				}

				if (ySelect == 0)
				{
					select = 0 + xSelect;
				}
				else if (ySelect == 1)
				{
					select = 3 + xSelect;
				}
				else if (ySelect == 2)
				{
					select = 6 + xSelect;
				}
				break;
			}


			case Core::KeyBoard::Key::LEFT:
			{
				if (xSelect > 0)
				{
					xSelect--;
				}
				else if (ySelect > 0)
				{
					ySelect--;
					xSelect = field.size() - 1;
				}
				else
				{
					ySelect = field.size() - 1;
					xSelect = field.size() - 1;
				}

				if (ySelect == 0)
				{
					select = 0 + xSelect;
				}
				else if (ySelect == 1)
				{
					select = 3 + xSelect;
				}
				else if (ySelect == 2)
				{
					select = 6 + xSelect;
				}
				break;
			}


			case Core::KeyBoard::Key::UP:
			{
				if (ySelect > 0)
				{
					ySelect--;
				}
				else if (xSelect > 0)
				{
					xSelect--;
					ySelect = field.size() - 1;
				}
				else
				{
					xSelect = field.size() - 1;
					ySelect = field.size() - 1;
				}

				break;
			}


			case Core::KeyBoard::Key::DOWN:
			{
				if (ySelect < field.size() - 1)
				{
					ySelect++;
				}
				else if (xSelect < field.size() - 1)
				{
					xSelect++;
					ySelect = 0;
				}
				else
				{
					xSelect = 0;
					ySelect = 0;
				}

				break;
			}

			}
		}
	}
}

void Player::Update()
{
	Core::Console::SetCursorPosition(0, 0);
	std::cout << *this;
}

void Player::Disconnect()
{
	shutdown(client, SD_SEND);
	freeaddrinfo(addrResult);
	closesocket(client);
	WSACleanup();
}


void Player::Send(const std::string& msg)
{
	if (send(client, msg.data(), msg.size(), 0) == SOCKET_ERROR)
	{
		std::cout << "Sending error" << std::endl;
		Disconnect();
		std::exit(-1);
	}
}

bool Player::CheckDataAvailable()
{
	fd_set readSet{};
	FD_ZERO(&readSet);
	FD_SET(client, &readSet);

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 10;

	int result = ::select(0, &readSet, nullptr, nullptr, &timeout);
	if (result == SOCKET_ERROR)
	{
		std::cout << "select failed: " << WSAGetLastError() << std::endl;
		Disconnect();
		return false;
	}

	return (result > 0);
}

std::string Player::Recive()
{
	const int SIZE = 1024;
	char receiveBuff[SIZE]{};

	if (!CheckDataAvailable())
	{
		return std::string();
	}

	if (recv(client, receiveBuff, SIZE, 0) == SOCKET_ERROR)
	{
		std::cout << "recv failed: " << WSAGetLastError() << std::endl;
		Disconnect();
	}

	return recivedMsg = std::string(receiveBuff);
}

void Player::AnotherUserMove()
{
	auto parseStr = [](std::string str) -> std::tuple<int, int, char>
	{
		size_t index = 0;

		return std::tuple<int, int, char> {
			std::stoi(str.substr(0, index = str.find(' '))),				// cord x
				std::stoi(str.substr(index + 1, str.find(' ', index + 1))), // cord y
				str[str.size() - 1]											// type
		};
	};

	if (!curentMove)
	{
		if (recivedMsg.size() > 1 && !IsGameEnded(recivedMsg))
		{
			std::tuple<int, int, char> parsedStr = parseStr(recivedMsg);

			field[std::get<1>(parsedStr)][std::get<0>(parsedStr)] = std::get<2>(parsedStr);
			buttonsField[std::get<1>(parsedStr)][std::get<0>(parsedStr)].SetText(std::string(1, std::get<2>(parsedStr)), Core::Fonts::FULL);
			curentMove = true;
			Update();
		}
	}
}

bool Player::IsGameEnded(const std::string& msg)
{
	if (msg == "Draw")
	{
		Core::Console::Clear();
		Disconnect();

		ResultMenu resultMenu{ Core::Wallpaper("data/Walls/ResultMenus/Draw.txt") };
		while (resultMenu.MainLoop());

		return true;
	}
	else if (msg.size() > 1 && msg.substr(2) == "Won")
	{
		Core::Console::Clear();
		Disconnect();

		std::string path = "data/Walls/ResultMenus/";
		msg[0] == typePlayer ? path += "Win.txt" : path += "Lose.txt";

		ResultMenu resultMenu{ Core::Wallpaper(path) };
		while (resultMenu.MainLoop());

		return true;
	}

	return false;
}


bool Player::MainLoop()
{
	static bool firstCalling = true;
	if (firstCalling)
	{
		Update();
		firstCalling = false;
	}

	Core::Event event;
	Core::KeyEvent* key = nullptr;

	std::pair<bool, char> gameExist;


	
	if (!curentMove)
	{
		Recive();
		if (IsGameEnded(recivedMsg))
		{
			firstCalling = true;
			return false;
		}
		AnotherUserMove();
		Recive();
	}

	if (Core::EventManager::PollKeyEvent(event));
	{

		CheckUserInput(event);
		key = Core::EventManager::ParseKeyEvent(event);

		if (key)
		{
			Update();
		}
	}


	return true;
}

std::ostream& operator<<(std::ostream& out, const Player& game)
{
	Core::Console::SetTextColor(game.application); out << game.wall;

	for (size_t i = 0; i < game.buttonsField.size(); i++)
	{
		for (size_t j = 0; j < game.buttonsField.size(); j++)
		{
			if (i == game.ySelect && j == game.xSelect)
			{
				Core::Console::SetTextColor(game.user); out << game.buttonsField[i][j]; Core::Console::SetTextColor(game.application);
			}
			else
			{
				out << game.buttonsField[i][j];
			}
		}
	}

	return out;
}