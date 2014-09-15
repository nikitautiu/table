#include "rules_ro.hpp"
#include "../game_core.hpp"
#include "../phase.hpp"

namespace table
{
    namespace internal
    {
        RoDiceHelper::RoDiceHelper(Color player)
        {

        }

        void RoDiceHelper::give_dice(DicePair)
        {

        }

        bool RoDiceHelper::is_done(void) const
        {

        }

        Color RoDiceHelper::get_winner(void) const
        {

        }

        std::pair<bool, DicePair> RoDiceHelper::get_double_pair(void) const
        {

        }
    }

/*******************************************************************************
                            CLASA ROMATCH
*******************************************************************************/
    RoMatch::RoMatch(int rounds_to_win, bool with_technical) :
        IMatch(),
        _num_rounds_to_win(rounds_to_win),
        _with_technical(with_technical),
        _opening_roll_phase(new RoOpeningRollPhase(Color::WHITE)),
        _game_phase()
    {
        _current_phase = _opening_roll_phase.get();
    }


    void RoMatch::next_phase(void)
    {
        IMatch::next_phase(); // se cheama implementare implicita
        // daca a trecut de pasul anterior inseamna ca se poate trece la urmatoarea faza


        auto starting_player = (_current_phase->get_win_outcome()).second;
        if(_current_phase->get_phase_type() == PhaseType::OPENING_ROLL)
        {
            auto win_type = (_current_phase->get_win_outcome()).first;
            if(win_type == "double")
            {
                auto starting_pair = _opening_roll_phase->get_starting_dices();
                _game_phase.reset(new RoGamePhase(starting_player, starting_pair)); // cu dubla de inceput
            }
            else
                _game_phase.reset(new RoGamePhase(starting_player)); // fara dubla de inceput
            _opening_roll_phase.reset();
        }
        else
            _game_phase.reset(new RoGamePhase(starting_player)); // se incepe cu castigatorul
        _current_phase = static_cast<IPhase*> (_game_phase.get()); // type-safe cast
    }

    void RoMatch::on_phase_action(void)
    {
        // TODO: De implemntat. Deocamdata ii numa ca sa se evite erorile
    }

/*******************************************************************************
                            CLASA ROOPENINGROLLPHASE
*******************************************************************************/
    RoOpeningRollPhase::RoOpeningRollPhase(Color starting_player) :
        IPhase(),
        _dice_helper(starting_player)
    {
        _phase_type = PhaseType::OPENING_ROLL;
        _current_player = starting_player;
    }

    void RoOpeningRollPhase::roll_dice(void)
    {
        IPhase::roll_dice();
        _dice_helper.give_dice(_current_dices);
        if(_dice_helper.is_done())
        {
            auto win_type_string = std::string(_dice_helper.get_double_pair().first ? "double" : "normal"); //verifica pt dubla
            _win_outcome = std::make_pair(win_type_string, _dice_helper.get_winner());
        }
        _starting_dice_pair = _dice_helper.get_double_pair().second;

    }

    DicePair RoOpeningRollPhase::get_starting_dices(void) const
    {
        if(_win_outcome.first != "double")
            throw std::runtime_error("There hasn't been a double");
        return _starting_dice_pair;
    }

/*******************************************************************************
                            CLASA ROGAMEPHASE
*******************************************************************************/
    RoGamePhase::RoGamePhase(Color starting_player, DicePair starting_double) :
        IPhase()
    {

    }

    void RoGamePhase::roll_dice(void)
    {

    }

    void RoGamePhase::submit_moves(Turn moves)
    {

    }
}
