#include "../../Includes.h"
#include "../../Game/Game.h"

int main()
{
    int size, winCondition;

    std::cout << "Rozmiar planszy: ";
    std::cin >> size;
    std::cout << "Ile w lini by wygrac: ";
    std::cin >> winCondition;
    Game game(size, winCondition, 1400, 900);
    game.run();

    return 0;
}