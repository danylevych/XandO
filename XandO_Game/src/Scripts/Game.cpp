#include "Game.h"

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "../Dependences/Include/Core.hpp"

Game::Game()
	: IMenu(),
	gameResult(nullptr) 
{
	Init();
}

Game::Game(char* gameResult)
	: IMenu(),
	gameResult(gameResult)
{
	Init();
}


void Game::Init()
{
	field = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	this->user = Core::Color::DARK_RED;
	this->application = Core::Color::GREEN;


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
					if (field[ySelect][xSelect] == ' ')
					{
						field[ySelect][xSelect] = currentMove;
						buttonsField[ySelect][xSelect].SetText(std::string(1, currentMove), Core::Fonts::FULL);

						currentMove == 'X' ? currentMove = 'O' : currentMove = 'X';
					}
				});

			button.push_back(*build.GetButton().release());
		}
		buttonsField.push_back(button);
		button.clear();
	}
}

void Game::CheckUserInput(Core::Event& e)
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

std::pair<bool, char> Game::IsGame()
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

bool Game::MainLoop()
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

	
	if (Core::EventManager::PollKeyEvent(event));
	{
		CheckUserInput(event);
		key = Core::EventManager::ParseKeyEvent(event);

		if (key)
		{
			Update();
		}

		gameExist = IsGame();
		if (!gameExist.first)
		{
			*gameResult = gameExist.second;
			firstCalling = true;
			return false;
		}
	}

	return true;
}

void Game::Update()
{
	Core::Console::SetCursorPosition(0, 0);
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Game& game)
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