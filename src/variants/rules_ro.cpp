#include "rules_ro.hpp"
#include "../game_core.hpp"
#include "../phase.hpp"

namespace table
{
    BoardState process_board(BoardState old_board, Turn moves) {
        // face  un set de mutari fie ele valide sau nu si returneaza BoardState-ul la final
        for(const auto checker_move : moves) {
            auto moved_color = Color();
            if(checker_move.first == -1 || checker_move.first == NUM_POINTS)
                moved_color = (checker_move.first == -1 ? Color::WHITE : Color::BLACK); // daca baga la loc, vezi ce culoare ii
            else {
                moved_color = old_board.points[checker_move.first].color;
                --old_board.points[checker_move.first];
            }

            auto next_position = checker_move.first + checker_move.second;
            if(next_position < 0 || next_position >= NUM_POINTS) {
                // daca iese de pe table
                auto old_done = old_board.get_done(moved_color);
                old_board.set_done(moved_color, old_done + 1);
            }
            else {
                if(old_board.points[next_position].number != 0) {
                    // scoate un pool
                    auto out_color = old_board.points[next_position].color;
                    auto old_out = old_board.get_out(out_color);
                    old_board.set_out(out_color, old_out + 1);
                    old_board.points[next_position] = Point(moved_color, 0);
                }
                ++old_board.points[next_position];
            }
        }
        return old_board;
    }

    namespace internal
    {
/*******************************************************************************
                            IMPLEMENTARE REGULI
*******************************************************************************/
        class TurnGenerator {
            private:
                size_t max_len;
                std::set <Turn> legal_moves;
                Turn current_turn;
                Color current_player;

                void do_backtracking(const BoardState&, std::multiset <int>);
                void purge_moves(void); // remov all less than max_len long moves
            public:
                std::set <Turn> compute_legal_moves(const BoardState&, Color, DicePair);
        };


        BoardState reverse_points(const BoardState& board) {
            PointArray rpoints;
            for (int i = 0; i < NUM_POINTS; ++i)
                rpoints[NUM_POINTS-i-1] = board.points[i];
            BoardState rval;
            rval.points = rpoints;
            return rval;
        }


        bool can_extract(const BoardState& board, Color player) {

            if ( board.get_out(player) ) return false;

            int starting_pos = board.get_starting_pos(player);
            int move_sign = board.get_move_sign(player);
            int finish_pos = board.get_starting_pos(-player);

            for (int i = starting_pos; i != finish_pos - ( 5 * move_sign ); i += move_sign)
                if ( board.points[i].number && board.points[i].color == player ) return false;

            return true;
        }

        // detalii de implementare(utilizatorul bibliotecii nu trebuie sa le vada)
        bool check_for_technical(const BoardState& board, Color player) {
            int house_start_pos = BoardState::get_starting_pos(-player),
                sign = -BoardState::get_move_sign(player);
            for(int delta = 0; delta < 8; ++delta) {
                int current_pos = house_start_pos + delta * sign;
                if(board.points[current_pos].color != player) {
                    return false; // nu-s de culoarea care trebuie
                }
                if(delta > 0 && !(board.points[current_pos].number == board.points[current_pos - sign].number &&
                                  (board.points[current_pos].number == 2 || board.points[current_pos].number == 1))) {
                    return false; // nu e un rand de 2 sau 1
                }
            }
            return true;
        }

        std::set <CheckerMove> get_possible_moves(const BoardState& board, Color player, size_t move_dist) {
            std::set<CheckerMove> rval;

            int sp = board.get_starting_pos(player);
            int ms = board.get_move_sign(player);

            if (board.get_out(player)) {
                auto pr = sp - ms + ( ms * move_dist ); // pozitia de reintrare pe tabla
                if ( board.points[pr].number >= 2 && board.points[pr].color != player )
                    return std::set<CheckerMove> {}; // set vid, fiindca e ocupata pozitia pe care se intra
                else
                    return std::set<CheckerMove> { std::make_pair(sp - ms, ms * move_dist) };
            }

            auto all_in_house = can_extract(board, player); // verifica daca se poate incepe sa se scoata
            for (int i = 0; i < NUM_POINTS; ++i) {
                auto point = board.points[i];
                auto ep = i + (ms * (int)move_dist);

                if ( point.color == player )
                if ((!(ep < NUM_POINTS && ep >= 0) && all_in_house)                                                              // (daca punctul de aterizare nu e in intervalul 0, 23 SI se poate scoate)
                    || ((ep < NUM_POINTS && ep >= 0) && ((board.points[ep].color != player && board.points[ep].number < 2)       // SAU (e in interval SI ((sunt mai putin de 2 piese de culoare opusa)
                                                         || board.points[ep].color == player)))                                  //                        SAU (se aterizeaza pe aceasi culoare))),
                    rval.insert(std::make_pair(i, (int)move_dist * ms));                                                         // se insereaza mutare valida.
            }
            return rval;
        }

