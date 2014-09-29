#include "helper_board.hpp"

namespace table {
/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    HelperBoard::HelperBoard(void) : _initial_board_state(),
                                     _current_board_state(),
                                     player(),
                                     dices(),
                                     valid_moves() {
    }

    HelperBoard::HelperBoard(const IPhase& phase) {
        init_from_board(phase);
    }

    HelperBoard::HelperBoard(const HelperBoard& other) : _initial_board_state(other._initial_board_state),
                                                         _current_board_state(other._current_board_state),
                                                         player(other.player),
                                                         dices(other.dices),
                                                         remaining_moves(other.remaining_moves) {
    }

    void HelperBoard::init_from_board(const IPhase& phase) {
        _initial_board_state = phase.get_current_board_state();
        _current_board_state = _initial_board_state;
        player = phase.get_current_player();
        dices = phase.get_current_dices();
        remaining_moves = std::multiset<int> ();
        valid_moves = &(phase.get_legal_moves());
        _board_process_func = phase.get_board_processing_function();
    }

    HelperBoard& HelperBoard::operator=(HelperBoard other)  {
        if ( this != &other )
            std::swap((*this), other);
        return (*this);
    }

    BoardState HelperBoard::get_board_state(void) const {
        return _current_board_state;
    }

    Turn HelperBoard::get_turn(void) const {
        return history;
    }

    void HelperBoard::push_move(CheckerMove checkerMove) {
        history.push_back(checkerMove);
        _current_board_state = _board_process_func(_initial_board_state, history);
    }

    void HelperBoard::pop_move(void) {
        history.pop_back();
        _current_board_state = _board_process_func(_initial_board_state, history);
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

    Color HelperBoard::get_current_player(void) const {
        return this->player;
    }
}
