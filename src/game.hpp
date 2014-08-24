#ifndef core_hpp_guard
#define core_hpp_guard

#include <cstdint>
#include <array>
#include <utility>

namespace table {
    const int NUM_POINTS = 24;
    const int NUM_CHECKERS_PER_PLAYER = 15;

    enum class Color : int8_t {
        WHITE = -1, BLACK = 1
    };

    struct Point {
        Color color;
        int number;

        Point(Color, int);

        Point& operator+=(int);
        Point& operator-=(int);
        Point& operator++(void);
        Point operator++(int);
        Point& operator--(void);
        Point operator--(int);
    };

    class Board {
    private:
        std::array <int, NUM_POINTS> points;
        Color current_player;
        std::array <unsigned int, 2> done;
        std::array <unsigned int, 2> out;

        pair <int, int> current_dice;
        bool starting_phase;
        vector <int> remaining_moves;
    public:
        Board(void);
        Board(const Board&);
        Board operator=(const Board&);

        bool is_won(void) const {
            return this->is_game_won;
        }

        Color get_winner(void) const {
            if(done[0] == 0 and out[0] == 0)
                return Color::WHITE;
            else if(done[1] == 0 and out[1])
                return Color::BLACK;
        }

        int get_out(Color color) const {
            int poz = (color ==  Color::WHITE ? 0 : 1);
            return out[poz];// vezi cate-s scoase
        }

        int get_done(Color color) const {
            int poz = (color ==  Color::WHITE ? 0 : 1);
            return done[poz];// vezi cate-s iesite
        }

        void roll_dice(void);
        pair <int, int> get_dice(void) const;

        bool is_move_legal(int, int) const; // verifica daca se poate muta de pe o pozitie cu cateva mutari in fata
        bool move_checker(int, int); // se muta. parametrii identici. returneaza fals si nu muta daca mutarea e ilegala
        std::vector <int> get_remaining_moves(void) const;
        std::vector <pair <int, int>> get_legal_moves(void) const; // returneaza perechi (pozitie, mutare)
    };
}

#endif
