#ifndef core_hpp_guard
#define core_hpp_guard

#include <cstdint>
#include <array>
#include <vector>
#include <utility>
#include <exception>

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

        Point(void);
        Point(Color, int);
        Point(const Point&);
        Point& operator=(const Point&);

        Point& operator+=(int);
        Point& operator-=(int);
        Point& operator++(void);
        Point operator++(int);
        Point& operator--(void);
        Point operator--(int);
    };

    // operatori non-member non-friend
    const Point operator+(Point, int); // audauga un nr de puluri
    const Point operator-(Point, int);
    bool operator==(Point, Point); // operatori de compararare
    bool operator!=(Point, Point);

    enum class GamePhase : int8_t {
        STARTING, GAME, NORMAL_WIN, TECHNICAL_WIN
    };

    class Board {
    private:
        std::array <Point, NUM_POINTS> points;
        Color current_player;
        Color winner;
        GamePhase current_phase;

        std::array <unsigned int, 2> done;
        std::array <unsigned int, 2> out;

        std::pair <int, int> current_dice;
        std::vector <int> remaining_moves;
    public:
        Board(void); // constructor inplicit
        Board(const Board&); // constructor copiere
        Board& operator=(Board); // operator copiere

        Color get_winner(void) const {
            // daca ii gata partida, returneaza castigatorul
            if(current_phase != GamePhase::NORMAL_WIN && current_phase != GamePhase::TECHNICAL_WIN)
                throw std::runtime_error("No winner yet"); // daca nu, exceptie
            return winner;
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

        GamePhase get_phase(void) const {
            return current_phase;
        }

        void roll_dice(void);
        std::pair <int, int> get_dice(void) const;

        const std::array <Point, NUM_POINTS> get_tabla(void) const {
            // returneaza reprezentarea tablei
            return points;
        }

        bool is_move_legal(int, int) const; // verifica daca se poate muta de pe o pozitie cu cateva mutari in fata
        bool move_checker(int, int); // se muta. parametrii identici. returneaza fals si nu muta daca mutarea e ilegala
        std::vector <int> get_remaining_moves(void) const;
        std::vector <std::pair <int, int>> get_legal_moves(void) const; // returneaza perechi (pozitie, mutare)
    };
}

#endif
