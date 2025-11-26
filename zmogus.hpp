#pragma once
#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string v_;
    std::string p_;

public:
    Zmogus() = default;

    Zmogus(const std::string& vardas, const std::string& pavarde)
        : v_(vardas), p_(pavarde) {
    }

    virtual ~Zmogus() = default;

    const std::string& vardas() const {
        return v_;
    }

    const std::string& pavarde() const {
        return p_;
    }

    virtual void spausdinti(std::ostream& os) const = 0;
};
