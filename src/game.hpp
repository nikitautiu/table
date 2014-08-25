#ifndef core_hpp_guard
#define core_hpp_guard

#include <cstdint>
#include <array>
#include <utility>

namespace table {
    const int NUM_POINTS = 24;
    const int NUM_CHECKERS_PER_PLAYER = 15;

    enum class Color : int8_t {
        // tipurile de table/jucatori
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
        std::array <Point, NUM_POINTS> points;
        Color current_player;
        std::array <unsigned int, 2> done;
        std::array <unsigned int, 2> out;

        pair <int, int> current_dice;
        bool starting_phase;
        vector <int> remaining_moves;
    public:
        Board(void); // constructor inplicit
        Board(const Board&); // constructor copiere
        Board operator=(const Board&); // operator copiere

        bool is_won(void) const {
            // zice daca ii gata partida
            return this->is_game_won;
        }

        Color get_winner(void) const {
            // daca ii gata partida, returneaza castigatorul
            if(done[0] == 0 and out[0] == 0)
                return Color::WHITE;
            else if(done[1] == 0 and out[1])
                return Color::BLACK;
        }

        int get_out(Color color) const {
            // primeste culoare si returneaza cate scoase de culoara aia is
            int poz = (color ==  Color::WHITE ? 0 : 1);
            return out[poz];
        }

        int get_done(Color color) const {
            // primeste culoare si returneaza cate de culoarea aia o terminat
            int poz = (color ==  Color::WHITE ? 0 : 1);
            return done[poz];
        }

        void roll_dice(void);
        pair <int, int> get_dice(void) const;

        const array <Point, NUM_POINTS> get_tabla(void) const {
            // returneaza reprezentarea tablei
            return this->points;
        }

        bool is_move_legal(int, int) const; // verifica daca se poate muta de pe o pozitie cu cateva mutari in fata
        bool move_checker(int, int); // se muta. parametrii identici. returneaza fals si nu muta daca mutarea e ilegala
        std::vector <int> get_remaining_moves(void) const;
        std::vector <pair <int, int>> get_legal_moves(void) const; // returneaza perechi (pozitie, mutare)
    };
}

#endif