#include "game.hpp"
namespace table {

    Board::Board(void) : points(),
                         current_player(),
                         current_dice(),
                         done(),
                         out(),
                         starting_phase(),
                         is_game_won(),
                         remaining_moves()
    {
        points[0] = points[NUM_POINTS-1] = 2;
        points[5] = points[NUM_POINTS-6] = 5;
        points[7] = points[NUM_POINTS-8] = 3;
        points[12] = points[NUM_POINTS-13] = 5;

    }

    Point::Point(Color p_color, int p_number) {
        this->color = p_color;
        this->number = p_number;
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
}
