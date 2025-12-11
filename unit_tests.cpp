#define CATCH_CONFIG_RUNNER
#include "catch_amalgamated.hpp"

#include "studentai.hpp"
#include "skaiciavimas.hpp"
#include "sort.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

int run_all_tests() {
    Catch::Session session;
    return session.run();
}

// ===== TESTAI =====

TEST_CASE("Studento vidurkis apskaiciuojamas teisingai") {
    SECTION("Keli ND pazymiai") {
        Studentas s("Vardas", "Pavarde", { 10, 8, 6 }, 9);
        REQUIRE(s.vidurkis() == Catch::Approx(8.0));
    }
}
