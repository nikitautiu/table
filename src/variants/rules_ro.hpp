#ifndef rulesro_hpp_guard
#define rulesro_hpp_guard

#include "../game_core.hpp"
#include "../match.hpp"
#include "../phase.hpp"

namespace table
{
    class RoMatch : public IMatch
    {
    private:
        int _num_rounds_to_win;
        bool _with_technical;
    public:
        RoMatch(int, bool);

        virtual void next_phase(void) override;
        virtual void on_phase_action(void) override;
    };


    class RoGamePhase : public IPhase
    {
    public:
        RoGamePhase(Color, DicePair); // creeaza o linie cu un player care incepe si un posibil zar de inceput

        virtual void roll_dice(void) override;
        virtual void submit_moves(Turn) override;
    };

    class RoOpeningRollPhase : public IPhase
    {
    public:
        RoOpeningRollPhase(Color); // creaza o faza de inceput cu un player care sa arunce primul

        virtual void roll_dice(void) override;
    };
}
#endif
