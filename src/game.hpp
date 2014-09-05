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
                            DEFINES AND ENUMS
*******************************************************************************/
struct BoardState {
    PointArray points;
    std::array <unsigned int, 2> done;
    std::array <unsigned int, 2> out;

    void init (void);

    int get_out(Color color) const;
    int get_done(Color color) const;
    void set_out(Color color, int new_value);
    void set_done(Color color, int new_value);
};

/******************************************************************************
                        ROUND CLASS
*******************************************************************************/
    class Round {
    private:
        BoardState current_board_state;
        Color current_player;
        Color winner;
        RoundPhase current_phase;
        DicePair current_dice;
        bool needs_reroll;

        std::set <Turn> valid_moves;
    public:
        Round(void); // constructor inplicit
        Round(const Round&); // constructor copiere
        Round& operator=(Round); // operator copiere

        void init(Color, DicePair);

        Color get_winner(void) const;
        Color get_current_player(void) const;
        RoundPhase get_phase(void) const;
        BoardState get_board_state(void) const;
        DicePair get_dice(void) const;
        const std::set <Turn>& get_legal_moves(void) const;
        bool get_needs_reroll(void) const;

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

        const std::set <Turn> *valid_moves; // pointer catre mutarile valide din Round

    public:
        // clasa pe care poti face mutari, da undo, verifica legalitatea lor etc
        HelperBoard(void);
        HelperBoard(const Round&); // initializeaza o tabla temporara din clasa de joc
        HelperBoard(const HelperBoard&); // constructor copiere
        HelperBoard& operator=(HelperBoard); // operator copiere

        void init_from_board(const Round&);

        BoardState get_board_state(void) const;
        Turn get_turn(void) const; // returneaza mutarile de pana acuma
        void push_move(CheckerMove); // face o mutare. daca ilegala, arunca exceptie
        void pop_move(void); // da undo la ultima mutare

        const std::set <Turn>& get_legal_moves(void) const;
        std::set<CheckerMove> get_immediately_legal_moves(void) const; // returneaza mutarile de cate o pula imediat legale(prima data cele obligatorii)
        std::multiset<int> get_remaining_moves(void) const; // returneaza mutarile ramase
        bool is_turn_done(void) const; // verifica daca s-a facut o tura completa legala
    };
}

#endif
