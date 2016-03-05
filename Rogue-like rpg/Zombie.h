#pragma once

#include "Character.h"

class Zombie : public Character
{
public:
	Zombie(int x, int y, int hp) :
		Character(x, y, hp) {}

	inline char symbol() override { return 'z'; }
	inline int damage() const override { return zombie_damage; }

	void move();
	void recieveDamage();
};