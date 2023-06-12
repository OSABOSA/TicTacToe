#pragma once
#include "../Includes.h"
#include "../Tile/Tile.h"


class Board
{
public:
	using b = std::vector<std::vector<Tile>>;
	Board(int size, int windowW, int windowH);
	int size;
	int topX, topY;
	int botX, botY;
	b board;
};

#include "Board.cpp"