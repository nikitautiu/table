#ifndef __DICELIB__
#define __DICELIB__

#include <utility>
#include <random>
#include <ctime>
#include <cstdlib>

namespace table {

    typedef std::pair<int, int> P_INT;

    P_INT double_dice_roll ();
    int dice_roll();
}

#endif // __DICELIB__
