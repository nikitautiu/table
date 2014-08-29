#ifndef _GUI_
#define _GUI_

#include <iostream>
#include "game.hpp"

namespace table
{	
	class Gui
	{
	private:
		char m[45][21];
		int xz;
		int dxd;
		int dxu;
		std::multiset <int> zario;
		std::array <Point, NUM_POINTS> poz;

		void fillup(int dx, Point pt) // metoda umplere punct de pe interfata
		{
			char pul;
			if (pt.color == Color::BLACK)
				pul = '@';
			else
				pul = 'O';
			int t = 4 + pt.number;
			if (pt.number > 5)
			{
				t = 4;
				m[dx][8] = (pt.number - 5);
			}
			for (int i = 4; i < t; ++i)
				m[dx][i] = pul;
		}

		void filldown(int dx, Point pt) // metoda umplere punct de pe interfata
		{
			char pul;
			if (pt.color == Color::BLACK)
				pul = '@';
			else
				pul = 'O';
			int t = 4 + pt.number;
			if (pt.number > 5)
			{
				t = 4;
				m[dx][12] = (pt.number - 5);
			}
			for (int i = 16; i > t; --i)
				m[dx][i] = pul;
		}

	public:
		Gui(void); //constructor default

		void draw(void) //afisare matrice pe consola
		{
			system("cls");
			for (int i = 0; i < 21; ++i)
			{
				for (int j = 0; j < 45; ++j)
					std::cout << m[j][i];
				std::cout << '\n';
			}
		}

		void margin(void) //margine interfata si desenare tabla
		{
			for (int i = 0; i < 45; ++i) //orizontal
			{
				m[i][0] = '-';
				m[i][20] = '-';

				if (i >= 3 && i <= 33)
				{
					m[i][3] = '-';
					m[i][18] = '-';
				}
			}

			for (int i = 0; i < 21; ++i) //vertical
			{
				m[0][i] = '|';
				m[44][i] = '|';

				if (i >= 4 && i <= 17)
				{
					m[3][i] = '|';
					m[17][i] = '|';
					m[19][i] = '|';
					m[33][i] = '|';
				}

			}

		}

		void game(HelperBoard temp) //tabla si cursor
		{
			BoardState bs = temp.get_board_state();
			poz = bs.points; //tabla

			dxd = 5;
			dxu = 31;

			for (int i = 0; i < 6; ++i)
			{
				filldown(dxd, poz[i]);
				dxd += 2;
			}

			dxd = 21;

			for (int i = 6; i < 12; ++i)
			{
				filldown(dxd, poz[i]);
				dxd += 2;
			}

			for (int i = 12; i < 18; ++i)
			{
				fillup(dxu, poz[i]);
				dxu -= 2;
			}

			dxu = 15;

			for (int i = 18; i < 24; ++i)
			{
				fillup(dxu, poz[i]);
				dxu -= 2;
			}
			
			m[18][6] = bs.get_done(Color::BLACK); //iesite
			m[18][12] = bs.get_done(Color::WHITE);
			m[18][8] = bs.get_out(Color::BLACK); //scoase
			m[18][10] = bs.get_out(Color::WHITE);

			zario = temp.get_remaining_moves();
			xz = 35;
			for (int i : zario)
			{
				m[i][10] = i;
				xz += 2;
			}
		}

		void update(Backgammon temp) // zaruri ,scoase, iesite si mutari posibile
		{

			

			HelperBoard hb = HelperBoard(temp); //zaruri
			

			


		}

		void info(Backgammon temp) //scor, rand, text, stare joc
		{
			
		}
	};
}


#endif _GUI_