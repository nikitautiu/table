#include "game.hpp"


namespace table {
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

    Board::Board(void) : points(),
                         current_player(),
                         winner(),
                         current_phase(),
                         done(),
                         out(),
                         current_dice(),
                         remaining_moves()
    {
        points[0] = Point(Color::WHITE, 2), points[NUM_POINTS-1] = Point(Color::BLACK, 2);
        points[5] = Point(Color::WHITE, 5), points[NUM_POINTS-6] = Point(Color::BLACK, 5);
        points[7] = Point(Color::WHITE, 3), points[NUM_POINTS-8] = Point(Color::BLACK, 3);
        points[12]= Point(Color::WHITE, 5), points[NUM_POINTS-13]= Point(Color::BLACK, 5);
    }

    Board::Board(const Board& other) : points(other.points),
                                       current_player(other.current_player),
                                       winner(other.winner),
                                       current_phase(other.current_phase),
                                       done(other.done),
                                       out(other.out),
                                       current_dice(other.current_dice),
                                       remaining_moves(other.remaining_moves) {}

    Board& Board::operator=(Board other) {
        // check for assignment to self
        if ( this != &other )
            std::swap((*this), other);
        return (*this);

    }
}
