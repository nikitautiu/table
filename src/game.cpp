#include "game.hpp"


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
                                   current_dice() {}

    Backgammon::Backgammon(const Backgammon& other) : current_board_state(other.current_board_state),
                                                      current_player(other.current_player),
                                                      winner(other.winner),
                                                      current_phase(other.current_phase),
                                                      current_dice(other.current_dice) {}

    Backgammon& Backgammon::operator=(Backgammon other) {
        // check for assignment to self
        if ( this != &other )
            std::swap((*this), other);
        return (*this);

    }
}
