#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>


#include "v03_runner.hpp"
#include "konteineriu_pasirinkimas.hpp"
#include "generatorius.hpp"
#include "bench_runner.hpp"

std::size_t nustatyti_eiluciu_kieki(const std::string& failas) {
    std::string pref = "studentai_";
    auto p = failas.find(pref);
    if (p == std::string::npos) return 0;
    p += pref.size();
    auto k = failas.find_first_not_of("0123456789", p);
    if (k == std::string::npos) return 0;
    std::string sk = failas.substr(p, k - p);
    try {
        return static_cast<std::size_t>(std::stoll(sk));
    }
    catch (...) {
        return 0;
    }
}

int main() {

    std::ios::sync_with_stdio(false);

    std::cout << "Pasirinkite rezima:\n";
    std::cout << "1 - Iprastas naudojimas (failu generavimas/greitas testavimas)\n";
    std::cout << "2 - Benchmark (visi failai, konteineriai ir strategijos)\n";
    int rezimas;
    std::cin >> rezimas;

    if (rezimas == 2) {
        run_benchmarks();
        return 0;
    }

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);



    int veiksmas = 0;
    std::cout << "Pasirinkite veiksma:\n";
    std::cout << "1 - Naudoti jau esama .txt faila\n";
    std::cout << "2 - Sugeneruoti naujus .txt failus (100..10000000 eiluciu)\n";
    std::cout << "Jusu pasirinkimas: ";
    std::cin >> veiksmas;

    if (veiksmas == 2) {
        std::random_device rd;
        std::mt19937 rng(rd());

        constexpr std::size_t K = 6;
        const std::size_t dydziai[] = { 100, 1000, 10000, 100000, 1000000, 10000000 };

        for (std::size_t N : dydziai) {
            std::string vardas = "studentai_" + std::to_string(N) + "_K6.txt";
            generuoti_faila(rng, vardas, N, K);
            std::cout << "Sugeneruotas failas: " << vardas << "\n";
        }
        std::cout << "Visi failai sugeneruoti.\n\n";
    }

    std::vector<std::string> failai;
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (!entry.is_regular_file()) continue;
        auto name = entry.path().filename().string();
        if (name.size() >= 4 && name.substr(name.size() - 4) == ".txt") {
            failai.push_back(name);
        }
    }

    if (failai.empty()) {
        std::cout << "Aplanke nerasta jokiu .txt failu.\n";
        return 0;
    }

    std::cout << "Rasti .txt failai:\n";
    for (std::size_t i = 0; i < failai.size(); ++i) {
        std::cout << (i + 1) << ") " << failai[i] << "\n";
    }

    int pasirinktas = 0;
    while (true) {
        std::cout << "Pasirinkite failo numeri: ";
        std::cin >> pasirinktas;
        if (pasirinktas >= 1 && static_cast<std::size_t>(pasirinktas) <= failai.size()) break;
        std::cout << "Neteisingas numeris, bandykite dar karta.\n";
    }

    std::string failas = failai[pasirinktas - 1];
    std::size_t n_eiluciu = nustatyti_eiluciu_kieki(failas);

    int kont = 0;
    int strategija = 0;
    int method = 1;
    int rikiavimas = 1;

    std::cout << "\nPasirinktas failas: " << failas << "\n";
    if (n_eiluciu > 0) {
        std::cout << "Apskaiciuota eiluciu: " << n_eiluciu << "\n";
    }

    std::cout << "Pasirinkite konteineri (1 - vector, 2 - list): ";
    std::cin >> kont;

    std::cout << "Pasirinkite skaidymo strategija (1, 2 arba 3): ";
    std::cin >> strategija;

    std::cout << "Pasirinkite galutinio balo metoda (1 - vidurkis, 2 - mediana): ";
    std::cin >> method;

    std::cout << "Ar rikiuoti rezultatus? (0 - ne, 1 - pagal pavarde/varda): ";
    std::cin >> rikiavimas;

    if (kont == 1) {
        run_v03<VectorTag>(failas, strategija, method, rikiavimas);
    }
    else {
        run_v03<ListTag>(failas, strategija, method, rikiavimas);
    }

    return 0;
}
