#ifndef _GUI_
#define _GUI_

#include <iostream>
#include "phase.hpp"

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
		std::array<Point, NUM_POINTS> poz;

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

		void draw(void); //afisare matrice pe consola

		void initialize(void); //margine interfata si desenare tabla
		
		void update(PhaseView temp); //tabla, iesite, scoase, zaruri si cursor(de implmentat)
		


		void info(Backgammon temp) //scor, rand, text, stare joc
		{
			if (temp.get_current_player() == Color::WHITE && temp.get_phase == GamePhase::GAME) //rand
			{
				m[39][7] = ' ';
				m[39][13] = 'R';
			}
				
			else if (temp.get_phase == GamePhase::GAME)
			{
				m[39][7] = 'R';
				m[39][13] = ' ';
			}

			else if (temp.get_phase() != GamePhase::GAME)
			{
				m[39][7] = ' ';
				m[39][13] = ' ';
			}


			draw();
		}
	};
}


#endif _GUI_