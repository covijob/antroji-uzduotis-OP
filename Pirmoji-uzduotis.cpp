#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <fstream>
#include <algorithm>

#include "v03_runner.hpp"
#include "konteineriu_pasirinkimas.hpp"
#include "generatorius.hpp"
#include "bench_runner.hpp"

namespace fs = std::filesystem;

std::size_t nustatyti_eiluciu_kieki(const std::string& failas) {
    std::ifstream in(failas);
    if (!in) return 0;
    std::size_t n = 0;
    std::string line;
    while (std::getline(in, line)) {
        ++n;
    }
    return n;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rezimas = 0;
    std::cout << "Pasirinkite rezima:\n";
    std::cout << "1 - Benchmark rezimas (bench_runner: visi txt, visos strategijos, visi konteineriai)\n";
    std::cout << "2 - Iprastas rezimas (darbas su vienu pasirinktu failu / generavimas)\n";
    std::cout << "Jusu pasirinkimas: ";
    std::cin >> rezimas;

    if (!std::cin) {
        std::cerr << "Neteisinga ivestis.\n";
        return 1;
    }

    if (rezimas == 1) {
        run_benchmarks();
        return 0;
    }

    if (rezimas != 2) {
        std::cerr << "Neteisingas rezimo pasirinkimas.\n";
        return 1;
    }

    std::string failas;
    int generuoti = 0;
    std::cout << "Ar norite generuoti nauja faila? (1 - taip, 0 - ne): ";
    std::cin >> generuoti;

    if (!std::cin) {
        std::cerr << "Neteisinga ivestis.\n";
        return 1;
    }

    if (generuoti == 1) {
        std::string vardas;
        std::size_t kiek = 0;
        std::size_t nd_kiekis = 0;

        std::cout << "Iveskite generuojamo failo pavadinima: ";
        std::cin >> vardas;

        std::cout << "Kiek studentu generuoti: ";
        std::cin >> kiek;

        std::cout << "Kiek namu darbu pazymiu generuoti kiekvienam studentui: ";
        std::cin >> nd_kiekis;

        if (!std::cin || kiek == 0 || nd_kiekis == 0) {
            std::cerr << "Neteisingi generavimo parametrai.\n";
            return 1;
        }

        std::random_device rd;
        std::mt19937 rng(rd());
        generuoti_faila(rng, vardas, kiek, nd_kiekis);
        failas = vardas;
    }
    else {
        std::vector<std::string> txt_failai;

        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (!entry.is_regular_file()) continue;
            const auto& p = entry.path();
            if (p.extension() == ".txt") {
                txt_failai.push_back(p.filename().string());
            }
        }

        if (txt_failai.empty()) {
            std::cerr << "Nerasta .txt failu.\n";
            return 1;
        }

        std::sort(txt_failai.begin(), txt_failai.end());

        std::cout << "Rasti .txt failai:\n";
        for (std::size_t i = 0; i < txt_failai.size(); ++i) {
            std::size_t n = nustatyti_eiluciu_kieki(txt_failai[i]);
            std::cout << i + 1 << " - " << txt_failai[i];
            if (n > 0) std::cout << " (" << n << " eiluciu)";
            std::cout << "\n";
        }

        std::size_t idx = 0;
        std::cout << "Pasirinkite faila pagal numeri: ";
        std::cin >> idx;

        if (!std::cin || idx < 1 || idx > txt_failai.size()) {
            std::cerr << "Neteisingas pasirinkimas.\n";
            return 1;
        }

        failas = txt_failai[idx - 1];
    }

    int kont = 0;
    std::cout << "Pasirinkite konteineri (1 - vector, 2 - list): ";
    std::cin >> kont;

    if (!std::cin || (kont != 1 && kont != 2)) {
        std::cerr << "Neteisingas konteinerio pasirinkimas.\n";
        return 1;
    }

    int method = 1;
    std::cout << "Pasirinkite galutinio balo skaiciavimo metoda (1 - vidurkis, 2 - mediana): ";
    std::cin >> method;

    if (!std::cin || (method < 1 || method > 2)) {
        std::cerr << "Neteisingas metodo pasirinkimas.\n";
        return 1;
    }

    int rikiavimas = 1;
    std::cout << "Ar rikiuoti rezultatus pagal pavarde? (1 - taip, 0 - ne): ";
    std::cin >> rikiavimas;

    if (!std::cin || (rikiavimas != 0 && rikiavimas != 1)) {
        std::cerr << "Neteisingas rikiavimo pasirinkimas.\n";
        return 1;
    }

    int strategija = 0;
    std::cout << "Pasirinkite strategija (1 - partition_copy, 2 - remove_if, 3 - partition): ";
    std::cin >> strategija;

    if (!std::cin || strategija < 1 || strategija > 3) {
        std::cerr << "Neteisingas strategijos pasirinkimas.\n";
        return 1;
    }

    if (kont == 1) {
        run_v03<VectorTag>(failas, strategija, method, rikiavimas);
    }
    else {
        run_v03<ListTag>(failas, strategija, method, rikiavimas);
    }

    return 0;
}
