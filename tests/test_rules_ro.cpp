#include "catch.hpp"
#include "../src/variants/rules_ro.hpp"
#include <iostream>

TEST_CASE("RoDiceHelper functioneaza cum trebuie", "[rules_ro][RoDiceHelper]")
{
    SECTION("se castiga din prima")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // ALTERNEAZA: NEGRU
        helper.give_dice(std::make_pair(2, 3)); // ALB
        helper.give_dice(std::make_pair(5, 3)); // NEGRU, negru = 8 > 5 => negru winner

        REQUIRE(helper.is_done());
        REQUIRE(helper.get_winner() == table::Color::BLACK);


        // SE VERIFICA DACA FUNCTIONEAZA FUNCTIA get_double_pair()
        auto double_pair = helper.get_double_pair();
        REQUIRE(!double_pair.first);
    }

    SECTION("se dau zaruri egale la inceput")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(4, 3)); // alb
        helper.give_dice(std::make_pair(4, 3)); // negru

        REQUIRE(helper.is_done() == false);
    }

    SECTION("se dau zaruri egale, apoi cineva castiga")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(4, 3)); // alb
        helper.give_dice(std::make_pair(4, 3)); // negru

        helper.give_dice(std::make_pair(4, 6)); // alb

        REQUIRE(!helper.is_done()); // trebuie sa dea cineva un zar castigator, nu e gata inca


        helper.give_dice(std::make_pair(1, 1)); // negru
        // => castigatorul este alb

        REQUIRE(helper.is_done());
        REQUIRE(helper.get_winner() == table::Color::WHITE);
    }

    SECTION("se da repetat acelasi zar, apoi castiga cineva")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(4, 3)); // alb
        helper.give_dice(std::make_pair(4, 3)); // negru

        // PUNCT DE REINITIALIZARE

        REQUIRE(!helper.is_done());

        helper.give_dice(std::make_pair(6, 6)); // alb

        REQUIRE(!helper.is_done());

        helper.give_dice(std::make_pair(6, 6)); // negru

        REQUIRE(!helper.is_done());

        helper.give_dice(std::make_pair(3, 6)); // alb
        helper.give_dice(std::make_pair(5, 6)); // WINNER, BLACK

        REQUIRE(helper.is_done());
    }

    SECTION("cineva da o dubla si castiga")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(4, 4)); // alb
        helper.give_dice(std::make_pair(4, 3)); // negru

        REQUIRE(helper.is_done());
        REQUIRE(helper.get_winner() == table::Color::WHITE);
    }

    SECTION("ambii jucatori dau dubla si castiga cea mai mare")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(4, 4)); // alb
        helper.give_dice(std::make_pair(6, 6)); // negru


        REQUIRE(helper.is_done());
        REQUIRE(helper.get_winner() == table::Color::BLACK);
    }

    SECTION("ambii jucatori dau aceeasi suma dar din numere diferite")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::BLACK); // negru
        helper.give_dice(std::make_pair(1, 6)); // alb
        helper.give_dice(std::make_pair(4, 3)); // negru

        REQUIRE(!helper.is_done());
    }
}

TEST_CASE("RoOpeningRollPhase functioneaza cum trebuie", "[rules_ro][RoOpeningRollPhase]")
{
    SECTION("roll_dice functioneaza corect")
    {
        auto ro_opening = table::RoOpeningRollPhase(table::Color::WHITE);
        ro_opening.roll_dice();

        auto dices = ro_opening.get_current_dices();

        REQUIRE(dices.first != 0);
        REQUIRE(dices.second != 0);
    }

    SECTION("get_starting_doubles trebuie sa returneze exceptie")
    {
        auto ro_opening = table::RoOpeningRollPhase(table::Color::WHITE);
        ro_opening.preset_roll_dice(std::make_pair(3, 4));


        REQUIRE_THROWS(ro_opening.get_starting_double());
    }

    SECTION("get_starting_doubles nu returneaza exceptie deoarece exista duble")
    {
        auto ro_opening = table::RoOpeningRollPhase(table::Color::WHITE);
        ro_opening.preset_roll_dice(std::make_pair(3, 3));
        REQUIRE(ro_opening.get_current_dices() == std::make_pair(3, 3));

        ro_opening.preset_roll_dice(std::make_pair(1, 2));
        REQUIRE(ro_opening.get_current_dices() == std::make_pair(1, 2));


        REQUIRE_NOTHROW(ro_opening.get_starting_double());

        auto starting_double = ro_opening.get_starting_double();
        REQUIRE(starting_double.first == starting_double.second);
    }

}

