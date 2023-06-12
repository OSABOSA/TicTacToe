#include "Board.h"

Board::Board(int size, int windowW, int windowH)
{
	this->size = size;
	int boardDimmension, tileDimmension;
	if (windowW>windowH)
		boardDimmension = windowH * 0.8;
	else
		boardDimmension = windowW * 0.8;
	topY = (windowH - boardDimmension) / 2;
	botY = topY + boardDimmension;
	topX = (windowW - boardDimmension) / 2;
	botX = topX + boardDimmension;
	tileDimmension = boardDimmension / size;

	using b = std::vector<std::vector<Tile>>;
	std::vector <Tile> r;
	
	for (int row = 0; row < size; row++)
	{
		board.push_back(r);
		for (int column = 0; column < size; column++)
		{
			int startX, startY;
			startX = topX + column * tileDimmension;
			startY = topY + row * tileDimmension;
			Tile t(startX, startY, tileDimmension);
			board.at(row).push_back(t);
		}
	}
}