        std::set <Turn> TurnGenerator::compute_legal_moves(const BoardState& board, Color color, DicePair dices) {
            current_player = color;
            current_turn = Turn();
            max_len = 0;

            std::multiset <int> moves; // populate moves
            if ( dices.first == dices.second )
                for (int i = 0; i < 4; ++i)
                    moves.insert(dices.first);
            else
                moves.insert(dices.first),
                moves.insert(dices.second);

            do_backtracking(board, moves);
            purge_moves();

            return legal_moves;
        }

        void TurnGenerator::purge_moves(void) {
            auto it = std::begin(legal_moves);
            while(it != std::end(legal_moves)) {
                if(it->size() < max_len)
                    it = legal_moves.erase(it);
                else
                    ++it;
            }
        }

        void TurnGenerator::do_backtracking(const BoardState& current_state, std::multiset <int> remaining_moves) {
            auto unique_moves = std::set <int>(std::begin(remaining_moves), std::end(remaining_moves)); // se iau mutarile distincte
            auto can_move = false;

            for(auto move_dist : unique_moves) {
                auto possible_moves = get_possible_moves(current_state, current_player, move_dist); // gaseste toate mutarile care se pot face

                auto new_remaining_moves = std::multiset <int> (remaining_moves);
                new_remaining_moves.erase(move_dist); // se calculeaza noile mutari ramase
                for(auto move : possible_moves) {
                    can_move = true; // s-a putut face cel putin o mutare

                    current_turn.push_back(move);
                    auto new_board_state = process_board(current_state, Turn({move})); // se execut a mutarile
                    do_backtracking(new_board_state, new_remaining_moves); // se intra in recursie
                    current_turn.pop_back(); // se anuleaza modificarile facute
                }
            }
            if(!can_move) {
                legal_moves.insert(current_turn); // daca nu se mai poate muta, introdu mutarile curente
                max_len = std::max(max_len, current_turn.size()); // se recalculeaza valoare maxima
            }
        }


        WinPair get_win_outcome(const BoardState& board) {
            if(board.get_done(Color::BLACK) == NUM_CHECKERS_PER_PLAYER)
                return std::make_pair(std::string("normal"), Color::BLACK);
            if(board.get_done(Color::WHITE) == NUM_CHECKERS_PER_PLAYER)
                return std::make_pair(std::string("normal"), Color::WHITE);
            if(internal::check_for_technical(board, Color::BLACK))
                return std::make_pair(std::string("technical"), Color::BLACK);
            if(internal::check_for_technical(board, Color::WHITE))
                return std::make_pair(std::string("technical"), Color::WHITE);
            return std::make_pair(NOT_WON_STRING, Color::WHITE); // culoarea nu conteaza
        }


        std::set <Turn> get_legal_moves(const BoardState& board, Color color, DicePair dices) {
            auto turn_computer = internal::TurnGenerator();
            return turn_computer.compute_legal_moves(board, color, dices);
        }

/*******************************************************************************
                            CLASA RODICEHELPER
*******************************************************************************/
        RoDiceHelper::RoDiceHelper(Color player) : _player(player),
                                                   _winner(),
                                                   _dices(std::make_pair(0, 0)),
                                                   _is_done(false)
        {
        }

        void RoDiceHelper::init(Color next_player)
        {
            _player = next_player;
            _dices = std::make_pair(0, 0);
            _is_done = false;
        }

        void RoDiceHelper::give_dice(DicePair dice_pair)
        {
            if ( _dices.first == 0 && _dices.second == 0 ) // daca este primul zar primit nu se intampla mare lucru
                _dices = dice_pair;
            else
            {
                if ( (dice_pair.first + dice_pair.second) == (_dices.first + _dices.second) ) // daca suma este egala
                {
                    if ( DiceUtils::DiceIsDouble(dice_pair) != get_double_pair().first ) // daca unul dintre zaruri e dubla
                    {
                        _is_done = true; // sigur va castiga cineva
                        if ( DiceUtils::DiceIsDouble(dice_pair) )
                            _winner = -_player;
                        else
                            _winner = _player;
                        return;
                    }
                    else // daca suma este egala si niciunul dintre zaruri nu e dubla atunci nu castiga nimeni si se da din nou
                    {
                        init(-_player);
                        return;
                    }
                }

                if ( (dice_pair.first + dice_pair.second) < (_dices.first + _dices.second) )
                {
                    _is_done = true;
                    _winner = _player;
                }
                else
                {
                    _is_done = true;
                    _winner = -_player;
                }
            }
            _player = -_player;
        }

