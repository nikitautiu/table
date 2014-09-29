#include "helper_board.hpp"

namespace table {
/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    HelperBoard::HelperBoard(void) : _initial_board_state(),
                                     _current_board_state(),
                                     _player(),
                                     _dices(),
                                     _valid_moves()
    {
    }

    HelperBoard::HelperBoard(const IPhase& phase)
    {
        _init_from_board(phase);
    }

    HelperBoard::HelperBoard(const HelperBoard& other) : _initial_board_state(other._initial_board_state),
                                                         _current_board_state(other._current_board_state),
                                                         _player(other._player),
                                                         _dices(other._dices),
                                                         _remaining_moves(other._remaining_moves)
    {
    }

    void HelperBoard::_init_from_board(const IPhase& phase)
    {
        _initial_board_state = phase.get_current_board_state();
        _current_board_state = _initial_board_state;
        _player = phase.get_current_player();
        _dices = phase.get_current_dices();
        _remaining_moves = std::multiset<int> {_dices.first, _dices.second};
        _valid_moves = &(phase.get_legal_moves());
        _board_process_func = phase.get_board_processing_function();
    }

    HelperBoard& HelperBoard::operator=(HelperBoard other)
    {
        if(this != &other)
            std::swap((*this), other);
        return (*this);
    }

    BoardState HelperBoard::get_board_state(void) const
    {
        return _current_board_state;
    }

    Turn HelperBoard::get_turn(void) const
    {
        return _history;
    }

    void HelperBoard::push_move(CheckerMove checkerMove)
    {
        _history.push_back(checkerMove);
        _current_board_state = _board_process_func(_initial_board_state, _history);
    }

    void HelperBoard::pop_move(void)
    {
        _history.pop_back();
        _current_board_state = _board_process_func(_initial_board_state, _history);
    }

    const std::set <Turn>& HelperBoard::get_legal_moves(void) const
    {
        return *_valid_moves;
    }

    // AJUTOR
    std::set<CheckerMove> HelperBoard::get_immediately_legal_moves(void) const
    {
        std::set<CheckerMove> rval;
        for ( auto i : *_valid_moves )
        {
            bool valid;
            for (unsigned int ii = 0; ii < i.size() &&
                                      ii < _history.size(); ++ii)
            {
                if ( i[ii] != _history[ii] ) {
                    valid = false;
                    break;
                }
            }
            if ( valid && _history.size() < i.size() )
                rval.insert(i[_history.size()]);

        }
        return rval;
    }

    std::multiset<int> HelperBoard::get_remaining_moves(void) const
    {
        return _remaining_moves;
    }

    bool HelperBoard::is_turn_done(void) const
    {
        if(get_immediately_legal_moves().empty())
            return true;
        return false;
    }

    Color HelperBoard::get_current_player(void) const
    {
        return _player;
    }
}
