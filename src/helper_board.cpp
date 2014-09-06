#include "helper_board.hpp"

namespace table {
/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    HelperBoard::HelperBoard(void) : current_board_state(),
                                     player(),
                                     dices(),
                                     remaining_moves(),
                                     valid_moves() {
    }

    HelperBoard::HelperBoard(const Round& round) {
        init_from_board(round);

    }

    HelperBoard::HelperBoard(const HelperBoard& other) : current_board_state(other.current_board_state),
                                                         player(other.player),
                                                         dices(other.dices),
                                                         remaining_moves(other.remaining_moves) {
    }

    void HelperBoard::init_from_board(const Round& round) {
        current_board_state = round.get_board_state();
        player = round.get_current_player();
        dices = round.get_dice();
        remaining_moves = std::multiset<int> ();
        valid_moves = &(round.get_legal_moves());

        if ( dices.first == dices.second )
            for (int i = 0; i < 4; ++i)
                remaining_moves.insert(dices.first);
        else
            remaining_moves.insert(dices.first),
            remaining_moves.insert(dices.second);
    }

    HelperBoard& HelperBoard::operator=(HelperBoard other)  {
        if ( this != &other )
            std::swap((*this), other);
        return (*this);
    }

    BoardState HelperBoard::get_board_state(void) const {
        return current_board_state;
    }

    Turn HelperBoard::get_turn(void) const {
        return history;
    }

    void HelperBoard::push_move(CheckerMove checkerMove) {
        history.push_back(checkerMove);
    }

    void HelperBoard::pop_move(void) {
        history.pop_back();
    }

    const std::set <Turn>& HelperBoard::get_legal_moves(void) const {
        return *valid_moves;
    }

    // AJUTOR
    std::set<CheckerMove> HelperBoard::get_immediately_legal_moves(void) const {
        std::set<CheckerMove> rval;
        for ( auto i : *valid_moves )
        {
            bool valid;
            for (unsigned int ii = 0; ii < i.size() &&
                                      ii < history.size(); ++ii)
            {
                if ( i[ii] != history[ii] ) {
                    valid = false;
                    break;
                }
            }
            if ( valid && history.size() < i.size() )
                rval.insert(i[history.size()]);

        }
        return rval;
    }

    std::multiset<int> HelperBoard::get_remaining_moves(void) const {
        return this->remaining_moves;
    }

    bool HelperBoard::is_turn_done(void) const {
        if ( get_immediately_legal_moves().empty() )
            return true;
        return false;
    }
}
