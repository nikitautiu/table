#include "gui.hpp"

namespace table
{

	Gui::Gui(void) : m(), zaruri(), xz(), dxd(), dxu(), poz(){}

	void Gui::draw(void)
	{
		system("cls"); //curata ecranul
		for (int i = 0; i < 21; ++i)
		{
			for (int j = 0; j < 45; ++j)
				std::cout << m[j][i];
			std::cout << '\n';
		}
	}

	void Gui::initialize(void)
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

	void Gui::update(BoardState bs)
	{
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

		/*
		zaruri = temp.get_remaining_moves(); //zaruri ISSUE. nu exsista metoda care returneaza zarurile curente
		xz = 35;
		for (int i : zaruri)
		{
			m[i][10] = i; 
			xz += 2;
		}
		*/
		draw();
	}

	void Gui::launch_menu(void)
	{
		int s;
		system("color 8F");
		system("cls"); //curata ecranul
		std::cout << "				~BAGAMON~" << '\n';
		std::cout << "-------------------------------------" << '\n';
		std::cout << "1 - Joaca" << '\n';
		std::cout << "2 - Despre" << '\n';
		std::cout << "3 - Iesire" << '\n' << "Selectati o optiune: ";
		system("pause>nul");
		std::cin >> s;
		if (s == 1 || s == 2 || s == 3)
		{
			if (s == 3)
				system("exit");
			else if (s == 2)
			{
			}
			else if (s == 1)
			{
				system("cls");
				std::cout << "1. Romanesti" << '\n';
				std::cout << "2. Rusesti" << '\n';
				system("pause>nul");
				std::cin >> s;
				if (s == 1 || s == 2)
				{
					if (s == 1)
						match_ro_init();
					else if (s == 2)
						match_ro_init();
				}
			}
		}
		else
			launch_menu();
	}

	void Gui::match_ro_init()
	{
		system("cls");
		std::cout << "ROMANESti";

	}
}