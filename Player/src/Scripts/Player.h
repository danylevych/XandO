#pragma once

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>
#include <vector>
#include "../../../Event/Core.hpp"

#pragma comment(lib, "Ws2_32.lib")


class Player : public Core::IMenu
{
private:
	WSADATA wsaData;
	SOCKET client;
	ADDRINFO hints{};
	ADDRINFO* addrResult = nullptr;

	std::string ip;
	std::string port;


private:
	bool curentMove;
	char typePlayer;
	std::vector<std::vector<char>> field;
	std::vector<std::vector<Core::Button>> buttonsField;
	size_t xSelect = 0;
	size_t ySelect = 0;

	std::string recivedMsg;


public:
	Player(const std::string& ip, const std::string& port);

	~Player();


private:
	virtual void Init() override;

	void CheckUserInput(Core::Event& e);

	void Update();

	void Disconnect();


private:
	void Send(const std::string& msg);

	bool CheckDataAvailable();

	std::string Recive();

	void AnotherUserMove();

	bool IsGameEnded(const std::string& msg);


private:
	virtual bool MainLoop() override;

	friend std::ostream& operator<<(std::ostream& out, const Player& game);
};