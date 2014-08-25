#include "game.hpp"
namespace table {
    Point::Point(void) : color(), number() {}

    Point::Point(Color p_color, int p_number) : color(p_color), number(p_number) {}

    Point::Point(const Point& other) : color(other.color), number(other.number) {}

    Point& Point::operator=(const Point& other) {
        this->number = other.number;
        this->color = other.color;
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
                         done(),
                         out(),
                         current_dice(),
                         starting_phase(),
                         is_game_won(),
                         remaining_moves()
    {
        points[0] = Point(Color::WHITE, 2), points[NUM_POINTS-1] = Point(Color::BLACK, 2);
        points[5] = Point(Color::WHITE, 5), points[NUM_POINTS-6] = Point(Color::BLACK, 5);
        points[7] = Point(Color::WHITE, 3), points[NUM_POINTS-8] = Point(Color::BLACK, 3);
        points[12]= Point(Color::WHITE, 5), points[NUM_POINTS-13]= Point(Color::BLACK, 5);
    }

    Board::Board(const Board& board) {

        int c = 0;
        for (const auto i : board.points )
            this->points[c++] = i;

        this->current_player = board.current_player;

        c = 0;
        for ( const auto i : board.done )
            this->done[c++] = i;

        c = 0;
        for ( const auto i : board.out )
            this->out[c++] = i;

        this->current_dice = board.current_dice;
        this->starting_phase = board.starting_phase;
        this->is_game_won = board.is_game_won;

        c = 0;
        for ( auto i : board.remaining_moves )
            this->remaining_moves[c++] = i;
    }

    Board& Board::operator=(const Board& board) {

                         // check for assignment to self
        if ( this != &board ) {
            int c = 0;
            for (const auto i : board.points )
                this->points[c++] = i;

            this->current_player = board.current_player;

            c = 0;
            for ( const auto i : board.done )
                this->done[c++] = i;

            c = 0;
            for ( const auto i : board.out )
                this->out[c++] = i;

            this->current_dice = board.current_dice;
            this->starting_phase = board.starting_phase;
            this->is_game_won = board.is_game_won;

            c = 0;
            for ( auto i : board.remaining_moves )
                this->remaining_moves[c++] = i;
        }
        return *this;
    }
}
