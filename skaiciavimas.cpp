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
    size_t n = pazymiai.size();
    if (n % 2 == 0) return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) * 0.5;
    return pazymiai[n / 2];
}

double galutinis_vidurkis(const Studentas& s) {
    return 0.4 * vidurkis(s.nd) + 0.6 * s.egzaminas;
}

double galutinis_mediana(const Studentas& s) {
    return 0.4 * mediana(s.nd) + 0.6 * s.egzaminas;
}

void apskaiciuoti_galutini(Studentas& s, int method) {
    if (method == 2) s.galutinis = galutinis_mediana(s);
    else s.galutinis = galutinis_vidurkis(s);
}
