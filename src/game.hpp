#ifndef core_hpp_guard
#define core_hpp_guard

#include <cstdint>
#include <array>
#include <vector>
#include <set>
#include <utility>
#include <exception>

namespace table {

/******************************************************************************
                            DEFINES AND ENUMS
*******************************************************************************/
    const int NUM_POINTS = 24;
    const int NUM_CHECKERS_PER_PLAYER = 15;

    using CheckerMove = std::pair <int, int>;
    using Turn = std::vector <CheckerMove>;
    using PointArray = std::array <Point, NUM_POINTS>;

    enum class GamePhase : int8_t {
        STARTING, GAME, NORMAL_WIN, TECHNICAL_WIN
    };

    enum class Color : int8_t {
        // tipurile de table/jucatori
        WHITE = -1, BLACK = 1
    };


/******************************************************************************
                        POINT CLASS
*******************************************************************************/
    struct Point {
        Color color;
        int number;

        Point(void);
        Point(Color, int);
        Point(const Point&);
        Point& operator=(Point);

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
                        BACKGAMMON CLASS
*******************************************************************************/
    class Backgammon {
    private:
        PointArray points;
        Color current_player;
        Color winner;
        GamePhase current_phase;

        std::array <unsigned int, 2> done;
        std::array <unsigned int, 2> out;

        std::pair <int, int> current_dice;
        std::vector <int> remaining_moves;
    public:
        Backgammon(void); // constructor inplicit
        Backgammon(const Backgammon&); // constructor copiere
        Backgammon& operator=(Backgammon); // operator copiere

        void intialize(void);

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

        std::pair <int, int> get_dice(void) const {
            return current_dice;
        }

        const PointArray get_point_array(void) const {
            // returneaza reprezentarea tablei
            return points;
        }

        void submint_turn(Turn); // trimite un set de mutari. daca sunt ilegale arunca exceptie. daca nu, efectueaza
        std::set <Turn> get_legal_moves(void) const; // returneaza toate seturile de mutari valide

/// DE IMPLEMENTAT, metode care primesc o tabla si returneaza mutari legale etc. Informatiile
/// sunt necesare si pt alte clase
    };


/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    class HelperBoard {
    public:
        // clasa pe care poti face mutari, da undo, verifica legalitatea lor etc
        HelperBoard(void);
        HelperBoard(const Backgammon&); // initializeaza o tabla temporara din clasa de joc
        HelperBoard(const HelperBoard&); // constructor copiere
        operator=(const HelperBoard&); // operator copiere

        Turn get_turn(void) const; // returneaza mutarile de pana acuma
        void push_move(CheckerMove); // face o mutare, aceleasi verificari de legalitate
        void pop_move(void); // da undo la ultima mutare

        std::set <CheckerMove> get_immediately_legal_moves(void) const; // returneaza mutarile de cate un pul imediat legale
        /// etc etc etc
    };
}

#endif
