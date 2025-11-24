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

    std::string line;
    std::size_t n = 0;
    bool pirmas = true;

    while (std::getline(in, line)) {
        if (pirmas) {
            pirmas = false;
            continue;
        }
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
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
        std::cerr << "Neteisingas pasirinkimas.\n";
        return 1;
    }

    int veiksmas = 0;
    std::cout << "\nPasirinkite veiksma:\n";
    std::cout << "1 - Naudoti jau esama .txt faila\n";
    std::cout << "2 - Sugeneruoti naujus .txt failus (100..10000000 eiluciu)\n";
    std::cout << "Jusu pasirinkimas: ";
    std::cin >> veiksmas;

    if (!std::cin) {
        std::cerr << "Neteisinga ivestis.\n";
        return 1;
    }

    std::string failas;

    if (veiksmas == 2) {
        std::random_device rd;
        std::mt19937 rng(rd());

        constexpr std::size_t K = 6;
        const std::size_t dydziai[] = { 100, 1000, 10000, 100000, 1000000, 10000000 };

        std::vector<std::string> sugeneruoti;

        for (std::size_t N : dydziai) {
            std::string vardas = "studentai_" + std::to_string(N) + "_K6.txt";
            generuoti_faila(rng, vardas, N, K);
            std::cout << "Sugeneruotas failas: " << vardas << "\n";
            sugeneruoti.push_back(vardas);
        }

        std::cout << "Visi failai sugeneruoti.\n\n";

        std::cout << "Pasirinkite kuri sugeneruota faila naudoti:\n";
        for (std::size_t i = 0; i < sugeneruoti.size(); ++i) {
            std::cout << i + 1 << " - " << sugeneruoti[i] << "\n";
        }

        std::size_t idx = 0;
        std::cout << "Jusu pasirinkimas: ";
        std::cin >> idx;

        if (idx < 1 || idx > sugeneruoti.size()) {
            std::cerr << "Neteisingas pasirinkimas.\n";
            return 1;
        }

        failas = sugeneruoti[idx - 1];
    }
    else if (veiksmas == 1) {
        std::vector<std::string> txt_failai;

        for (const auto& entry : fs::directory_iterator(".")) {
            if (!entry.is_regular_file()) continue;
            auto name = entry.path().filename().string();
            if (name.size() >= 4 && name.substr(name.size() - 4) == ".txt") {
                txt_failai.push_back(name);
            }
        }

        if (txt_failai.empty()) {
            std::cout << "Kataloge nerasta jokiu .txt failu.\n";
            return 0;
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

        if (idx < 1 || idx > txt_failai.size()) {
            std::cerr << "Neteisingas pasirinkimas.\n";
            return 1;
        }

        failas = txt_failai[idx - 1];
    }
    else {
        std::cerr << "Neteisingas pasirinkimas.\n";
        return 1;
    }

    std::cout << "\nPasirinktas failas: " << failas << "\n";

    int kont = 0;
    std::cout << "Pasirinkite konteineri (1 - vector, 2 - list): ";
    std::cin >> kont;

    int method = 0;
    std::cout << "Pasirinkite galutinio balo metoda (1 - vidurkis, 2 - mediana): ";
    std::cin >> method;

    int rikiavimas = 0;
    std::cout << "Ar rikiuoti rezultatus? (0 - ne, 1 - pagal pavarde/varda): ";
    std::cin >> rikiavimas;

    int strategija = 0;
    std::cout << "Pasirinkite strategija (1 - partition_copy, 2 - remove_if, 3 - partition_inplace): ";
    std::cin >> strategija;

    if (strategija < 1 || strategija > 3) {
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
