#ifndef rules_hpp_guard
#define rules_hpp_guard

#include <cstdint>
#include <set>
#include "game_core.hpp"

namespace table {
    enum class WinType : int8_t {
        NOT_WON, NORMAL_WIN, TECHNICAL_WIN
    }; // tipuri de castig, none daca nu s-a castigat

    using WinerWinPair = std::pair <WinType, Color>; // pereche tip de victorie/invingator

    BoardState process_board(BoardState, Turn); // face mutarile pe un board
    std::set <Turn> get_legal_moves(const BoardState&, Color, DicePair); // returneaza un set cu toate mutarile legale pt o tabla, un jucator si un set de zaruri
    WinerWinPair get_win_outcome(const BoardState&); // retunreaza o pereche cu tipul de victori si castigator. tip = NOT_WON daca nu s-a castigat inca
}

#endif
