#include "skaiciavimas.hpp"
#include <algorithm>

double vidurkis(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double sum = 0.0;
    for (int v : pazymiai) sum += v;
    return sum / pazymiai.size();
}

double mediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    std::size_t n = pazymiai.size();
    if (n % 2 == 0) return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) * 0.5;
    return pazymiai[n / 2];
}

double galutinis_vidurkis(const Studentas& s) {
    return s.galutinis(1);
}

double galutinis_mediana(const Studentas& s) {
    return s.galutinis(2);
}
