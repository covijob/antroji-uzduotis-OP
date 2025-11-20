#pragma once
#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas = 0;
    double galutinis = 0.0;   
};
// is anksto skaiciuojame galutini bala