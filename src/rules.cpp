#include "rules.hpp"
#include "game.hpp"
namespace table {
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

    bool check_for_technical(const BoardState& board, Color player) {
        int house_start_pos = (player == Color::BLACK ? 0 : NUM_POINTS - 1),
            sign = (player == Color::BLACK ? 1 : -1);
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

    WinerWinPair get_win_outcome(const BoardState& board) {
        if(board.get_done(Color::BLACK) == NUM_CHECKERS_PER_PLAYER)
            return std::make_pair(WinType::NORMAL_WIN, Color::BLACK);
        if(board.get_done(Color::WHITE) == NUM_CHECKERS_PER_PLAYER)
            return std::make_pair(WinType::NORMAL_WIN, Color::WHITE);
        if(check_for_technical(board, Color::BLACK))
            return std::make_pair(WinType::TECHNICAL_WIN, Color::BLACK);
        if(check_for_technical(board, Color::WHITE))
            return std::make_pair(WinType::TECHNICAL_WIN, Color::WHITE);
        return std::make_pair(WinType::NOT_WON, Color::WHITE); // culoarea nu conteaza
    }


    std::set <Turn> get_legal_moves(BoardState board, Color color, DicePair dices) {

    }
}
