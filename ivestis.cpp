#include "ivestis.hpp"

#include "skaiciavimas.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <cctype>

bool try_parse_int(const std::string& tok, int& out) {
    if (tok.empty()) return false;
    std::size_t i = 0;
    if (tok[0] == '+' || tok[0] == '-') i = 1;
    if (i == tok.size()) return false;
    for (; i < tok.size(); ++i) {
        if (!std::isdigit((unsigned char)tok[i])) return false;
    }
    try {
        long long v = std::stoll(tok);
        if (v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max()) return false;
        out = static_cast<int>(v);
        return true;
    }
    catch (...) {
        return false;
    }
}

void ivedimas_is_konsoles(std::vector<Studentas>& grupe) {
    grupe.clear();

    int n;
    std::cout << "Iveskite studentu skaiciu: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Neteisingas skaicius.\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        Studentas s;
        std::cout << "Iveskite " << (i + 1) << "-ojo studento pavarde ir varda: ";
        std::cin >> s.pavarde >> s.vardas;

        int nd_kiekis;
        std::cout << "Kiek namu darbu pazymiu? ";
        std::cin >> nd_kiekis;
        s.nd.clear();
        s.nd.reserve(nd_kiekis);
        std::cout << "Iveskite " << nd_kiekis << " pazymius: ";
        for (int j = 0; j < nd_kiekis; ++j) {
            int v;
            std::cin >> v;
            s.nd.push_back(v);
        }

        std::cout << "Iveskite egzamino pazymi: ";
        std::cin >> s.egzaminas;

        grupe.push_back(std::move(s));
    }
}

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Klaida atidarant faila: " << path << "\n";
        return false;
    }

    grupe.clear();

    std::string eilute;
    std::size_t nr = 0;
    while (std::getline(in, eilute)) {
        ++nr;
        if (nr == 1) continue;
        if (eilute.find_first_not_of(" \t\r\n") == std::string::npos) continue;

        std::istringstream iss(eilute);
        Studentas s;
        if (!(iss >> s.pavarde >> s.vardas)) continue;

        std::vector<int> visi;
        std::string tok;
        while (iss >> tok) {
            int v;
            if (try_parse_int(tok, v) && v >= 1 && v <= 10) visi.push_back(v);
        }
        if (visi.empty()) continue;

        s.egzaminas = visi.back();
        s.nd.assign(visi.begin(), visi.end() - 1);

        grupe.push_back(std::move(s));
    }
    return true;
}

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe, int method) {
    if (!skaityti_is_failo(path, grupe)) return false;
    for (auto& s : grupe) {
        apskaiciuoti_galutini(s, method);
    }
    return true;
}

bool skaityti_is_failo(const std::string& path, std::list<Studentas>& grupe, int method) {
    std::vector<Studentas> tmp;
    if (!skaityti_is_failo(path, tmp, method)) return false;
    grupe.clear();
    for (auto& s : tmp) grupe.push_back(std::move(s));
    return true;
}
