#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "studentai.hpp"
#include "skaiciavimas.hpp"
#include "sort.hpp"


TEST_CASE("Studento vidurkis apskaiciuojamas teisingai") {
    SECTION("Keli ND pazymiai") {
        Studentas s("Vardas", "Pavarde", { 10, 8, 6 }, 9);
        REQUIRE(s.vidurkis() == Catch::Approx(8.0));
    }
}

TEST_CASE("Studento mediana: nelyginis ir lyginis", "[mediana]") {

    SECTION("Nelyginis kiekis") {
        Studentas s("A", "B", { 3, 1, 2 }, 0); // surikiavus 1,2,3 -> 2
        REQUIRE(s.mediana() == Catch::Approx(2.0));
    }

    SECTION("Lyginis kiekis") {
        Studentas s("A", "B", { 4, 2, 8, 6 }, 0); // 2,4,6,8 o kam (4+6)/2 = 5
        REQUIRE(s.mediana() == Catch::Approx(5.0));
    }
}

TEST_CASE("sort.hpp: rusiavimas pagal pavarde ir varda", "[sort]") {

    std::vector<Studentas> v = {
        Studentas("Jonas", "Bbb", {1}, 1),
        Studentas("Aiste", "Aaa", {1}, 1),
        Studentas("Zita",  "Bbb", {1}, 1)
    };

    std::sort(v.begin(), v.end(), less_pavarde_vardas);

    REQUIRE(v[0].pavarde() == "Aaa");
    REQUIRE(v[0].vardas() == "Aiste");

    REQUIRE(v[1].pavarde() == "Bbb");
    REQUIRE(v[1].vardas() == "Jonas");

    REQUIRE(v[2].pavarde() == "Bbb");
    REQUIRE(v[2].vardas() == "Zita");
}

