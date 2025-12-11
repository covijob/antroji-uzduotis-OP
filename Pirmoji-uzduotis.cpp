#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <limits>

#include "v03_runner.hpp"
#include "generatorius.hpp"
#include "bench_runner.hpp"
//#include "unit_tests.cpp"

int run_all_tests();

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

void isvesti_faila_i_konsole(const std::string& pavadinimas, const std::string& antraste) {
    std::ifstream in(pavadinimas);
    if (!in) {
        std::cerr << "Nepavyko atidaryti failo: " << pavadinimas << "\n";
        return;
    }
    std::cout << "\n" << antraste << " (" << pavadinimas << "):\n";
    std::string eil;
    while (std::getline(in, eil)) {
        std::cout << eil << "\n";
    }
}

bool yra_tik_raides(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s) {
        if (!std::isalpha(c)) return false;
    }
    return true;
}

int saugus_skaicius_intervale(const std::string& pranesimas, int min, int max) {
    int x;
    for (;;) {
        std::cout << pranesimas;
        if (!(std::cin >> x)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Neteisinga ivestis, bandykite dar karta.\n";
            continue;
        }
        if (x < min || x > max) {
            std::cout << "Reiksme turi buti tarp " << min << " ir " << max << ".\n";
            continue;
        }
        return x;
    }
}

void rankine_ivestis_i_faila(const std::string& failas) {
    std::ofstream out(failas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failas << "\n";
        return;
    }

    int kiek = saugus_skaicius_intervale("Kiek studentu norite ivesti rankiniu budu: ", 1, 1000000);

    for (int i = 0; i < kiek; ++i) {
        std::string vardas, pavarde;

        for (;;) {
            std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
            std::cin >> vardas;
            if (!yra_tik_raides(vardas)) {
                std::cout << "Vardas turi sudaryti tik is raidziu.\n";
                continue;
            }
            break;
        }

        for (;;) {
            std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
            std::cin >> pavarde;
            if (!yra_tik_raides(pavarde)) {
                std::cout << "Pavarde turi sudaryti tik is raidziu.\n";
                continue;
            }
            break;
        }

        std::vector<int> nd;
        std::cout << "Iveskite namu darbu pazymius (0-10). Baigti ivesdami -1.\n";
        for (;;) {
            int paz;
            std::cout << "Pazymys: ";
            if (!(std::cin >> paz)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Neteisinga ivestis, bandykite dar karta.\n";
                continue;
            }
            if (paz == -1) {
                if (nd.empty()) {
                    std::cout << "Privaloma ivesti bent viena namu darbu pazymi.\n";
                    continue;
                }
                break;
            }
            if (paz < 0 || paz > 10) {
                std::cout << "Pazymys turi buti tarp 0 ir 10.\n";
                continue;
            }
            nd.push_back(paz);
        }

        int egz = saugus_skaicius_intervale("Iveskite egzamino pazymi (0-10): ", 0, 10);

        out << pavarde << " " << vardas << " ";
        for (int x : nd) out << x << " ";
        out << egz << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int rezimas = 0;
    std::cout << "Pasirinkite rezima:\n";
    std::cout << "1 - Benchmark rezimas (bench_runner: visi txt, visos strategijos, visi konteineriai)\n";
    std::cout << "2 - Iprastas rezimas (darbas su vienu pasirinktu failu / generavimas)\n";
    std::cout << "3 - Rankine studentu ivestis\n";
    std::cout << "4 – Unit Tests\n";
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

    bool rankine = false;

    if (rezimas == 2) {
    }
    else if (rezimas == 3) {
        rankine = true;
    }

    else if (rezimas == 4) {
        int result = run_all_tests();
        std::cout << "\nTestai baigti. " << result << "\n";
        return result;
    }

    else {
        std::cerr << "Neteisingas rezimo pasirinkimas.\n";
        return 1;
    }

    std::string failas;

    if (rankine) {
        failas = "rankine_ivestis.txt";
        rankine_ivestis_i_faila(failas);
    }
    else {
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

    int isvesti_konsole = 0;
    std::cout << "Ar papildomai isvesti rezultatus i konsole? (1 - taip, 0 - ne): ";
    std::cin >> isvesti_konsole;

    if (!std::cin || (isvesti_konsole != 0 && isvesti_konsole != 1)) {
        std::cerr << "Neteisingas pasirinkimas.\n";
        return 1;
    }

    if (kont == 1) {
        run_v03<VectorTag>(failas, strategija, method, rikiavimas);
    }
    else {
        run_v03<ListTag>(failas, strategija, method, rikiavimas);
    }

    if (isvesti_konsole == 1) {
        isvesti_faila_i_konsole("kietiakai.txt", "Kietiakai");
        isvesti_faila_i_konsole("vargsiukai.txt", "Vargsiukai");
    }

    return 0;
}
