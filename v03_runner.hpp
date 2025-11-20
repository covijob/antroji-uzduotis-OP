#pragma once

#include <iostream>
#include <type_traits>
#include <string>

#include "konteineriu_pasirinkimas.hpp"
#include "v03_api.hpp"

template<typename Tag>
void run_v03(const std::string& failas, int strategija, int method, int rikiavimas) {
    long long t_read = 0, t_split = 0, t_sort = 0, t_write = 0;

    auto all = read_all<Tag>(failas, method, &t_read);

    ContainerT<Tag, Studentas> varg;
    ContainerT<Tag, Studentas> kiet;

    split_groups<Tag>(all, varg, kiet, strategija, &t_split);
    sort_groups<Tag>(varg, kiet, rikiavimas, &t_sort);
    write_groups<Tag>(varg, kiet, method, &t_write);

    std::cout << "=== v0.3 (" << (std::is_same_v<Tag, VectorTag> ? "vector" : "list") << ") ===\n";
    std::cout << "Skaitymas: " << t_read << " ms\n";
    std::cout << "Skaidymas: " << t_split << " ms\n";
    std::cout << "Rikiavimas: " << t_sort << " ms\n";
    std::cout << "Rasymas: " << t_write << " ms\n";
    std::cout << "Is viso: " << (t_read + t_split + t_sort + t_write) << " ms\n";

    if (!all.empty()) {
        std::cout << "Pirmo studento atminties adresas: " << &(*all.begin()) << "\n";
    }

    std::cout << "---------------------------------------\n";
}

template<typename Tag>
void run_v03(const std::string& failas, int method, int rikiavimas) {
    int strategija = 3;
    run_v03<Tag>(failas, strategija, method, rikiavimas);
}
