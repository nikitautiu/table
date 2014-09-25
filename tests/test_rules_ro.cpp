#inclued "catch.hpp"
#include "../src/variants/rules_ro.hpp"

TEST_CASE("RoDiceHelper functioneaza cum trebuie", "[ro_rules][RoDiceHelper][failing]")
{
    SECTION("se castiga din prima")
    {
        auto helper = table::internal::RoDiceHelper(table::Color::WHITE);
        helper.give_dice(std::make_pair(2, 3));
        helper.give_dice(std::make_pair(5, 3));

        REQUIRE(helper.is_done());
        REUQIRE(helper.get_wiiner() == table::Color::BLACK);

        auto double_pair = helper.get_double_pair();
        REQUIRE(!helper.first());
    }
}
