#include "gui.hpp"

namespace table
{

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

	void Gui::update(PhaseView temp)
	{
		BoardState bs = temp.get_current_board_state();
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

		zario = temp.get_remaining_moves(); //zaruri ISSUE. nu exsista metoda care returneaza zarurile curente
		xz = 35;
		for (int i : zario)
		{
			m[i][10] = i; 
			xz += 2;
		}

		draw();
	}
}