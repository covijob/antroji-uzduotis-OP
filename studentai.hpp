#pragma once
#include <string>
#include <vector>

class Studentas {
public:
    Studentas()
        : vardas_{}, pavarde_{}, nd_{}, egzaminas_{ 0 } {
    }

    Studentas(const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& nd,
        int egzaminas)
        : vardas_{ vardas }, pavarde_{ pavarde }, nd_{ nd }, egzaminas_{ egzaminas } {
    }

    Studentas(const Studentas& other)
        : vardas_{ other.vardas_ },
        pavarde_{ other.pavarde_ },
        nd_{ other.nd_ },
        egzaminas_{ other.egzaminas_ } {
    }

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            nd_ = other.nd_;
            egzaminas_ = other.egzaminas_;
        }
        return *this;
    }

    ~Studentas() = default;

    inline const std::string& vardas()  const { return vardas_; }
    inline const std::string& pavarde() const { return pavarde_; }
    inline const std::vector<int>& nd() const { return nd_; }
    inline int egzaminas() const { return egzaminas_; }


private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
};
