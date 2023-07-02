#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "../Dependences/Include/Core.hpp"

class Game : public Core::IMenu
{
private:
	char* gameResult;
	std::vector<std::vector<char>> field;
	std::vector<std::vector<Core::Button>> buttonsField;
	size_t xSelect = 0;
	size_t ySelect = 0;
	char currentMove = 'X';

public:
	Game();
	Game(char* gameResult);

private:
	virtual void Init() override;

	void CheckUserInput(Core::Event& e);

	// bool - returned value true if we can continue the game.
	// char - returned which palyer was won the game, when we continue the value will be 'n' - no-one won.
	std::pair<bool, char> IsGame();
	
	void Update();

public:
	virtual bool MainLoop() override;

	friend std::ostream& operator<<(std::ostream& out, const Game& game);
};