#pragma once
#include <random>
#include <string>

void generuoti_faila(std::mt19937& rng,
    const std::string& vardas,
    std::size_t kiek,
    std::size_t nd_kiekis);