        bool RoDiceHelper::is_done(void) const
        {
            if ( _is_done )
                return true;
            return false;
        }

        Color RoDiceHelper::get_winner(void) const
        {
            if ( !is_done() )
                throw std::runtime_error("No winner yet.");
            return _winner;
        }

        std::pair<bool, DicePair> RoDiceHelper::get_double_pair(void) const
        {
            if ( _dices.first != _dices.second )
                return std::make_pair(false, DicePair(0, 0));
            return std::make_pair(true, _dices);
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
                auto starting_pair = _opening_roll_phase->get_starting_double();
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
        if(_current_phase->get_win_outcome().first != "not_won")
        {
            auto old_score = get_score(_current_phase->get_win_outcome().second).first;
            _set_score(_current_phase->get_win_outcome().second, old_score + 1);
        }
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

    void RoOpeningRollPhase::preset_roll_dice(DicePair dice_pair)
    {
        IPhase::_current_dices = dice_pair;
        _process_dices();
    }

    void RoOpeningRollPhase::roll_dice(void)
    {
        IPhase::roll_dice();
        _process_dices();
    }

    DicePair RoOpeningRollPhase::get_starting_double(void) const
    {
        if(_win_outcome.first != "double")
            throw std::runtime_error("There hasn't been a double");
        return _starting_dice_pair;
    }

    void RoOpeningRollPhase::_process_dices()
    {
        _dice_helper.give_dice(_current_dices);
        if(_dice_helper.is_done())
        {
            auto win_type_string = std::string(_dice_helper.get_double_pair().first ? "double" : "normal"); //verifica pt dubla
            _win_outcome = std::make_pair(win_type_string, _dice_helper.get_winner());
            _starting_dice_pair = _dice_helper.get_double_pair().second;
        }
    }

/*******************************************************************************
                            CLASA ROGAMEPHASE
*******************************************************************************/
    RoGamePhase::RoGamePhase(Color starting_player, DicePair starting_double) :
        IPhase()
    {
        _phase_type = PhaseType::GAME_PHASE;
        _board_process_func = process_board;
        _current_player = starting_player;

        if(starting_double != DicePair(0, 0))
        {
            // cu dubla de inceput
            _dice_obligation = DiceObligation::CAN_NOT_ROLL;
            _current_dices = starting_double;
        }
        else
            _dice_obligation = DiceObligation::MUST_ROLL;

        _init_board_state();
    }

    RoGamePhase::RoGamePhase(const BoardState& state, Color player, DicePair dices) :
        IPhase()
    {
        _phase_type = PhaseType::GAME_PHASE;
        _board_process_func = process_board;
        _current_player = player;
        _current_state = state;

        if(dices != DicePair(0, 0))
        {
            _dice_obligation = DiceObligation::CAN_NOT_ROLL;
            _current_dices = dices;
        }
        else
            _dice_obligation = DiceObligation::MUST_ROLL;

        _compute_legal_moves();
        _win_outcome = internal::get_win_outcome(_current_state);
    }


    void RoGamePhase::_init_board_state(void)
    {
        auto& points = _current_state.points;

        points[0]  = Point(Color::WHITE, 2), points[NUM_POINTS-1]  = Point(Color::BLACK, 2);
        points[5]  = Point(Color::WHITE, 5), points[NUM_POINTS-6]  = Point(Color::BLACK, 5);
        points[7]  = Point(Color::WHITE, 3), points[NUM_POINTS-8]  = Point(Color::BLACK, 3);
        points[12] = Point(Color::WHITE, 5), points[NUM_POINTS-13] = Point(Color::BLACK, 5);
    }

    void RoGamePhase::_compute_legal_moves(void)
    {
        auto turn_computer = internal::TurnGenerator();
        _legal_moves = turn_computer.compute_legal_moves(_current_state, _current_player, _current_dices);
    }

    void RoGamePhase::roll_dice(void)
    {
        IPhase::roll_dice();
        _dice_obligation = DiceObligation::CAN_NOT_ROLL;
        _compute_legal_moves();
    }

    void RoGamePhase::submit_moves(Turn moves)
    {
        IPhase::submit_moves(moves);
        _current_state = process_board(_current_state, moves);
        _win_outcome = internal::get_win_outcome(_current_state);

        _current_player = -_current_player; // toggle players
        _dice_obligation = DiceObligation::MUST_ROLL;
    }
}
