#ifndef _GUI_
#define _GUI_

#include <iostream>

namespace table
{
	class gui
	{
	private:
		char draw[44][20];
	public:
		void show()
		{
			  for (int i = 0; i <= 20; ++i)
				for (int j = 0; j <= 44)
					std::cout << draw[i][j];
				  
	}
		void droll()
		{

		}
		
	};
}


#endif _GUI_