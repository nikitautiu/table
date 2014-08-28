#ifndef _GUI_
#define _GUI_

#include <iostream>
#include "game.hpp"

namespace table
{
	class gui
	{
	private:
		char draw[44][20];
		Board act;
	public:
		gui(void); //constructor default

		void draw(void) //tabla, zaruri si mutari posibile
		{

		}

		void info(void) //scor, rand, text
		{
			
		}
	};
}


#endif _GUI_