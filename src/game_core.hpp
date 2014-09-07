#ifndef game_hpp_guard
#define game_hpp_guard

#include <cstdint>
#include <array>
#include <vector>
#include <set>
#include <utility>
#include <exception>

namespace table {
/******************************************************************************
                        POINT CLASS
*******************************************************************************/
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
        Point& operator=(Point);
        Point& operator=(int);

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


/******************************************************************************
                            DEFINES AND ENUMS
*******************************************************************************/
    const int NUM_POINTS = 24;
    const int NUM_CHECKERS_PER_PLAYER = 15;

    using CheckerMove = std::pair <int, int>;
    using Turn = std::vector <CheckerMove>;
    using PointArray = std::array <Point, NUM_POINTS>;
    using DicePair = std::pair <int, int>;

    enum class RoundPhase : int8_t {
        STARTING, GAME, NORMAL_WIN, TECHNICAL_WIN
    };




/******************************************************************************
                            BOARDSTATE CLASS
*******************************************************************************/
    struct BoardState {
        PointArray points;
        std::array <unsigned int, 2> done;
        std::array <unsigned int, 2> out;

        void init (void);

        int get_out(Color color) const; // nr scoase temporar
        int get_done(Color color) const; // nr scoase permanent
        void set_out(Color color, int new_value);
        void set_done(Color color, int new_value);

        static int get_starting_pos(Color);
        static int get_move_sign(Color);
    };
}

#endif
