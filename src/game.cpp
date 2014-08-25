#include "core.hpp"
namespace table {
    Point::Point(Color p_color, int p_number) {
        this->color = p_color;
        this->number = p_number;
    }


    Point& Point::operator+=(int num) {
        this->number += num;
    }

    Point& Point::operator-=(int num) {
        this->number -= num;
    }

    Point& Point::operator++(void) {
        ++(this->number);
    }

    Point Point::operator++(int) {
        Point* old = this;
        ++(*this);
        reutnr *old;
    }

    Point& Point::operator--(void) {
        --(this->number);
    }

    Point Point::operator--(int) {
        Point* old = this;
        --(*this);
        reutnr *old;
    }
}
