#include "Tile.h"

Tile::Tile(int startX, int startY, int tileDimmension)
{
	this->startX = startX;
	this->startY = startY;
	this->endX = startX + tileDimmension;
	this->endY = startY + tileDimmension;

	sf::RectangleShape inside(pos(tileDimmension, tileDimmension));
	inside.setPosition(startX, startY);
	inside.setOutlineThickness(2.f);
	inside.setOutlineColor(sf::Color::Black);
	inside.setFillColor(sf::Color::White);
	this->object = inside;

	this->isPlayer = false;
	this->isBot = false;
	this->isEmpty = true;
}