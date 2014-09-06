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
/******************************************
    STILL NEED RULES HEADER, DO NOT MODIFY
********************************************/
    const std::set <Turn>& HelperBoard::get_legal_moves(void) const {
        return *valid_moves;
    }

    std::set<CheckerMove> HelperBoard::get_immediately_legal_moves(void) const {
        std::set<CheckerMove> TODO;
        return TODO; // Anti-Warning, compile
    }

    std::multiset<int> HelperBoard::get_remaining_moves(void) const {
        std::multiset<int> TODO;
        return TODO; // Anti-Warning, compile
    }

    bool HelperBoard::is_turn_done(void) const {
        bool TODO = true;
        return TODO; // Anti-Warning, compile
    }

/******************************************
STILL NEED RULES HEADER, DO NOT MODIFY
********************************************/
}
