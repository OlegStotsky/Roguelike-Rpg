#include "Game.h"

using namespace std;

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

Game::Game()
{
	_map = new Map;

	_map->readInp("map.txt");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			switch (_map->_map[i][j])
			{
			case 'H':
				_hero = new Knight(j, i, hero_hp);
				break;
			case 'Z':
				_monsters.push_back(new Zombie(i, j, hero_hp));
				break;
			case 'P':
				_princess = new Princess(i, j, princess_hp);
				break;
			}
		}
	}

	_gameState = GameState::playing;
}

void Game::setGameState(string state)
{
	if (state == "playing")
		_gameState = GameState::playing;
	if (state == "paused")
		_gameState = GameState::paused;
	if (state == "exiting")
		_gameState = GameState::exiting;
}

void Game::start()
{
	while (!isExiting())
	{
		gameLoop();
	}
}

void Game::draw()
{
	_map->draw();
	cout << _hero->hitPoints() << endl;
}

void Game::gameLoop()
{
	draw();
	nextMove();
}

bool Game::isExiting()
{
	return (_gameState == GameState::exiting ? true : false);
}

void Game::nextMove()
{
	_hero->move(_map);
	for (auto monster : _monsters)
	{
		monster->move(_map);
	}
}

Character* Game::findMonster(int x, int y)
{
	for (auto monster : _monsters)
	{
		if (monster->x() == x && monster->y() == y)
			return monster;
	}

	return nullptr;
}

void Game::deleteMonster(Character *target)
{
	auto it = find(_monsters.begin(), _monsters.end(), target);
	if (it == _monsters.end())
	{
		throw std::runtime_error("Trying to delete non existing monster");
	}
	_monsters.erase(it);
}