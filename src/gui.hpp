<<<<<<< HEAD
#ifndef gui_hpp_guard
#define gui_hpp_guard

#include <iostream>
#include "phase.hpp"
#include "match.hpp"
#include "helper_board.hpp"
#include "variants\rules_ro.hpp"
#include <chrono>
#include <thread>

namespace table
{	
	class Gui
	{
	private:
		char m[45][21]; //matrice afisare continut
		int xz; //increment afisare zaruri
		int dxd; //increment afisare puncte jos
		int dxu; //increment afisare puncte sus
		std::multiset<int> zaruri; //multiset pentru zarurile ramase
		PointArray poz; //array de puncte pentru afisare

		void fillup(int dx, Point pt) // metoda umplere puncte de sus de pe interfata
=======
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
>>>>>>> master
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

<<<<<<< HEAD
		void filldown(int dx, Point pt) // metoda umplere puncte de jos de pe interfata
=======
		void filldown(int dx, Point pt) // metoda umplere punct de pe interfata
>>>>>>> master
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

<<<<<<< HEAD
		void match_ro_init(); //initializare partida romaneasca

		void draw(void); //afisare matrice pe consola

		void dice(DicePair temp); //afisare zaruri

		void draw_score(const IMatch& temp); //afisare scor

		void initialize(void); //margine interfata si desenare tabla
		
		void update(HelperBoard temp); //tabla, iesite, scoase, zaruri, rand si cursor(de implmentat)
		
		void launch_menu(void); //deschidere meniu


=======
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

		void initialize(void) //margine interfata si desenare tabla
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

		void update(HelperBoard temp) //tabla, iesite, scoase, zaruri si cursor
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

			zario = temp.get_remaining_moves(); //zaruri
			xz = 35;
			for (int i : zario)
			{
				m[i][10] = i;
				xz += 2;
			}

			draw();
		}


		void info(Backgammon temp) //scor, rand, text, stare joc
		{

		}
>>>>>>> master
	};
}


<<<<<<< HEAD
#endif gui_hpp_guard
=======
#endif _GUI_
>>>>>>> master
