#include "gui.hpp"

namespace table
{

	Gui::Gui(void) : zaruri(), xz(), dxd(), dxu(), poz(){}

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

	void Gui::update(HelperBoard temp)
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

		zaruri = temp.get_remaining_moves(); //zaruri
		xz = 35;
		for (int i : zaruri)
		{
			m[i][10] = i; 
			xz += 2;
		}
	
		Color cp = temp.get_current_player(); //rand
		if (cp == Color::BLACK)
		{
			m[39][13] = 'X';
			m[39][7] = ' ';
		}

		else
		{
			m[39][13] = ' ';
			m[39][7] = 'X';
		}

		draw(); //desenare matrice
	}

	void Gui::dice(DicePair temp)
	{
		m[35][10] = temp.first;
		m[37][10] = temp.second;
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

	void Gui::draw_score(const IMatch& temp)
	{
		std::pair<int, int> scor = temp.get_score(Color::BLACK);
		m[37][7] = scor.second;
		m[37][13] = scor.first;
		draw();
	}

	void Gui::match_ro_init()
	{
		RoMatch meci(3,true);
		auto faza = meci.get_current_phase();
		while (faza->get_win_outcome().first == "not_won")
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			faza->roll_dice();
			DicePair p = faza->get_current_dices();
			dice(p);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			faza->roll_dice();
			DicePair m = faza->get_current_dices();
			dice(m);
		}
		while (!meci.is_game_over())
		{
			meci.next_phase();
			faza = meci.get_current_phase();
			while (faza->get_win_outcome().first == "not_won")
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
				faza->roll_dice();
				HelperBoard temp(*faza);
				bool ok = true;
				bool can_undo = false;
				bool gata = false;
				while ( !gata )
				{
					int undo;
					if (can_undo)
					{
						std::cout << "Anulati mutarea? (1|0) ";
						std::cin >> undo;
						if (undo == 1)
						{
							temp.pop_move();
						}
						if (temp.is_turn_done())
							gata = true;
						else
							ok = true;

					}
					while (ok)
					{
						update(temp);
						CheckerMove cm;
						std::cout << '/n' << "Pozitie: ";
						std::cin >> cm.first;
						std::cout << '\n' << "Increment: ";
						std::cin >> cm.second;
						std::set<CheckerMove> pos_mov = temp.get_immediately_legal_moves();
						for (CheckerMove i : pos_mov)
						{
							if (i == cm)
							{
								ok = false;
								temp.push_move(cm);
								can_undo = true;
								break;
							}
						}
					}
				}
				if (gata)
					faza->submit_moves(temp.get_turn());
			}
			meci.next_phase();
			draw_score(meci);
		}
	}
}