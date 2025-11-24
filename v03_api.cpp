#include "v03_api.hpp"
#include "skaiciavimas.hpp"
#include "ivestis.hpp"
#include "formatas.hpp"
#include "sort.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <type_traits>
#include <list>
#include <vector>
#include <iterator>

using clock_t_v03 = std::chrono::steady_clock;

template<typename Tag>
ContainerT<Tag, Studentas> read_all(const std::string& path, long long* out_read_ms) {
    auto start = clock_t_v03::now();
    ContainerT<Tag, Studentas> v;
    skaityti_is_failo(path, v);
    auto end = clock_t_v03::now();
    if (out_read_ms) {
        *out_read_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    return v;
}

static inline bool is_kietas(const Studentas& s, int method) {
    return s.galutinis(method) >= 5.0;
}

template<typename Tag>
void split_groups(ContainerT<Tag, Studentas>& all,
    ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int method,
    long long* out_split_ms)
{
    auto start = clock_t_v03::now();

    for (auto& s : all) {
        if (is_kietas(s, method)) kiet.emplace_back(s);
        else varg.emplace_back(s);
    }

    auto end = clock_t_v03::now();
    if (out_split_ms) {
        *out_split_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template<typename Tag>
void split_groups_remove(ContainerT<Tag, Studentas>& all,
    ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int method,
    long long* out_split_ms)
{
    auto start = clock_t_v03::now();

    using Cont = ContainerT<Tag, Studentas>;

    if constexpr (std::is_same_v<Cont, std::vector<Studentas>>) {
        std::copy_if(all.begin(), all.end(),
            std::back_inserter(kiet),
            [&](const Studentas& s) { return is_kietas(s, method); });

        auto it = std::remove_if(all.begin(), all.end(),
            [&](const Studentas& s) { return is_kietas(s, method); });

        varg.assign(all.begin(), it);
        all.erase(it, all.end());
    }
    else {
        for (auto it = all.begin(); it != all.end();) {
            if (is_kietas(*it, method)) {
                auto cur = it++;
                kiet.splice(kiet.end(), all, cur);
            }
            else {
                ++it;
            }
        }
        varg.splice(varg.end(), all);
    }

    auto end = clock_t_v03::now();
    if (out_split_ms) {
        *out_split_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template<typename Tag>
void split_groups_partition(ContainerT<Tag, Studentas>& all,
    ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int method,
    long long* out_split_ms)
{
    auto start = clock_t_v03::now();

    auto it = std::partition(all.begin(), all.end(),
        [&](const Studentas& s) { return !is_kietas(s, method); });

    for (auto i = all.begin(); i != it; ++i) varg.emplace_back(*i);
    for (auto i = it; i != all.end(); ++i) kiet.emplace_back(*i);

    auto end = clock_t_v03::now();
    if (out_split_ms) {
        *out_split_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template<typename Tag>
void sort_one(ContainerT<Tag, Studentas>& c, int rikiavimas) {
    if (rikiavimas == 0) return;
    using Cont = ContainerT<Tag, Studentas>;
    if constexpr (std::is_same_v<Cont, std::list<Studentas>>) {
        if (rikiavimas == 1) {
            c.sort(less_pavarde_vardas);
        }
        else {
            c.sort(less_vardas_pavarde);
        }
    }
    else {
        if (rikiavimas == 1) {
            std::sort(c.begin(), c.end(), less_pavarde_vardas);
        }
        else {
            std::sort(c.begin(), c.end(), less_vardas_pavarde);
        }
    }
}

template<typename Tag>
void sort_groups(ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int rikiavimas,
    long long* out_sort_ms)
{
    auto start = clock_t_v03::now();

    sort_one<Tag>(varg, rikiavimas);
    sort_one<Tag>(kiet, rikiavimas);

    auto end = clock_t_v03::now();
    if (out_sort_ms) {
        *out_sort_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template<typename Tag>
void write_groups(const ContainerT<Tag, Studentas>& varg,
    const ContainerT<Tag, Studentas>& kiet,
    int method,
    long long* out_write_ms)
{
    auto start = clock_t_v03::now();

    using Cont = ContainerT<Tag, Studentas>;

    if constexpr (std::is_same_v<Cont, std::vector<Studentas>>) {
        std::ofstream out_varg("vargsiukai.txt");
        std::ofstream out_kiet("kietiakai.txt");
        isvesti_rezultatus(out_varg, varg, method);
        isvesti_rezultatus(out_kiet, kiet, method);
    }
    else {
        std::ofstream out_varg("vargsiukai.txt");
        std::ofstream out_kiet("kietiakai.txt");
        isvesti_rezultatus(out_varg, varg, method);
        isvesti_rezultatus(out_kiet, kiet, method);
    }

    auto end = clock_t_v03::now();
    if (out_write_ms) {
        *out_write_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template ContainerT<VectorTag, Studentas> read_all<VectorTag>(const std::string&, long long*);
template ContainerT<ListTag, Studentas> read_all<ListTag>(const std::string&, long long*);

template void split_groups<VectorTag>(ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    int, long long*);
template void split_groups<ListTag>(ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    int, long long*);

template void split_groups_remove<VectorTag>(ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    int, long long*);
template void split_groups_remove<ListTag>(ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    int, long long*);

template void split_groups_partition<VectorTag>(ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    int, long long*);
template void split_groups_partition<ListTag>(ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    int, long long*);

template void sort_groups<VectorTag>(
    ContainerT<VectorTag, Studentas>&,
    ContainerT<VectorTag, Studentas>&,
    int, long long*);
template void sort_groups<ListTag>(
    ContainerT<ListTag, Studentas>&,
    ContainerT<ListTag, Studentas>&,
    int, long long*);

template void write_groups<VectorTag>(
    const ContainerT<VectorTag, Studentas>&,
    const ContainerT<VectorTag, Studentas>&,
    int, long long*);
template void write_groups<ListTag>(
    const ContainerT<ListTag, Studentas>&,
    const ContainerT<ListTag, Studentas>&,
    int, long long*);
