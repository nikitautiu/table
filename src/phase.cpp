#include "phase.hpp"
#include "dice.hpp"
#include "game_core.hpp"

namespace table
{
/*******************************************************************************
                            CLASA IPHASE
*******************************************************************************/
    IPhase::IPhase(void) :
        _current_state(),
        _phase_type(),
        _dice_obligation(),
        _current_player(),
        _current_dices(),
        _legal_moves(),
        _win_outcome(std::make_pair(NOT_WON_STRING, Color::WHITE)),
        _board_process_func()
    {
    }

    BoardState IPhase::get_current_board_state(void) const
    {
        return _current_state;
    }

    PhaseType IPhase::get_phase_type(void) const
    {
        return _phase_type;
    }

    DiceObligation IPhase::get_dice_obligation(void) const
    {
        return _dice_obligation;
    }

    Color IPhase::get_current_player(void) const
    {
        return _current_player;
    }

    DicePair IPhase::get_current_dices(void) const
    {
        return _current_dices;
    }

    const std::set<Turn>& IPhase::get_legal_moves(void) const
    {
        return _legal_moves;
    }

    WinPair IPhase::get_win_outcome(void) const
    {
        return _win_outcome;
    }

    void IPhase::roll_dice(void)
    {
        // implemntarea implicita a functie dice roll
        // A se chema din implementarile derivate

        if(_win_outcome.first != NOT_WON_STRING)
            throw std::runtime_error("Dices can not be rolled after the round is over");
        if(_dice_obligation == DiceObligation::CAN_NOT_ROLL)
            throw std::runtime_error("The dices can not be rolled");
        _current_dices = double_dice_roll();
    }

    void IPhase::preset_roll_dice(DicePair dice_pair)
    {
        _current_dices = dice_pair;
    }

    void IPhase::submit_moves(Turn moves)
    {
        // A se chema din implementarile derivate
        if(_win_outcome.first != "not_won")
            throw std::runtime_error("Can not move after the round has ended");
        if(_phase_type == PhaseType::OPENING_ROLL)
            throw std::runtime_error("Can not move during the opening roll");
        if(_legal_moves.find(moves) == _legal_moves.end())
            throw std::runtime_error("This is not a valid move");
    }

    std::function<BoardState(BoardState, Turn)> IPhase::get_board_processing_function(void) const
    {
        return _board_process_func;
    }

/*******************************************************************************
                            CLASA PHASEVIEW
*******************************************************************************/
    PhaseView::PhaseView(IPhase& phase, IMatch& match) : _wrapped_phase(&phase), _observer(&match)
    {
    }

    BoardState PhaseView::get_current_board_state(void) const
    {

        return _wrapped_phase->get_current_board_state();
    }

    PhaseType PhaseView::get_phase_type(void) const
    {
        return _wrapped_phase->get_phase_type();
    }

    DiceObligation PhaseView::get_dice_obligation(void) const
    {
        return _wrapped_phase->get_dice_obligation();
    }

    Color PhaseView::get_current_player(void) const
    {
        return _wrapped_phase->get_current_player();
    }

    DicePair PhaseView::get_current_dices(void) const
    {
        return _wrapped_phase->get_current_dices();
    }

    const std::set<Turn>& PhaseView::get_legal_moves(void) const
    {
        return _wrapped_phase->get_legal_moves();
    }

    WinPair PhaseView::get_win_outcome(void) const
    {
        return _wrapped_phase->get_win_outcome();
    }

    void PhaseView::roll_dice(void)
    {
        _wrapped_phase->roll_dice();
        _observer->on_phase_action();
    }

    void PhaseView::submit_moves(Turn moves)
    {
        _wrapped_phase->submit_moves(moves);
        _observer->on_phase_action();
    }

    std::function<BoardState(BoardState, Turn)> PhaseView::get_board_processing_function(void) const
    {
        return _wrapped_phase->get_board_processing_function();
    }
}
