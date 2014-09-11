#ifndef match_hpp_guard
#define match_hpp_guard

#include <cstdint>
#include <memory>
#include "game_core.hpp"
#include "phase.hpp"

namespace table
{
    class IMatch
    {
        // interfata IMatch
        // Interfata pe a carei specificatie se bazeaza toate restul claselor
    private:
        std::array<int, 2> _score;
    protected:
        // detalii de implementare, clasele care mostenesc sa vor folosi de el

        std::unique_ptr<IPhase> _current_phase;
        bool _game_is_over;
        void _set_score(Color, int); // folosita de mostenitori ca sa actualizeze scorul
    public:
        Match(void); // constructor vid
        Match(const Match&); // constructor de copiere
        Match& operator=(Match); // operator de copiere
        // se vor putea adauga ulterior constructori care permit creearea personalizata cu reguli diferite(ex. pana la cat se joaca)

        PhaseView get_current_phase(void); // returneaza o noua faza de joc
        std::pair<int, int> get_score(Color) const; // returneaza o perche a scorurilor cu culoare primita ca prima valoare
        bool is_game_over(void) const; // retunreaza daca s-a terminat partida

        virtual void next_phase(void) = 0; // trece la urmatoarea faza a jocului
        virtual void on_phase_action(void) = 0; // chemat de fiecare daca cand se face o modificare la faza curenta
    };

}
#endif