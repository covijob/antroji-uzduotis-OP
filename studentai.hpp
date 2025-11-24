#pragma once
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class Studentas {
private:
    std::string v_;
    std::string p_;
    std::vector<int> nd_;
    int egz_;
public:
    Studentas() : egz_(0) {}
    Studentas(const std::string& vardas, const std::string& pavarde,
        const std::vector<int>& nd, int egz)
        : v_(vardas), p_(pavarde), nd_(nd), egz_(egz) {
    }

    const std::string& vardas() const { return v_; }
    const std::string& pavarde() const { return p_; }

    void setVardas(const std::string& v) { v_ = v; }
    void setPavarde(const std::string& p) { p_ = p; }

    const std::vector<int>& nd() const { return nd_; }
    int egz() const { return egz_; }

    void setND(const std::vector<int>& v) { nd_ = v; }
    void setEgz(int e) { egz_ = e; }

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
};
