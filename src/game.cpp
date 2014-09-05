#include <exception>
#include "game.hpp"
#include "dice.hpp"
#include "rules.hpp"

namespace table {
/******************************************************************************
                                POINT CLASS
*******************************************************************************/
    Point::Point(void) : color(), number() {}

    Point::Point(Color p_color, int p_number) : color(p_color), number(p_number) {}

    Point::Point(const Point& other) : color(other.color), number(other.number) {}

    Point& Point::operator=(Point other) {
        if(this != &other)
            std::swap((*this), other);
        return (*this);
    }

    Point& Point::operator=(int new_value) {
        number = new_value;
        return (*this);
    }


    Point& Point::operator+=(int num) {
        this->number += num;
        return (*this);
    }

    Point& Point::operator-=(int num) {
        this->number -= num;
        return (*this);
    }

    Point& Point::operator++(void) {
        ++(this->number);
        return (*this);
    }

    Point Point::operator++(int) {
        Point* old = this;
        ++(*this);
        return (*old);
    }

    Point& Point::operator--(void) {
        --(this->number);
        return (*this);
    }

    Point Point::operator--(int) {
        Point* old = this;
        --(*this);
        return (*old);
    }

    const Point operator+(Point a, int num) {
        a.number += num;
        return a;
    }

    const Point operator-(Point a, int num) {
        a.number -= num;
        return a;
    }

    bool operator==(Point a, Point b) {
        return ( a.color == b.color && a.number == b.number );
    }

    bool operator!=(Point a, Point b) {
        return !(a.color == b.color && a.number == b.number);
    }


/******************************************************************************
                        BOARDSTATE CLASS
*******************************************************************************/
    void BoardState::init (void) {
        points[0]  = Point(Color::WHITE, 2), points[NUM_POINTS-1]  = Point(Color::BLACK, 2);
        points[5]  = Point(Color::WHITE, 5), points[NUM_POINTS-6]  = Point(Color::BLACK, 5);
        points[7]  = Point(Color::WHITE, 3), points[NUM_POINTS-8]  = Point(Color::BLACK, 3);
        points[12] = Point(Color::WHITE, 5), points[NUM_POINTS-13] = Point(Color::BLACK, 5);
    }

    int BoardState::get_out(Color color) const {
        // primeste culoare si returneaza cate scoase de culoara aia is
        int poz = (color ==  Color::WHITE ? 0 : 1);
        return out[poz];
    }

    int BoardState::get_done(Color color) const {
        // primeste culoare si returneaza cate de culoarea aia o terminat
        int poz = (color ==  Color::WHITE ? 0 : 1);
        return done[poz];
    }

    void BoardState::set_out(Color color, int new_value) {
        int poz = (color ==  Color::WHITE ? 0 : 1);
        out[poz] =  new_value;
    }

    void BoardState::set_done(Color color, int new_value) {
        int poz = (color ==  Color::WHITE ? 0 : 1);
        done[poz] = new_value;
    }

/******************************************************************************
                        ROUND CLASS
*******************************************************************************/
    Round::Round(void) : current_board_state(),
                                   current_player(),
                                   winner(),
                                   current_phase(),
                                   current_dice(),
                                   valid_moves() {
    }

    Round::Round(const Round& other) : current_board_state(other.current_board_state),
                                                      current_player(other.current_player),
                                                      winner(other.winner),
                                                      current_phase(other.current_phase),
                                                      current_dice(other.current_dice),
                                                      valid_moves(other.valid_moves) {
    }

    Round& Round::operator=(Round other) {
        // check for assignment to self
        if ( this != &other )
            std::swap((*this), other);
        return (*this);

    }

    void Round::init(Color starting_player, DicePair starting_dice=DicePair(0,0)) {
        // initializeaza tabla, daca se da si o perche de zaruri inseamna ca s-a dat o dubla
        (*this) = Round(); // reinitializeaza cu nul
        current_board_state.init();
        current_phase = RoundPhase::GAME;
        current_player = starting_player;
        if(starting_dice == DicePair(0,0))
            needs_reroll = true;
        else {
            needs_reroll = false;
            current_dice = starting_dice;
        }
    }

