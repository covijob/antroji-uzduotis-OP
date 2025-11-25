#include "ivestis.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

Studentas nuskaityti_studenta(const std::string& eilute) {
    std::istringstream in(eilute);
    Studentas s;
    in >> s;
    return s;
}


bool skaityti_is_failo(const std::string& failas, std::vector<Studentas>& grupe) {
    std::ifstream in(failas);
    if (!in) return false;

    std::string eil;
    std::getline(in, eil);

    while (std::getline(in, eil)) {
        if (eil.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        grupe.push_back(nuskaityti_studenta(eil));
    }
    return true;
}

bool skaityti_is_failo(const std::string& failas, std::list<Studentas>& grupe) {
    std::ifstream in(failas);
    if (!in) return false;

    std::string eil;
    std::getline(in, eil);

    while (std::getline(in, eil)) {
        if (eil.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        grupe.push_back(nuskaityti_studenta(eil));
    }
    return true;
}
