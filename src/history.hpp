#ifndef history_hpp_guard
#define history_hpp_guard

#include "match.hpp"
#include "phase.hpp"
#include <vector>

namespace table
{
/*******************************************************************************
                            CLASA PHASE HISTORY
*******************************************************************************/

    class LoggedPhase;
    class LoggedMatch;

    struct HistoryElement;

    typedef std::vector<HistoryElement> History;
    typedef std::vector<History> MatchLog;

    struct HistoryElement {
        DicePair dices;
        Turn turn;
        Color player;
    };

    class LoggedPhase : public IPhase
    {
        // clasa wrapper PhaseHistory
        // salveaza toate starile unui match in obiectul history
        private:
            //TODO: add string in history
            IPhase* _wrapped_phase;
            LoggedMatch* _observer; // este anuntat cand se termina partida ( primeste informatii )
            History _history;
        public:
            LoggedPhase(IPhase&);

            //GETTERS
            virtual BoardState get_current_board_state(void) const override;
            virtual PhaseType get_phase_type(void) const override;
            virtual DiceObligation get_dice_obligation(void) const override;
            virtual Color get_current_player(void) const override;
            virtual DicePair get_current_dices(void) const override;
            virtual const std::set<Turn>& get_legal_moves(void) const override;
            virtual WinPair get_win_outcome(void) const override;
            //END GETTERS

            virtual void roll_dice(void) override;
            virtual void submit_moves(Turn) override; // updateaza istoricul si
                                                      // daca este sfarsitul liniei cheama on_phase_end() din LoggedPhase

            History get_history(void) const; // getter ( returns _history )
    };

    class LoggedMatch : public IMatch
    {
        // clasa wrapper LoggedMatch
        // salveaza mai multe linii sub forma de LoggedPhase
        private:
            IMatch* _wrapped_match;
            MatchLog _match_log;
        public:
            LoggedMatch(IMatch&);

            virtual std::unique_ptr<IPhase> get_current_phase(void); // returneaza o noua faza de joc
            virtual std::pair<int, int> get_score(Color) const override; // returneaza o perche a scorurilor cu culoare primita ca prima valoare
            virtual bool is_game_over(void) const override; // returneaza daca s-a terminat partida

            virtual void next_phase(void) override;      // trece la urmatoarea faza a jocului
            virtual void on_phase_action(void) override; // chemat de fiecare daca cand se face o modificare la faza curenta

            void on_phase_end(const LoggedPhase&);  // updater-ul clase LoggedMatch ( se apeleaza la sfarsitul unei linii )
    };

}

#endif // history_hpp_guard
