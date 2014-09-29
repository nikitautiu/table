#ifndef helper_board_guard
#define helper_board_guard

#include "game_core.hpp"
#include "phase.hpp"

namespace table
{
/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    class HelperBoard
    {
    private:
        BoardState _initial_board_state; // asta se initializeaza din bagamon.
        BoardState _current_board_state; // dupa modificari
        Color _player; // playeru care face mutaorile
        DicePair _dices; // zarurile cu care se lucreaza
        Turn _history;   // se pusheaza aici toate mutarile ( first = poz.init, second = nr mutari )
        std::multiset<int> _remaining_moves; // mutarile ramase cu care se lucreaza

        const std::set <Turn> *_valid_moves; // pointer catre mutarile valide din Round
        std::function <BoardState(BoardState, Turn)> _board_process_func; // functie pt facut mutarile partiale

        HelperBoard(void);
        void _init_from_board(const IPhase&); // initialieaza dintr-un iphase
    public:
        // clasa pe care poti face mutari, da undo, verifica legalitatea lor etc

        HelperBoard(const IPhase&); // initializeaza o tabla temporara din clasa de joc
        HelperBoard(const HelperBoard&); // constructor copiere
        HelperBoard& operator=(HelperBoard); // operator copiere

        BoardState get_board_state(void) const; // getter
        Color get_current_player(void) const; // getter
        Turn get_turn(void) const; // returneaza mutarile de pana acuma
        void push_move(CheckerMove); // face o mutare. daca ilegala, arunca exceptie
        void pop_move(void); // da undo la ultima mutare

        const std::set <Turn>& get_legal_moves(void) const;
        std::set<CheckerMove> get_immediately_legal_moves(void) const; // returneaza mutarile de cate o pula imediat legale(prima data cele obligatorii)
        std::multiset<int> get_remaining_moves(void) const; // returneaza mutarile ramase
        bool is_turn_done(void) const; // verifica daca s-a facut o tura completa legala
    };
}

#endif
