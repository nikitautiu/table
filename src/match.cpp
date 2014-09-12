#include "phase.hpp"
#include "match.hpp"
#include "game_core.hpp"

namespace table
{
/*******************************************************************************
                                METODE PROTEJATE
*******************************************************************************/
    void IMatch::_set_score(Color player, int new_score)
    {
        if(player == Color::WHITE)
            _score[0] = new_score;
        else
            _score[1] = new_score;
    }

/*******************************************************************************
                                METODE PUBLICE
*******************************************************************************/
    IMatch::IMatch(void) :
        _score(),
        _current_phase(),
        _game_is_over()
    {
    }

    std::unique_ptr<IPhase> IMatch::get_current_phase(void)
    {
        return std::unique_ptr<IPhase> (new PhaseView(*(_current_phase), *this));
    }

    std::pair<int, int> IMatch::get_score(Color first_player) const
    {
        if(first_player == Color::WHITE)
            return std::make_pair(_score[0], _score[1]);
        else
            return std::make_pair(_score[1], _score[0]);
    }

    bool IMatch::is_game_over(void) const
    {
        return _game_is_over;
    }

    void IMatch::next_phase(void)
    {
        // incompleta. a se chema din metodele derivate
        if(_game_is_over)
            throw std::runtime_error("Can not progres to another phase after the match finished");
        if((_current_phase->get_win_outcome()).first == "not_won")
            throw std::runtime_error("Can not progress to another phase while the current phase is running");
    }
}
