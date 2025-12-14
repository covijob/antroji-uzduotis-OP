#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "v03_runner.hpp"

namespace fs = std::filesystem;

struct Strategija {
    int id;
    const char* pavadinimas;
};

void run_benchmarks() {
    std::vector<fs::path> failai;

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (!entry.is_regular_file()) continue;
        const auto& p = entry.path();
        if (p.extension() == ".txt") {
            failai.push_back(p);
        }
    }

    if (failai.empty()) {
        std::cout << "Nerasta .txt failu benchmarkams.\n";
        return;
    }

    std::sort(failai.begin(), failai.end());

    std::cout << "Rasti failai:\n";
    for (const auto& f : failai) {
        std::cout << " - " << f.string() << "\n";
    }

    Strategija strategijos[] = {
        {1, "partition_copy"},
        {2, "remove_if"},
        {3, "partition"}
    };

    int method = 1;
    int rikiavimas = 1;

    for (const auto& failas : failai) {
        std::cout << "\n================================\n";
        std::cout << "Failas: " << failas.string() << "\n";
        std::cout << "================================\n\n";

        std::cout << "Konteineris: std::vector\n\n";
        for (const auto& strat : strategijos) {
            std::cout << "[Strategija " << strat.id << " (" << strat.pavadinimas << ")]\n";
            run_v03<VectorTag>(failas.string(), strat.id, method, rikiavimas);
        }

        std::cout << "\nKonteineris: std::list\n\n";
        for (const auto& strat : strategijos) {
            std::cout << "[Strategija " << strat.id << " (" << strat.pavadinimas << ")]\n";
            run_v03<ListTag>(failas.string(), strat.id, method, rikiavimas);
        }
    }

    std::cout << "\nVisi benchmark testai baigti.\n";
}
