#include "Game.h"

Game::Game(int size, int winCondition, int windowW, int windowH)
: window(sf::VideoMode(windowW, windowH), "Tic Tac Toe")
, board(size, windowW, windowH)
, isPlayerTurn(true)
, winCondition(winCondition)
, maxDepth(6)
{}

void Game::run()
{
    while (window.isOpen()) {


        render(this->board);
        window.display();
        if (isPlayerTurn) 
        {
            handleEvents(this->board);
            update();
        }
        else
        {
            Board::b bestMove;
            bestMove = minmax(this->board.board, maxDepth, isPlayerTurn, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()).second;
            this->board.board = bestMove;
            isPlayerTurn = true;
            sf::Event event;
            while (window.pollEvent(event)) {}
        }
    }
}

void Game::render(Board &obj)
{
    window.clear(sf::Color::White);
    for (auto &row : obj.board)
    {
        for (auto &tile : row) 
        {
            window.draw(tile.object);
        }
    }
}

void Game::handleEvents(Board& board)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int selectedRow = -1, selectedCol = -1;

                for (int iter = 0; iter < board.size; iter++)
                {
                    if (y > board.board.at(iter).at(0).startY
                        && y < board.board.at(iter).at(0).endY)
                        selectedRow = iter;
                    if (x > board.board.at(0).at(iter).startX
                        && x < board.board.at(0).at(iter).endX)
                        selectedCol = iter;
                }

                if (!(selectedRow == -1 || selectedCol ==-1) && board.board.at(selectedRow).at(selectedCol).isEmpty)
                {
                    isPlayerTurn = false;
                    board.board.at(selectedRow).at(selectedCol).isPlayer = true;
                    board.board.at(selectedRow).at(selectedCol).isEmpty = false;
                }

            }
        }
    }
}

void Game::update()
{
    for (auto &row : board.board)
    {
        for (auto &tile : row)
        {
            if (tile.isBot)
                tile.object.setFillColor(sf::Color::Blue);
            else if (tile.isPlayer)
                tile.object.setFillColor(sf::Color::Red);
            else if (tile.isEmpty)
                tile.object.setFillColor(sf::Color::White);
        }
    }
}

bool Game::checkWin(bool isPlayerTurn, Board::b board)
{
    int size = board.size();
    // check rows
    if (isPlayerTurn)
    {
        for (size_t row = 0; row < size; row++)
        {
            int count = 0;
            for (size_t col = 0; col < size; col++)
            {
                if (board.at(row).at(col).isPlayer) {
                    count++;
                    if (count == winCondition)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }

        // check columns
        for (size_t col = 0; col < size; col++)
        {
            int count = 0;
            for (size_t row = 0; row < size; row++)
            {
                if (board.at(row).at(col).isPlayer) {
                    count++;
                    if (count == winCondition)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }


        // check diagonal down to right
        for (size_t row = 0; row <= size - winCondition; row++)
        {
            for (size_t col = 0; col <= size - winCondition; col++) {
                int count = 0;
                for (size_t off = 0; off < winCondition; off++)
                {
                    if (board.at(row + off).at(col + off).isPlayer) {
                        count++;
                        if (count == winCondition)
                            return true;
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }

        // check diagonal down to left
        for (size_t row = 0; row <= size - winCondition; row++)
        {
            for (size_t col = winCondition - 1; col <= size - winCondition; col++) {
                int count = 0;
                for (size_t off = 0; off < winCondition; off++)
                {
                    if (board.at(row + off).at(col - off).isPlayer) {
                        count++;
                        if (count == winCondition)
                            return true;
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }

        return false;
    }
    else
    {
        for (size_t row = 0; row < size; row++)
        {
            int count = 0;
            for (size_t col = 0; col < size; col++)
            {
                if (board.at(row).at(col).isBot) {
                    count++;
                    if (count == winCondition)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }

        // check columns
        for (size_t col = 0; col < size; col++)
        {
            int count = 0;
            for (size_t row = 0; row < size; row++)
            {
                if (board.at(row).at(col).isBot) {
                    count++;
                    if (count == winCondition)
                        return true;
                }
                else {
                    count = 0;
                }
            }
        }


        // check diagonal down to right
        for (size_t row = 0; row <= size - winCondition; row++)
        {
            for (size_t col = 0; col <= size - winCondition; col++) {
                int count = 0;
                for (size_t off = 0; off < winCondition; off++)
                {
                    if (board.at(row + off).at(col + off).isBot) {
                        count++;
                        if (count == winCondition)
                            return true;
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }

        // check diagonal down to left
        for (size_t row = 0; row <= size - winCondition; row++)
        {
            for (size_t col = winCondition - 1; col <= size - winCondition; col++) {
                int count = 0;
                for (size_t off = 0; off < winCondition; off++)
                {
                    if (board.at(row + off).at(col - off).isBot) {
                        count++;
                        if (count == winCondition)
                            return true;
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }

        return false;
    }
    
}

std::pair<int, Board::b> Game::minmax(Board::b board, int depth, bool isPlayer, int alpha, int beta)
{
    //create all possible outcomes
    std::vector<Board::b> vecBoards;
    for (auto& row : board)
    {
        for (auto& tile : row)
        {
            if (tile.isEmpty)
            {
                tile.isEmpty = false;
                if (isPlayer)
                    tile.isPlayer = true;
                else
                    tile.isBot = true;
                vecBoards.push_back(board);
                if (isPlayer)
                    tile.isPlayer = false;
                else
                    tile.isBot = false;
                tile.isEmpty = true;
            }
        }
    }

    //win condition
    if (checkWin(!isPlayer, board))
    {
        std::pair<int, Board::b> pair;
            if (!isPlayer)
            {
                pair.first = std::numeric_limits<int>::max();
            }
            else
            {
                pair.first = std::numeric_limits<int>::min();
            }
        pair.second = board;
        return pair;
    }

    if (!depth || !vecBoards.size())
    {
        std::pair<int, Board::b> ret;
        ret.first = 0;
        ret.second = board;
        return ret; //static eval (this one does quite ok)
    }

    int noOfBoards = vecBoards.size();


    if (isPlayer)
    {
        std::pair<int, Board::b> maxEval;
        maxEval.first = std::numeric_limits<int>::min();
        maxEval.second = board;
        for (size_t i = 0; i < noOfBoards; i++)
        {
            std::pair<int, Board::b> eval;
            eval = minmax(vecBoards.at(i), depth - 1, false, alpha, beta);
            eval.second = vecBoards.at(i);
            if (eval.first > alpha)
            {
                alpha = eval.first;
                maxEval = eval;
            }
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else
    {
        std::pair<int, Board::b> minEval;
        minEval.first = std::numeric_limits<int>::max();
        minEval.second = board;
        for (size_t i = 0; i < noOfBoards; i++)
        {
            std::pair<int, Board::b> eval;
            eval = minmax(vecBoards.at(i), depth - 1, true, alpha, beta);
            eval.second = vecBoards.at(i);
            if (eval.first < beta)
            {
                beta = eval.first;
                minEval = eval;
            }
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}