#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

#include "konteineriu_pasirinkimas.hpp"
#include "v03_runner.hpp"
#include "bench_runner.hpp"

namespace fs = std::filesystem;

void run_benchmarks() {
    std::vector<fs::path> failai;

    for (const auto& entry : fs::directory_iterator(".")) {
        if (!entry.is_regular_file()) continue;
        const auto& p = entry.path();
        if (p.extension() == ".txt" &&
            p.filename().string().rfind("studentai_", 0) == 0) {
            failai.push_back(p);
        }
    }

    if (failai.empty()) {
        std::cout << "Nerasta studentu failu kataloge.\n";
        return;
    }

    std::sort(failai.begin(), failai.end());

    std::cout << "Rasti failai:\n";
    for (auto& f : failai) {
        std::cout << " - " << f.string() << "\n";
    }

    int method = 1;      // 1 - vidurkis (kaip pas tave projekte)
    int rikiavimas = 1;  // 1 - rikiuoti pagal pavarde/varda

    struct StrategijaCfg {
        int id;
        const char* pavadinimas;
    };

    StrategijaCfg strategijos[] = {
        {1, "partition_copy"},
        {2, "remove_if"},
        {3, "partition"}
    };

    for (const auto& failas : failai) {
        std::cout << "\n========================================\n";
        std::cout << "Failas: " << failas.string() << "\n";

        for (int container = 0; container < 2; ++container) {
            std::cout << "\n----------------------------------------\n";
            if (container == 0)
                std::cout << "Konteineris: std::vector\n";
            else
                std::cout << "Konteineris: std::list\n";

            for (const auto& strat : strategijos) {
                std::cout << "\n[Strategija " << strat.id
                    << " (" << strat.pavadinimas << ")]\n";

                if (container == 0) {
                    run_v03<VectorTag>(
                        failas.string(),
                        strat.id,   // strategija
                        method,
                        rikiavimas
                    );
                }
                else {
                    run_v03<ListTag>(
                        failas.string(),
                        strat.id,
                        method,
                        rikiavimas
                    );
                }
            }
        }
    }

    std::cout << "\nVisi benchmark testai baigti.\n";
}
