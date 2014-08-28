#ifndef _GUI_
#define _GUI_

#include <iostream>
#include "game.hpp"

namespace table
{	
	class gui
	{
	private:
		char m[45][21];
		int xz;
		std::vector <int> zario;
	public:
		gui(void); //constructor default

		void draw(void) //afisare matrice pe consola
		{
			system("cls");
			for (int i = 0; i < 21; ++i)
			{
				for (int j = 0; j < 45; ++j)
					cout << m[j][i];
				cout << '\n';
			}
		}

		void margin(void) //margine interfata si desenare tabla
		{
			for (int i = 0; i < 45; ++i) //orizontal
			{
				m[i][0] = "-";
				m[i][20] = "-";

				if (i >= 3 && i <= 33)
				{
					m[i][3] = "-";
					m[i][18] = "-";
				}
			}

			for (int i = 0; i < 21; ++i) //vertical
			{
				m[0][i] = "|";
				m[44][i] = "|";

				if (i >= 4 && i <= 17)
				{
					m[3][i] = "|";
					m[17][i] = "|";
					m[19][i] = "|";
					m[33][i] = "|";
				}

			}

		}

		void update(table::Board temp) //tabla, zaruri ,scoase, iesite si mutari posibile
		{
			zario = temp.get_remaining_moves(); //zaruri
			xz = 35;
			for (int i : zario)
			{
				m[x][10] = i;
				xz += 2;
			}

			
		}

		void info(table::Board temp) //scor, rand, text
		{
			
		}
	};
}


#endif _GUI_