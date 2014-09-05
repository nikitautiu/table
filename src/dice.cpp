#include "dice.hpp"

using namespace table {
	
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
	
}
