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

    enum class GamePhase : int8_t {
        STARTING, GAME, NORMAL_WIN, TECHNICAL_WIN
    };


/******************************************************************************
                            DEFINES AND ENUMS
*******************************************************************************/
struct BoardState {
    PointArray points;
    std::array <unsigned int, 2> done;
    std::array <unsigned int, 2> out;

    void initialize (void) {
        points[0]  = Point(Color::WHITE, 2), points[NUM_POINTS-1]  = Point(Color::BLACK, 2);
        points[5]  = Point(Color::WHITE, 5), points[NUM_POINTS-6]  = Point(Color::BLACK, 5);
        points[7]  = Point(Color::WHITE, 3), points[NUM_POINTS-8]  = Point(Color::BLACK, 3);
        points[12] = Point(Color::WHITE, 5), points[NUM_POINTS-13] = Point(Color::BLACK, 5);
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

    void set_out(Color color, int new_value) {
        int poz = (color ==  Color::WHITE ? 0 : 1);
        out[poz] =  new_value;
    }

    void set_done(Color color, int new_value) {
        int poz = (color ==  Color::WHITE ? 0 : 1);
        done[poz] = new_value;
    }


};

/******************************************************************************
                        BACKGAMMON CLASS
*******************************************************************************/
    class Backgammon {
    private:
        BoardState current_board_state;
        Color current_player;
        Color winner;
        GamePhase current_phase;
        DicePair current_dice;
    public:
        Backgammon(void); // constructor inplicit
        Backgammon(const Backgammon&); // constructor copiere
        Backgammon& operator=(Backgammon); // operator copiere

        void initialize(void) {
            (*this) = Backgammon(); // reinitializeaza cu nul
            current_phase = GamePhase::STARTING;
            current_board_state.initialize();
        }

        Color get_winner(void) const {
            // daca ii gata partida, returneaza castigatorul
            if(current_phase != GamePhase::NORMAL_WIN && current_phase != GamePhase::TECHNICAL_WIN)
                throw std::runtime_error("No winner yet"); // daca nu, exceptie
            return winner;
        }

        Color get_current_player(void) const {
            return current_player; // returneaza playerul actual
        }

        GamePhase get_phase(void) const {
            return current_phase;
        }

        BoardState get_board_state(void) const {
            // returneaza reprezentarea tablei
            return current_board_state;
        }

        DicePair get_dice(void) const {
            return current_dice;
        }

        void roll_dice(void); // arunca cu zarul, actualizeaza current_dice(atentie cand current_game_phase = STARTING)
        void submit_turn(Turn); // trimite un set de mutari. daca sunt ilegale arunca exceptie. daca nu, efectueaza
    };


/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/
    class HelperBoard {
    private:
        BoardState current_board_state; // asta se initializeaza din bagamon. dupa se modifica cand se fac mutari
        Color player; // playeru care face mutaorile
        DicePair dices; // zarurile cu care se lucreaza
        Turn history;   // se pusheaza aici toate mutarile ( first = poz.init, second = nr mutari )
        std::multiset<int> remaining_moves; // mutarile ramase cu care se lucreaza


    public:
        // clasa pe care poti face mutari, da undo, verifica legalitatea lor etc
        HelperBoard(void);
        HelperBoard(const Backgammon&); // initializeaza o tabla temporara din clasa de joc
        HelperBoard(const HelperBoard&); // constructor copiere
        HelperBoard& operator=(HelperBoard); // operator copiere
        BoardState get_board_state(void) const;

        Turn get_turn(void) const; // returneaza mutarile de pana acuma
        void push_move(CheckerMove); // face o mutare. daca ilegala, arunca exceptie
        void pop_move(void); // da undo la ultima mutare

        std::set<CheckerMove> get_immediately_legal_moves(void) const; // returneaza mutarile de cate o pula imediat legale(prima data cele obligatorii)
        std::multiset<int> get_remaining_moves(void) const; // returneaza mutarile ramase
        bool is_turn_done(void) const; // verifica daca s-a facut o tura completa legala
    };
}

#endif
