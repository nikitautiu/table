#ifndef gui_hpp_guard
#define gui_hpp_guard

#include <iostream>
#include "phase.hpp"
#include "match.hpp"
#include "helper_board.hpp"
#include "variants\rules_ro.hpp"

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
		PointArray poz;

		void fillup(int dx, Point pt) // metoda umplere puncte de sus de pe interfata
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

		void filldown(int dx, Point pt) // metoda umplere puncte de jos de pe interfata
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

		void match_ro_init(); //initializare partida romaneasca

		void draw(void); //afisare matrice pe consola

		void initialize(void); //margine interfata si desenare tabla
		
		void update(BoardState bs); //tabla, iesite, scoase, zaruri si cursor(de implmentat)
		
		void launch_menu(void); //deschidere meniu

	};
}


#endif gui_hpp_guard