#ifndef __DICELIB__
#define __DICELIB__

#include <utility>
#include <random>
#include <ctime>
#include <cstdlib>

namespace table {

    typedef std::pair<int, int> P_INT;

    P_INT DoubleDiceRoll ()
    {
        std::time_t time = std::time(NULL);
        std::mt19937 generator(rand() + time);
        std::uniform_int_distribution<int> distribution(1, 6);

        int dice_roll1 = distribution(generator);
        int dice_roll2 = distribution(generator);




        return std::make_pair(dice_roll1, dice_roll2);

    }

    int DiceRoll()
    {
        std::time_t time = std::time(NULL);
        std::mt19937 generator(rand() + time);
        std::uniform_int_distribution<int> distribution(1, 6);
        int dice_roll1 = distribution(generator);

        return dice_roll1;
    }

}



#endif // __DICELIB__
