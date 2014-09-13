#include "rules.hpp"
#include "game_core.hpp"

#include <set>

namespace table {
        namespace internal {

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
        }


    BoardState process_board(BoardState old_board, Turn moves) {
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


    WinPair get_win_outcome(const BoardState& board) {
        if(board.get_done(Color::BLACK) == NUM_CHECKERS_PER_PLAYER)
            return std::make_pair(std::string("normal"), Color::BLACK);
        if(board.get_done(Color::WHITE) == NUM_CHECKERS_PER_PLAYER)
            return std::make_pair(std::string("normal"), Color::WHITE);
        if(internal::check_for_technical(board, Color::BLACK))
            return std::make_pair(std::string("technical"), Color::BLACK);
        if(internal::check_for_technical(board, Color::WHITE))
            return std::make_pair(std::string("technical"), Color::WHITE);
        return std::make_pair(std::string("not_won"), Color::WHITE); // culoarea nu conteaza
    }


    std::set <Turn> get_legal_moves(const BoardState& board, Color color, DicePair dices) {
        auto turn_computer = internal::TurnGenerator();
        return turn_computer.compute_legal_moves(board, color, dices);
    }
}
