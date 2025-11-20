#pragma once
#include "studentai.hpp"

inline bool less_pavarde_vardas(const Studentas& a, const Studentas& b) {
    if (a.pavarde != b.pavarde) return a.pavarde < b.pavarde;
    return a.vardas < b.vardas;
}
