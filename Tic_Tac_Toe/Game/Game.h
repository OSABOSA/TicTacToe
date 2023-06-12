#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Includes.h"
#include "../Board/Board.h"
class Game
{
public:
    Game(int size, int winCondition, int windowW, int windowH);
    void run();

private:
    using pos = sf::Vector2f;
    sf::RenderWindow window;
    Board board;
    int winCondition;
    void render(Board& obj);
    void handleEvents(Board& obj);
    void update();
    bool checkWin(bool isPlayerTurn, Board::b board);
    bool isPlayerTurn;
    std::pair<int, Board::b> minmax(Board::b board, int depth,
        bool isMaximizingPlayer, int alpha, int beta);
    int maxDepth;
};

#include "Game.cpp"

