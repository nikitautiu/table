#ifndef phase_hpp_guard
#define phase_hpp_guard

#include <cstdint>
#include "game_core.hpp"

namespace table
{
    enum class PhaseType : int8_t
    {
        // enum MatchPhase
        // Specifica faza curenta a partidei(inceput, runda sau finalizata)
        // OPENING_ROLL = se poate doar da cu zarul, nu muta
        // GAME_PHASE = se poate si da cu zarul si muta
        // GAME_END = partida a luat sfarsit
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

    public:
        IPhase(void); // constructor vid
        IPhase(const IPhase&); // constructor de copiere          TODO: DE IMPLEMENTAT
        IPhase& operator=(IPhase); // operator de copiere

        BoardState get_current_board_state(void) const; // returneaza starea curenta a tablei
        PhaseType get_phase_type(void) const; // returneaza un TypePhase cu tipul fazei
        DiceObligation get_dice_obligation(void) const; // returneaza obligativitatea aruncarii zarului
        Color get_current_player(void) const; // returneaza playerul curent
        DicePair get_current_dice_pair(void) const; // returneaza zarurile aruncate
        const std::set<Turn>& get_legal_moves(void) const; // retunreaza mutarile care se pot face;
        WinPair get_win_outcome(void) const; // returneaza starea de victorie(tipul victoriei/castigatorul)
                                             // Daca nu a castigat nimeni, "first" este egal cu not_won

        virtual void roll_dice(void) = 0; // alea iacta est
        virtual void submit_moves(Turn) = 0; // Primeste o serie de mutari, daca sunt invalide, exceptie, daca nu, le efectueaza
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
        PhaseView(const IPhase&, const IMatch&); // constructor wrapper

        // toate restul metodelor functioneaza ca un proxy catre obiectul IPhase continut
        BoardState get_current_board_state(void) const;
        PhaseType get_phase_type(void) const;
        DiceObligation get_dice_obligation(void) const;
        Color get_current_player(void) const;
        DicePair get_current_dice_pair(void) const;
        const std::set<Turn>& get_legal_moves(void) const;
        WinPair get_win_outcome(void) const;

        void roll_dice(void);
        void submit_moves(Turn);
    };
}
#endif