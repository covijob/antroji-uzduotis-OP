#pragma once
#include <string>
#include <vector>
#include <istream> 
#include <cstdio>  
#include <algorithm>


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

    void setVardas(const std::string& v) { vardas_ = v; }
    void setPavarde(const std::string& p) { pavarde_ = p; }

    void clearNd() { nd_.clear(); }
    void addNd(int v) { nd_.push_back(v); }

    void setEgzaminas(int v) { egzaminas_ = v; }

    std::istream& readStudent(std::istream& is) {
        is >> vardas_ >> pavarde_;

        nd_.clear();
        int x;
        while (is >> x) {
            nd_.push_back(x);
            if (is.peek() == '\n' || is.peek() == EOF) break;
        }

        if (!nd_.empty()) {
            egzaminas_ = nd_.back();
            nd_.pop_back();
        }
        else {
            egzaminas_ = 0;
        }

        return is;
    }

    double galutinis(int metodas) const {
        if (metodas == 2) return mediana();
        return vidurkis();
    }

    double vidurkis() const {
        if (nd_.empty()) return egzaminas_;
        double suma = 0.0;
        for (int v : nd_) suma += v;
        return 0.4 * (suma / nd_.size()) + 0.6 * egzaminas_;
    }

    double mediana() const {
        if (nd_.empty()) return egzaminas_;
        std::vector<int> temp = nd_;
        std::sort(temp.begin(), temp.end());
        double m;
        size_t n = temp.size();
        if (n % 2 == 0)
            m = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
        else
            m = temp[n / 2];
        return 0.4 * m + 0.6 * egzaminas_;
    }

private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzaminas_;
};
