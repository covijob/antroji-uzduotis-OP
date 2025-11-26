#include "skaiciavimas.hpp"
#include <algorithm>

double galutinis_vidurkis(const Studentas& s) {
    return s.galutinis(1);
}

double galutinis_mediana(const Studentas& s) {
    return s.galutinis(2);
}
