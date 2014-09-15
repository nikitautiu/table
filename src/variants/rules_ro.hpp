#ifndef rulesro_hpp_guard
#define rulesro_hpp_guard

#include "../game_core.hpp"
#include "../match.hpp"
#include "../phase.hpp"

namespace table
{
    // FORWARD DECLARATIONS
    class RoOpeningRollPhase;
    class RoGamePhase;

    namespace internal
    {
        class RoDiceHelper
        {
        public:
            // TODO: de implementat
            RoDiceHelper(Color); // primeste playerul care incepe

            void give_dice(DicePair); // da zarurile arunctae. progreseaza algoritmul
            bool is_done(void) const; // returneaza true daca s-a castigat cineva darea cu zarul
            Color get_winner(void) const; // returneaza castigatorul
            std::pair<bool, DicePair> get_double_pair(void) const; // returneaza o perche de  tipul (bool e dubla?, DicePair daca da atunci dubla)
        };
    }

    class RoMatch : public IMatch
    {
    private:
        int _num_rounds_to_win;
        bool _with_technical;

        std::unique_ptr<RoOpeningRollPhase> _opening_roll_phase;
        std::unique_ptr<RoGamePhase> _game_phase;
    public:
        RoMatch(int, bool);

        virtual void next_phase(void) override;
        virtual void on_phase_action(void) override;
    };


    class RoGamePhase : public IPhase
    {
    public:
        RoGamePhase(Color, DicePair=DicePair(0, 0)); // creeaza o linie cu un player care incepe si un posibil zar de inceput

        virtual void roll_dice(void) override;
        virtual void submit_moves(Turn) override;
    };

    class RoOpeningRollPhase : public IPhase
    {
        // faza de inceput pt jtablele romanesti
        // are valorile de castig "not_won", "double" sau "normal"
    private:
        internal::RoDiceHelper _dice_helper;
        DicePair _starting_dice_pair;
    public:
        RoOpeningRollPhase(Color); // creaza o faza de inceput cu un player care sa arunce primul

        DicePair get_starting_dices(void) const;
        virtual void roll_dice(void) override;
    };
}
#endif
