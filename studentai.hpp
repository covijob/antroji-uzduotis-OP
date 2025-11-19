#pragma once
#include <string>
#include <vector>

#pragma once
#include <string>
#include <vector>

class Studentas {
public:
    Studentas()
        : vardas{}, pavarde{}, nd{}, egzaminas{ 0 } {
    }

    Studentas(const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& nd,
        int egzaminas)
        : vardas{ vardas }, pavarde{ pavarde }, nd{ nd }, egzaminas{ egzaminas } {
    }

    Studentas(const Studentas& other)
        : vardas{ other.vardas },
        pavarde{ other.pavarde },
        nd{ other.nd },
        egzaminas{ other.egzaminas } {
    }

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            nd = other.nd;
            egzaminas = other.egzaminas;
        }
        return *this;
    }

    ~Studentas() = default;

    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzaminas;
};
