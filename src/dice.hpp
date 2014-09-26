#ifndef __DICELIB__
#define __DICELIB__

#include <utility>
#include <random>
#include <ctime>
#include <cstdlib>

namespace table {

    typedef std::pair<int, int> P_INT;
    typedef std::pair<int, int> DicePair;

    P_INT double_dice_roll ();
    int dice_roll();

    class DiceUtils
    {
        public:
            static bool DiceIsValid(DicePair dice_pair);
            static bool DiceIsDouble(DicePair dice_pair);
            static int DiceSum(DicePair dice_pair);
    };
}

#endif // __DICELIB__
