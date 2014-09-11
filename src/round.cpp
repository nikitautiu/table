#include "round.hpp"
#include "dice.hpp"
#include "rules.hpp"

namespace table {
/******************************************************************************
                        ROUND CLASS
*******************************************************************************/
    Round::Round(void) : current_board_state(),
                                   current_player(),
                                   winner(),
                                   current_phase(),
                                   current_dice(),
                                   valid_moves() {
    }

   Round::Round(const Round& other) : current_board_state(other.current_board_state),
                                                      current_player(other.current_player),
                                                      winner(other.winner),
                                                      current_phase(other.current_phase),
                                                      current_dice(other.current_dice),
                                                      valid_moves(other.valid_moves) {
    }

    Round& Round::operator=(Round other) {
        // check for assignment to self
        if ( this != &other )
            std::swap((*this), other);
        return (*this);

    }

    void Round::init(Color starting_player, DicePair starting_dice=DicePair(0,0)) {
        // initializeaza tabla, daca se da si o perche de zaruri inseamna ca s-a dat o dubla
        (*this) = Round(); // reinitializeaza cu nul
        current_board_state.init();
        current_phase = RoundPhase::GAME;
        current_player = starting_player;
        if(starting_dice == DicePair(0,0))
            needs_reroll = true;
        else {
            needs_reroll = false;
            current_dice = starting_dice;
        }
    }

    Color Round::get_winner(void) const {
        // daca ii gata partida, returneaza castigatorul
        if(current_phase != RoundPhase::NORMAL_WIN && current_phase != RoundPhase::TECHNICAL_WIN)
            throw std::runtime_error("No winner yet"); // daca nu, exceptie
        return winner;
    }

    Color Round::get_current_player(void) const {
        return current_player; // returneaza playerul actual
    }

    RoundPhase Round::get_phase(void) const {
        return current_phase;
    }

    BoardState Round::get_board_state(void) const {
        // returneaza reprezentarea tablei
        return current_board_state;
    }

    DicePair Round::get_dice(void) const {
        return current_dice;
    }

    const std::set <Turn>& Round::get_legal_moves(void) const {
        return valid_moves;
    }

    bool Round::get_needs_reroll(void) const {
        return needs_reroll;
    }

    void Round::roll_dice(void) {
        if(current_phase != RoundPhase::GAME)
            throw std::runtime_error("Can only roll during game phase");
        else if(!needs_reroll)
            throw std::runtime_error("Dice does not need to be rerolled");
        else {
            current_dice = double_dice_roll();
            valid_moves = table::get_legal_moves(current_board_state, current_player, current_dice);
        }
    }

    void Round::submit_turn(Turn moves) {
        if(valid_moves.find(moves) != valid_moves.end()) {
            auto new_board_state = process_board(current_board_state, moves);
            current_board_state = new_board_state;
        }
        else if(current_phase == RoundPhase::GAME)
            throw std::runtime_error("Illegal moves");
        else
            throw std::runtime_error("Cannot move in this game phase");
    }
}