namespace internal
{
    // genereaza o tabla romaneasca de inceput de joc
    table::BoardState get_clean_ro_board(void)
    {
        auto board_state = table::BoardState();
        auto& points = board_state.points;

        points[0]  = table::Point(table::Color::WHITE, 2);
        points[table::NUM_POINTS-1]  = table::Point(table::Color::BLACK, 2);
        points[5]  = table::Point(table::Color::WHITE, 5);
        points[table::NUM_POINTS-6]  = table::Point(table::Color::BLACK, 5);
        points[7]  = table::Point(table::Color::WHITE, 3);
        points[table::NUM_POINTS-8]  = table::Point(table::Color::BLACK, 3);
        points[12] = table::Point(table::Color::WHITE, 5);
        points[table::NUM_POINTS-13] = table::Point(table::Color::BLACK, 5);

        return board_state;
    }

}

TEST_CASE("RoGamePhase functioneaza cum trebuie", "[rules_ro][RoGamePhase]")
{
    SECTION("Constructorul RoGamePhase(Color, DicePair) initializeaza obiectul cum trebuie")
    {
        SECTION("DicePair implicit")
        {
            auto phase = table::RoGamePhase(table::Color::WHITE); //se initializeaza fara dubla de inceput

            CHECK(phase.get_phase_type() == table::PhaseType::GAME_PHASE);
            CHECK(phase.get_current_board_state() == internal::get_clean_ro_board());
            CHECK(phase.get_dice_obligation() == table::DiceObligation::MUST_ROLL);
            CHECK(phase.get_current_player() == table::Color::WHITE);
        }

        SECTION("DicePair explicit")
        {
            auto phase = table::RoGamePhase(table::Color::WHITE, table::DicePair(2, 3)); //se initializeaza cu dubla de inceput

            CHECK(phase.get_phase_type() == table::PhaseType::GAME_PHASE);
            CHECK(phase.get_current_board_state() == internal::get_clean_ro_board());
            CHECK(phase.get_dice_obligation() == table::DiceObligation::CAN_NOT_ROLL);
            CHECK(phase.get_current_player() == table::Color::WHITE);
            CHECK(phase.get_current_dices() == table::DicePair(2, 3));
        }
    }

    SECTION("Constructorul RoGamePhase(BoardState, Color, DicePair) initializeaza obiectul cum trebuie")
    {
        auto state_input = table::BoardState();

        state_input.points[2] = table::Point(table::Color::WHITE, 3);
        state_input.points[5] = table::Point(table::Color::WHITE, 7);
        state_input.points[10] = table::Point(table::Color::BLACK, 9);
        state_input.points[8] = table::Point(table::Color::WHITE, 1);

        SECTION("DicePair implicit")
        {
            auto phase = table::RoGamePhase(state_input, table::Color::WHITE); //se initializeaza fara dubla de inceput

            CHECK(phase.get_phase_type() == table::PhaseType::GAME_PHASE);
            CHECK(phase.get_current_board_state() == state_input);
            CHECK(phase.get_dice_obligation() == table::DiceObligation::MUST_ROLL);
            CHECK(phase.get_current_player() == table::Color::WHITE);
        }

        SECTION("DicePair explicit")
        {
            auto phase = table::RoGamePhase(state_input, table::Color::WHITE, table::DicePair(2, 3)); //se initializeaza cu dubla de inceput

            CHECK(phase.get_phase_type() == table::PhaseType::GAME_PHASE);
            CHECK(phase.get_current_board_state() == state_input);
            CHECK(phase.get_dice_obligation() == table::DiceObligation::CAN_NOT_ROLL);
            CHECK(phase.get_current_player() == table::Color::WHITE);
            CHECK(phase.get_current_dices() == table::DicePair(2, 3));
        }
    }
}

