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
                        BACKGAMMON CLASS
*******************************************************************************/
    Backgammon::Backgammon(void) : current_board_state(),
                                   current_player(),
                                   winner(),
                                   current_phase(),
                                   current_dice(),
                                   valid_moves() {
    }

    Backgammon::Backgammon(const Backgammon& other) : current_board_state(other.current_board_state),
                                                      current_player(other.current_player),
                                                      winner(other.winner),
                                                      current_phase(other.current_phase),
                                                      current_dice(other.current_dice),
                                                      valid_moves(other.valid_moves) {
    }

    Backgammon& Backgammon::operator=(Backgammon other) {
        // check for assignment to self
        if ( this != &other )
            std::swap((*this), other);
        return (*this);

    }

    void Backgammon::roll_dice(void) {
        if ( this->current_phase != GamePhase::STARTING ) {
            this->current_dice = double_dice_roll();
            this->valid_moves = get_legal_moves(current_board_state, current_player, current_dice);
        }
        else
        {
            DicePair roll_1 = double_dice_roll();
            DicePair roll_2 = double_dice_roll();

            if ( roll_1.first + roll_1.second > roll_2.first + roll_2.second )
                current_player = Color::WHITE;
            else
                current_player = Color::BLACK;
        }
    }

    void Backgammon::submit_turn(Turn moves) {
        if(valid_moves.find(moves) != valid_moves.end()) {
            auto new_board_state = process_board(current_board_state, moves);
            current_board_state = new_board_state;
        }
        else
            throw std::runtime_error("Illegal moves");
    }


/******************************************************************************
                        HELPERBOARD CLASS
*******************************************************************************/


    HelperBoard::HelperBoard(void) : current_board_state(),
                                     player(),
                                     dices(),
                                     remaining_moves() {
    }

    HelperBoard::HelperBoard(const Backgammon& other) : current_board_state(other.get_board_state()),
                                                        player(other.get_current_player()),
                                                        dices(other.get_dice()),
                                                        remaining_moves() {

        if ( dices.first == dices.second )
            for (int i = 0; i < 4; ++i)
                remaining_moves.insert(dices.first);
        else
            remaining_moves.insert(dices.first),
            remaining_moves.insert(dices.second);
    }


    HelperBoard::HelperBoard(const HelperBoard& other) : current_board_state(other.current_board_state),
                                                         player(other.player),
                                                         dices(other.dices),
                                                         remaining_moves(other.remaining_moves)


    {
    }

    HelperBoard& HelperBoard::operator=(HelperBoard other)  {
        if ( this != &other )
            std::swap((*this), other);
        return (*this);
    }

    inline BoardState HelperBoard::get_board_state(void) const {
        return current_board_state;
    }

    inline Turn HelperBoard::get_turn(void) const {
        return history;
    }

    inline void HelperBoard::push_move(CheckerMove checkerMove) {
        history.push_back(checkerMove);
    }

    inline void HelperBoard::pop_move(void) {
        history.pop_back();
    }
/******************************************
    STILL NEED RULES HEADER, DO NOT MODIFY
********************************************/
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
