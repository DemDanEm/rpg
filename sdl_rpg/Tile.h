#pragma once
#include <string>
#include "Vector2.h"


class Tile
{
public:
	std::string spritePath;
	Vector2 grid;

	bool collision;

	Tile(std::string sprite, Vector2 pos, bool coll = false)
	{
		this->spritePath = sprite;
		this->grid = pos;
		this->collision = coll;
	}

};