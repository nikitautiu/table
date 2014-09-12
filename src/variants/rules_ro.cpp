#include "rules_ro.hpp"
#include "../game_core.hpp"
#include "../phase.hpp"

namespace table
{
/*******************************************************************************
                            CLASA ROMATCH
*******************************************************************************/
    RoMatch::RoMatch(int rounds_to_win=3, bool with_technical=true) :
        IMatch(),
        _num_rounds_to_win(rounds_to_win),
        _with_technical(with_technical)
    {
        _current_phase.reset(new RoOpeningRollPhase(Color::WHITE)); // noua faza de joc
    }

    void RoMatch::next_phase(void)
    {
        IMatch::next_phase(); // se cheama implementare implicita
        // de implementat restu
    }

    void RoMatch::on_phase_action(void)
    {
        // TODO: De implemntat. Deocamdata ii numa ca sa se evite erorile
    }

/*******************************************************************************
                            CLASA ROOPENINGROLLPHASE
*******************************************************************************/
    RoOpeningRollPhase::RoOpeningRollPhase(Color starting_player) : IPhase()
    {
        _phase_type = PhaseType::OPENING_ROLL;
        _current_player = starting_player;
    }

    void RoOpeningRollPhase::roll_dice(void)
    {
        IPhase::roll_dice();
    }
}
