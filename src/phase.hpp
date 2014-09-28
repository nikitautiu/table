#ifndef phase_hpp_guard
#define phase_hpp_guard

#include <cstdint>
#include <functional>
#include "game_core.hpp"
#include "match.hpp"
#include "phase.hpp"

namespace table
{
    class IMatch;

    enum class PhaseType : int8_t
    {
        // enum MatchPhase
        // Specifica faza curenta a partidei(inceput, runda sau finalizata)
        // OPENING_ROLL = se poate doar da cu zarul, nu muta
        // GAME_PHASE = se poate si da cu zarul si muta
        OPENING_ROLL, GAME_PHASE
    };

    enum class DiceObligation : int8_t
    {
        // enum DiceCompulsion
        // Specifica obligativitate aruncarii zarului
        // MUST_ROLL = zarul trebuie aruncat din nou
        // CAN_ROLL = zarul poate fi folosit in starea in care e, dar poate fi rearuncat
        // CAN_NOT_ROLL = zarul terbuie folosit ca atare
        MUST_ROLL, CAN_ROLL, CAN_NOT_ROLL
    };

    class IPhase
    {
        // interfata IMatch
        // Interfata pe a carei specificatie se bazeaza toate restul claselor
        // cu variante diferite de joc
    protected:
        BoardState _current_state;
        PhaseType _phase_type;
        DiceObligation _dice_obligation;
        Color _current_player;
        DicePair _current_dices;
        std::set<Turn> _legal_moves;
        WinPair _win_outcome;
        std::function <BoardState(BoardState, Turn)> _board_process_func;

    public:
        IPhase(void); // constructor vid
        IPhase(const IPhase&); // constructor copiere

        virtual BoardState get_current_board_state(void) const; // returneaza starea curenta a tablei
        virtual PhaseType get_phase_type(void) const; // returneaza un TypePhase cu tipul fazei
        virtual DiceObligation get_dice_obligation(void) const; // returneaza obligativitatea aruncarii zarului
        virtual Color get_current_player(void) const; // returneaza playerul curent
        virtual DicePair get_current_dices(void) const; // returneaza zarurile aruncate
        virtual const std::set<Turn>& get_legal_moves(void) const; // retunreaza mutarile care se pot face;
        virtual WinPair get_win_outcome(void) const; // returneaza starea de victorie(tipul victoriei/castigatorul)
                                             // Daca nu a castigat nimeni, "first" este egal cu not_won

        virtual void roll_dice(void) = 0; // alea iacta est
        virtual void submit_moves(Turn); // Primeste o serie de mutari, daca sunt invalide, exceptie, daca nu, le efectueaza

        virtual std::function<BoardState(BoardState, Turn)> get_board_processing_function(void) const; // returneaz funcita de procesare a tablelor
    };

    class PhaseView : public IPhase
    {
        // clasa wrapper ce primeste un IPhase la constructie si poate fi ulterior
        // subscrisa la un obiect de tip IMatch. Actioneaza ca un proxy pt obiectul
        // IPhase pe care il contine si in acelasi timp anunt IMatch-ul cand se intampla
        // orice schimbare(mutare, aruncare zar, castig etc.). Acesta din urma poate
        // chema getteri pt a vedea schimbarea

    private:
        IPhase* _wrapped_phase;
        IMatch* _observer;



    public:
        PhaseView(IPhase&, IMatch&); // constructor wrapper

        PhaseView(void) = delete;                // FACUTI
        PhaseView(const IPhase&) = delete;       // INACCESIBILI

        // toate restul metodelor functioneaza ca un proxy catre obiectul IPhase continut
        virtual BoardState get_current_board_state(void) const override;
        virtual PhaseType get_phase_type(void) const override;
        virtual DiceObligation get_dice_obligation(void) const override;
        virtual Color get_current_player(void) const override;
        virtual DicePair get_current_dices(void) const override;
        virtual const std::set<Turn>& get_legal_moves(void) const override;
        virtual WinPair get_win_outcome(void) const override;

        virtual void roll_dice(void) override;
        virtual void submit_moves(Turn) override;

        virtual std::function<BoardState(BoardState, Turn)> get_board_processing_function(void) const override;
    };
}
#endif
