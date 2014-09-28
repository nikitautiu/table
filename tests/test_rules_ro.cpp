#include "catch.hpp"
#include "../src/variants/rules_ro.hpp"

TEST_CASE("RoDiceHelper functioneaza cum trebuie", "[ro_rules][RoDiceHelper]")
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



