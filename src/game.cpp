#include "game.hpp"
namespace table {
    Point::Point(void) : color(), number() {}

    Point::Point(Color p_color, int p_number) : color(p_color), number(p_number) {}

    Point::Point(Point other) : number(other.number), color(other.color) { }

    Point& Point::operator=(Point other) {
        this->number = other.number;
        this->color = other.color;
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
}
