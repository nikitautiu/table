#ifndef round_hpp_guard
#define round_hpp_guard

#include "round.hpp"
#include "game_core.hpp"

namespace table {
/******************************************************************************
                        ROUND CLASS
*******************************************************************************/
    class Round {
    private:
        BoardState current_board_state;
        Color current_player;
        Color winner;
        RoundPhase current_phase;
        DicePair current_dice;
        bool needs_reroll;

        std::set <Turn> valid_moves;
    public:
        Round(void); // constructor inplicit
        Round(const Round&); // constructor copiere
        Round& operator=(Round); // operator copiere

        void init(Color, DicePair);

        Color get_winner(void) const;
        Color get_current_player(void) const;
        RoundPhase get_phase(void) const;
        BoardState get_board_state(void) const;
        DicePair get_dice(void) const;
        const std::set <Turn>& get_legal_moves(void) const;
        bool get_needs_reroll(void) const;

        void roll_dice(void); // arunca cu zarul, actualizeaza current_dice(atentie cand current_game_phase = STARTING)
        void submit_turn(Turn); // trimite un set de mutari. daca sunt ilegale arunca exceptie. daca nu, efectueaza
    };
}

#endif
