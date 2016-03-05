#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Map.h"
#include "Character.h"
#include "Knight.h"
#include "Zombie.h"
#include "Princess.h"

using Direction = std::pair<int, int>;

class Game
{
public:
	enum class GameState { playing, paused, exiting };

	static Game& getInstance();

	void setGameState(std::string state); //todo
	void start();
	void draw();
	void gameLoop();
	bool isExiting();
	void nextMove();
	void heroMove();
	Character* findMonster(int x, int y);
	void deleteMonster(Character *target);

	Game(const Game& rhs) = delete;
	Game& operator=(const Game &rhs) = delete;

private:
	Game();

	GameState _gameState;
	std::vector<Character*> _monsters;
	Knight *_hero;
	Princess *_princess;
	Map *_map;
};