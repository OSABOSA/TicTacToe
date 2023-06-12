#pragma once
#include "../Includes.h"

class Tile
{
public:
	using pos = sf::Vector2f;
	Tile() {};
	Tile(int startX, int startY, int tileDimmension);
	int startX, startY;
	int endX, endY;
	sf::RectangleShape object;
	bool isPlayer;
	bool isBot;
	bool isEmpty;
};

#include "Tile.cpp"