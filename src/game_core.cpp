#include <exception>
#include "game_core.hpp"
#include "dice.hpp"

namespace table {
    Color operator-(Color color) {
        return (color == Color::WHITE ? Color::BLACK : Color::WHITE);
    }

/******************************************************************************
                                POINT CLASS
*******************************************************************************/
    Point::Point(void) : color(), number() {}

    Point::Point(Color p_color, int p_number) : color(p_color), number(p_number) {}

    Point::Point(const Point& other) : color(other.color), number(other.number) {}


    Point& Point::operator=(Point other) {
        if(this != &other)
        {
            std::swap(color, other.color);
            std::swap(number, other.number);
        }
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

    BoardState::BoardState(void) : points(), done(), out() {}

    BoardState::BoardState(const BoardState& board) : points(board.points),
                                                      done(board.done),
                                                      out(board.out)
    {
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

    int BoardState::get_starting_pos(Color player) {
        return (player == Color::WHITE ? 0 : NUM_POINTS - 1);
    }

    int BoardState::get_move_sign(Color player) {
        return (player == Color::WHITE ? 1 : -1);
    }
}
