#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "zmogus.hpp"
#include "studentu_dll.h"


class Studentas : public Zmogus {
private:
    std::vector<int> nd_;
    int egz_;

public:
    Studentas()
        : Zmogus(), nd_(), egz_(0) {
    }

    Studentas(const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& nd,
        int egz)
        : Zmogus(vardas, pavarde), nd_(nd), egz_(egz) {
    }

    ~Studentas() = default;

    Studentas(const Studentas& kitas)
        : Zmogus(kitas), nd_(kitas.nd_), egz_(kitas.egz_) {
    }

    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {
            v_ = kitas.v_;
            p_ = kitas.p_;
            nd_ = kitas.nd_;
            egz_ = kitas.egz_;
        }
        return *this;
    }

    void spausdinti(std::ostream& os) const override {
        os << pavarde() << " " << vardas() << " ";

        for (int x : nd_) {
            os << x << " ";
        }

        os << egz_;
    }

    void nuskaityti(std::istream& is) {
        v_.clear();
        p_.clear();
        nd_.clear();
        egz_ = 0;

        std::string pav, var;
        if (!(is >> pav >> var)) {
            return;
        }

        std::vector<int> nd_tmp;
        int x;
        while (is >> x) {
            nd_tmp.push_back(x);
        }

        if (nd_tmp.empty()) {
            p_ = pav;
            v_ = var;
            nd_.clear();
            egz_ = 0;
        }
        else {
            egz_ = nd_tmp.back();
            nd_tmp.pop_back();
            nd_ = nd_tmp;
            p_ = pav;
            v_ = var;
        }

        is.clear();
    }

    const std::vector<int>& nd() const {
        return nd_;
    }

    int egzaminas() const {
        return egz_;
    }

    void prideti_nd(int pazymys) {
        nd_.push_back(pazymys);
    }

    void nustatyti_nd(const std::vector<int>& nd) {
        nd_ = nd;
    }

    void nustatyti_egzamina(int egz) {
        egz_ = egz;
    }

    double vidurkis() const {
        if (nd_.empty()) return 0.0;
        return dll_vidurkis(nd_.data(), static_cast<int>(nd_.size()));
    }


    double mediana() const {
        if (nd_.empty()) return 0.0;
        std::vector<int> k = nd_;
        std::sort(k.begin(), k.end());
        std::size_t n = k.size();
        if (n % 2 == 1) return static_cast<double>(k[n / 2]);
        return (k[n / 2 - 1] + k[n / 2]) / 2.0;
    }

    double galutinis(int method) const {
        double nd_rez = (method == 1) ? vidurkis() : mediana();
        return 0.4 * nd_rez + 0.6 * egz_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Studentas& s) {
        s.spausdinti(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Studentas& s) {
        s.nuskaityti(is);
        return is;
    }
};

inline double galutinis_vidurkis(const Studentas& s) {
    return s.galutinis(1);  
}

inline double galutinis_mediana(const Studentas& s) {
    return s.galutinis(2);  
}
