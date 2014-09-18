#include "catch.hpp"
#include "../src/game_core.hpp"

TEST_CASE("clasa Point se comporta conform specificatiei", "[game_core][Point]")
{
    SECTION("clasa Point contine o culoare si un numar accesabile")
    {
        auto temp = table::Point(table::Color::WHITE, 5);
        REQUIRE(temp.color == table::Color::WHITE);
        REQUIRE(temp.number == 5);
    }

    SECTION("clasa Porin implementeazao peratorii de atribuire, scadere, incrementare, decrementare")
    {
        auto temp = table::Point(table::Color::WHITE, 5);
        temp += 2;
        REQUIRE(temp.number == 7);
        temp -= 5;
        REQUIRE(temp.number == 2);
        --temp;
        REQUIRE(temp.number == 1);
        ++temp;
        REQUIRE(temp.number == 2);
    }
}
