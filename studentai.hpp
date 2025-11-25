#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>

class Studentas {
private:
    std::string v_;
    std::string p_;
    std::vector<int> nd_;
    int egz_;

public:
    Studentas()
        : v_(), p_(), nd_(), egz_(0) {
    }

    Studentas(const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& nd,
        int egz)
        : v_(vardas), p_(pavarde), nd_(nd), egz_(egz) {
    }

    ~Studentas() = default;

    Studentas(const Studentas& kitas)
        : v_(kitas.v_), p_(kitas.p_), nd_(kitas.nd_), egz_(kitas.egz_) {
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

    // Getteriai
    const std::string& vardas() const {
        return v_;
    }

    const std::string& pavarde() const {
        return p_;
    }

    const std::vector<int>& nd() const {
        return nd_;
    }

    int egzaminas() const {
        return egz_;
    }

    void nustatyti_varda(const std::string& vardas) {
        v_ = vardas;
    }

    void nustatyti_pavarde(const std::string& pavarde) {
        p_ = pavarde;
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
        double suma = std::accumulate(nd_.begin(), nd_.end(), 0.0);
        return suma / nd_.size();
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
        os << s.pavarde() << " " << s.vardas() << " ";
        for (int x : s.nd_) os << x << " ";
        os << s.egz_;
        return os;
    }

   
    friend std::istream& operator>>(std::istream& is, Studentas& s) {
        std::string pav, var;
        if (!(is >> pav >> var)) return is;

        std::vector<int> nd;
        int x;
        while (is >> x) nd.push_back(x);

        if (nd.empty()) {
            s = Studentas(var, pav, {}, 0);
        }
        else {
            int egz = nd.back();
            nd.pop_back();
            s = Studentas(var, pav, nd, egz);
        }
        return is;
    }
};
