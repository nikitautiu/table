#include "catch.hpp"
#include "../src/game_core.hpp"

TEST_CASE("enumul Color e negabil", "[game_core]")
{
    REQUIRE(-table::Color::WHITE == table::Color::BLACK);
    REQUIRE(table::Color::WHITE == -table::Color::BLACK);
}

TEST_CASE("clasa Point se comporta conform specificatiei", "[game_core][Point]")
{
    SECTION("are ca proprietati o culoare si un nr")
    {
        auto temp = table::Point(table::Color::WHITE, 5);
        REQUIRE(temp.color == table::Color::WHITE);
        REQUIRE(temp.number == 5);
    }

    SECTION("implementeaza operatorii unari de atribuire, scadere, incrementare, decrementare")
    {
        auto temp = table::Point(table::Color::WHITE, 5);
        temp += 2;
        CHECK(temp.number == 7);
        temp -= 5;
        CHECK(temp.number == 2);
        --temp;
        CHECK(temp.number == 1);
        ++temp;
        CHECK(temp.number == 2);
    }

    SECTION("implementeaza operatorii binari aritmetici si logici")
    {
        auto point_a = table::Point(table::Color::WHITE, 5),
             point_b = table::Point(table::Color::BLACK, 5),
             point_c = table::Point(table::Color::WHITE, 10);

        // egalitate/inegalitate
        REQUIRE(point_a == point_a);
        REQUIRE(point_a != point_b);
        REQUIRE(point_a != point_c);

        // adunare/scadere
        REQUIRE((point_a + 5) == point_c);
        REQUIRE((point_c - 5) == point_a);
    }
}

TEST_CASE("clasa BoardState se comporta conform specificatiei", "[game_core][BoardState]")
{
    auto temp_board_state = table::BoardState();
    REQUIRE(temp_board_state.points.size() == table::NUM_POINTS);

    SECTION("proprietatea points e random accesible")
    {
        temp_board_state.points[2] = temp_board_state.points[5] = table::Point(table::Color::WHITE, 6);
        REQUIRE(temp_board_state.points[2] == temp_board_state.points[5]);
        REQUIRE(temp_board_state.points[2] == table::Point(table::Color::WHITE, 6));
    }
}
