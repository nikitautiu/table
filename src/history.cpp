#include "history.hpp"

namespace table {
/******************************************************************************
                        CLASS LOGGED PHASE
******************************************************************************/

    LoggedPhase::LoggedPhase(IPhase& phase) : _wrapped_phase(&phase) // constructor
    {
    }

    // GETTERE
    BoardState LoggedPhase::get_current_board_state(void) const
    {

        return _wrapped_phase->get_current_board_state();
    }

    PhaseType LoggedPhase::get_phase_type(void) const
    {
        return _wrapped_phase->get_phase_type();
    }

    DiceObligation LoggedPhase::get_dice_obligation(void) const
    {
        return _wrapped_phase->get_dice_obligation();
    }

    Color LoggedPhase::get_current_player(void) const
    {
        return _wrapped_phase->get_current_player();
    }

    DicePair LoggedPhase::get_current_dices(void) const
    {
        return _wrapped_phase->get_current_dices();
    }

    const std::set<Turn>& LoggedPhase::get_legal_moves(void) const
    {
        return _wrapped_phase->get_legal_moves();
    }

    WinPair LoggedPhase::get_win_outcome(void) const
    {
        return _wrapped_phase->get_win_outcome();
    }

    History LoggedPhase::get_history(void) const
    {
        return _history;
    }
    // SFARSIT GETTERE

    void LoggedPhase::roll_dice(void) // da cu zarul
    {
        _wrapped_phase->roll_dice();
    }

    void LoggedPhase::submit_moves(Turn moves) // updateaza istoria
    {
        _wrapped_phase->submit_moves(moves);
        HistoryElement update_value;
        update_value.dices = _wrapped_phase->get_current_dices();
        update_value.player = _wrapped_phase->get_current_player();
        update_value.turn = moves;
        _history.push_back(update_value);

        if((_wrapped_phase->get_win_outcome()).first != "not_won") // daca este sfarsitul liniei se apeleaza on_phase_end()
            _observer->on_phase_end(*this);
    }


/******************************************************************************
                        CLASS LOGGED MATCH
******************************************************************************/
    std::unique_ptr<IPhase> LoggedMatch::get_current_phase(void)
    {
        auto internal_ptr = (_wrapped_match->get_current_phase()).release();
        return std::unique_ptr<IPhase> (new LoggedPhase(*internal_ptr));
    }

    std::pair<int, int> LoggedMatch::get_score(Color player) const
    {
        return _wrapped_match->get_score(player);
    }

    bool LoggedMatch::is_game_over(void) const
    {
        return _wrapped_match->is_game_over();
    }

    void LoggedMatch::next_phase(void)
    {
        _wrapped_match->next_phase();
    }

    void LoggedMatch::on_phase_action(void)
    {
        _wrapped_match->on_phase_action();
    }

    void LoggedMatch::on_phase_end(const LoggedPhase& logged_phase)
    {
        auto history = logged_phase.get_history();
        this->_match_log.push_back(history);
    }
}