    Color Round::get_winner(void) const {
        // daca ii gata partida, returneaza castigatorul
        if(current_phase != RoundPhase::NORMAL_WIN && current_phase != RoundPhase::TECHNICAL_WIN)
            throw std::runtime_error("No winner yet"); // daca nu, exceptie
        return winner;
    }

    Color Round::get_current_player(void) const {
        return current_player; // returneaza playerul actual
    }

    RoundPhase Round::get_phase(void) const {
        return current_phase;
    }

    BoardState Round::get_board_state(void) const {
        // returneaza reprezentarea tablei
        return current_board_state;
    }

    DicePair Round::get_dice(void) const {
        return current_dice;
    }

    const std::set <Turn>& Round::get_legal_moves(void) const {
        return valid_moves;
    }

    bool Round::get_needs_reroll(void) const {
        return needs_reroll;
    }

    void Round::roll_dice(void) {
        if(current_phase != RoundPhase::GAME)
            throw std::runtime_error("Can only roll during game phase");
        else if(!needs_reroll)
            throw std::runtime_error("Dice does not need to be rerolled");
        else {
            current_dice = double_dice_roll();
            valid_moves = table::get_legal_moves(current_board_state, current_player, current_dice);
        }
    }

    void Round::submit_turn(Turn moves) {
        if(valid_moves.find(moves) != valid_moves.end()) {
            auto new_board_state = process_board(current_board_state, moves);
            current_board_state = new_board_state;
        }
        else if(current_phase == RoundPhase::GAME)
            throw std::runtime_error("Illegal moves");
        else
            throw std::runtime_error("Cannot move in this game phase");
    }


/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/


    HelperBoard::HelperBoard(void) : current_board_state(),
                                     player(),
                                     dices(),
                                     remaining_moves(),
                                     valid_moves() {
    }

    HelperBoard::HelperBoard(const Round& round) {
        init_from_board(round);

    }

    HelperBoard::HelperBoard(const HelperBoard& other) : current_board_state(other.current_board_state),
                                                         player(other.player),
                                                         dices(other.dices),
                                                         remaining_moves(other.remaining_moves) {
    }

    void HelperBoard::init_from_board(const Round& round) {
        current_board_state = round.get_board_state();
        player = round.get_current_player();
        dices = round.get_dice();
        remaining_moves = std::multiset<int> ();
        valid_moves = &(round.get_legal_moves());

        if ( dices.first == dices.second )
            for (int i = 0; i < 4; ++i)
                remaining_moves.insert(dices.first);
        else
            remaining_moves.insert(dices.first),
            remaining_moves.insert(dices.second);
    }

    HelperBoard& HelperBoard::operator=(HelperBoard other)  {
        if ( this != &other )
            std::swap((*this), other);
        return (*this);
    }

    BoardState HelperBoard::get_board_state(void) const {
        return current_board_state;
    }

    Turn HelperBoard::get_turn(void) const {
        return history;
    }

    void HelperBoard::push_move(CheckerMove checkerMove) {
        history.push_back(checkerMove);
    }

    void HelperBoard::pop_move(void) {
        history.pop_back();
    }
/******************************************
    STILL NEED RULES HEADER, DO NOT MODIFY
********************************************/
    const std::set <Turn>& HelperBoard::get_legal_moves(void) const {
        return *valid_moves;
    }

    std::set<CheckerMove> HelperBoard::get_immediately_legal_moves(void) const {
        std::set<CheckerMove> TODO;
        return TODO; // Anti-Warning, compile
    }

    std::multiset<int> HelperBoard::get_remaining_moves(void) const {
        std::multiset<int> TODO;
        return TODO; // Anti-Warning, compile
    }

    bool HelperBoard::is_turn_done(void) const {
        bool TODO = true;
        return TODO; // Anti-Warning, compile
    }

/******************************************
STILL NEED RULES HEADER, DO NOT MODIFY
********************************************/
}
