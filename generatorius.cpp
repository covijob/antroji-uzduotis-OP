#include "generatorius.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

void generuoti_faila(std::mt19937& rng,
    const std::string& vardas,
    std::size_t kiek,
    std::size_t nd_kiekis)
{
    std::uniform_int_distribution<int> pazymys(1, 10);

    std::ofstream out(vardas);
    out << "Pavarde Vardas ";
    for (std::size_t i = 0; i < nd_kiekis; ++i) out << "ND" << i + 1 << " ";
    out << "Egzaminas\n";

    for (std::size_t i = 0; i < kiek; ++i) {
        out << "Pavarde" << i << " "
            << "Vardas" << i << " ";

        for (std::size_t j = 0; j < nd_kiekis; ++j) {
            out << pazymys(rng) << " ";
        }

        out << pazymys(rng) << "\n";
    }
}
