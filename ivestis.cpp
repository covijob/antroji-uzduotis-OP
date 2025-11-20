#include "ivestis.hpp"
#include "skaiciavimas.hpp"
#include <iostream>
#include <fstream>
#include <limits>

void ivedimas_is_konsoles(std::vector<Studentas>& grupe) {
    grupe.clear();
    int n;
    std::cin >> n;
    if (!std::cin || n <= 0) return;

    grupe.reserve(n);
    for (int i = 0; i < n; ++i) {
        Studentas s;
        std::cin >> s.pavarde >> s.vardas;

        int nd_kiekis;
        std::cin >> nd_kiekis;
        s.nd.reserve(nd_kiekis);
        for (int j = 0; j < nd_kiekis; ++j) {
            int v;
            std::cin >> v;
            s.nd.push_back(v);
        }
        std::cin >> s.egzaminas;
        grupe.push_back(std::move(s));
    }
}

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe) {
    std::ifstream in(path);
    if (!in) return false;

    grupe.clear();
    grupe.reserve(10000);

    std::string pav, vard;
    std::string line;
    std::getline(in, line);

    while (true) {
        if (!(in >> pav >> vard)) break;

        Studentas s;
        s.pavarde = std::move(pav);
        s.vardas = std::move(vard);

        s.nd.clear();
        s.nd.reserve(10);

        int x;
        std::vector<int> tmp;
        tmp.reserve(10);

        while (in >> x) tmp.push_back(x);
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (tmp.empty()) continue;
        s.egzaminas = tmp.back();
        if (tmp.size() > 1) {
            s.nd.assign(tmp.begin(), tmp.end() - 1);
        }

        grupe.push_back(std::move(s));
    }

    return true;
}

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe, int method) {
    if (!skaityti_is_failo(path, grupe)) return false;
    for (auto& s : grupe) apskaiciuoti_galutini(s, method);
    return true;
}

bool skaityti_is_failo(const std::string& path, std::list<Studentas>& grupe, int method) {
    std::vector<Studentas> tmp;
    if (!skaityti_is_failo(path, tmp, method)) return false;
    grupe.assign(std::make_move_iterator(tmp.begin()),
        std::make_move_iterator(tmp.end()));
    return true;
}
