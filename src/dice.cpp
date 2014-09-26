#include "dice.hpp"

namespace table {

/***********************************************************************************
                            GLOBAL NAMESPACE
***********************************************************************************/

	P_INT double_dice_roll()
	{
        std::time_t time = std::time(NULL);
        std::mt19937 generator(rand() + time);
        std::uniform_int_distribution<int> distribution(1, 6);

        int dice_roll1 = distribution(generator);
        int dice_roll2 = distribution(generator);


        return std::make_pair(dice_roll1, dice_roll2);
	}

	int dice_roll()
	{
        std::time_t time = std::time(NULL);
        std::mt19937 generator(rand() + time);
        std::uniform_int_distribution<int> distribution(1, 6);
        int dice_roll1 = distribution(generator);

        return dice_roll1;
	}

/***********************************************************************************
                            CLASS DICEUTILS
***********************************************************************************/

    bool DiceUtils::DiceIsValid(DicePair dice_pair)
    {
        if ( dice_pair.first < 1 || dice_pair.first > 6 )
            return false;
        if ( dice_pair.second < 1 || dice_pair.second > 6 )
            return false;
        return true;
    }

    bool DiceUtils::DiceIsDouble(DicePair dice_pair)
    {
        if ( dice_pair.first == dice_pair.second )
            return true;
        return false;
    }

    int DiceUtils::DiceSum(DicePair dice_pair)
    {
        return dice_pair.first + dice_pair.second;
    }

}
