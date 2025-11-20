#include "v03_api.hpp"
#include "ivestis.hpp"
#include "skaiciavimas.hpp"
#include "sort.hpp"
#include "formatas.hpp"

#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <type_traits>

using clock_type = std::chrono::steady_clock;

template<typename Tag>
ContainerT<Tag, Studentas> read_all(const std::string& path, long long* out_read_ms) {
    auto start = clock_type::now();

    ContainerT<Tag, Studentas> c;

    if constexpr (std::is_same_v<Tag, VectorTag>) {
        skaityti_is_failo(path, c);
    }
    else {
        std::vector<Studentas> tmp;
        skaityti_is_failo(path, tmp);
        for (auto& s : tmp) c.push_back(std::move(s));
    }

    auto end = clock_type::now();
    if (out_read_ms) {
        *out_read_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    return c;
}

template<typename Tag>
ContainerT<Tag, Studentas> read_all(const std::string& path, int method, long long* out_read_ms) {
    auto start = clock_type::now();

    ContainerT<Tag, Studentas> c;

    if constexpr (std::is_same_v<Tag, VectorTag>) {
        skaityti_is_failo(path, c, method);
    }
    else {
        skaityti_is_failo(path, c, method);
    }

    auto end = clock_type::now();
    if (out_read_ms) {
        *out_read_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    return c;
}

template<typename Tag>
void split_groups(ContainerT<Tag, Studentas>& all,
    ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int strategija,
    long long* out_split_ms)
{
    auto start = clock_type::now();

    auto is_varg = [](const Studentas& s) {
        return s.galutinis < 5.0;
        };

    varg.clear();
    kiet.clear();

    if constexpr (std::is_same_v<Tag, VectorTag>) {
        varg.reserve(all.size());
        kiet.reserve(all.size());
    }

    if (strategija == 1) {
        for (const auto& s : all) {
            if (is_varg(s)) varg.push_back(s);
            else kiet.push_back(s);
        }
    }
    else if (strategija == 2) {
        for (const auto& s : all) {
            if (is_varg(s)) varg.push_back(s);
        }
        auto it = std::remove_if(all.begin(), all.end(), is_varg);
        all.erase(it, all.end());
        kiet.swap(all);
    }
    else {
        auto it = std::stable_partition(all.begin(), all.end(), is_varg);
        varg.assign(all.begin(), it);
        kiet.assign(it, all.end());
    }

    auto end = clock_type::now();
    if (out_split_ms) {
        *out_split_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template<typename Tag>
void sort_groups(ContainerT<Tag, Studentas>& varg,
    ContainerT<Tag, Studentas>& kiet,
    int rikiavimas,
    long long* out_sort_ms)
{
    auto start = clock_type::now();

    if (rikiavimas == 1) {
        auto cmp = less_pavarde_vardas;

        if constexpr (std::is_same_v<Tag, VectorTag>) {
            std::sort(varg.begin(), varg.end(), cmp);
            std::sort(kiet.begin(), kiet.end(), cmp);
        }
        else {
            varg.sort(cmp);
            kiet.sort(cmp);
        }
    }

    auto end = clock_type::now();
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
    auto start = clock_type::now();

    std::vector<Studentas> v_varg, v_kiet;
    if constexpr (std::is_same_v<Tag, VectorTag>) {
        v_varg.assign(varg.begin(), varg.end());
        v_kiet.assign(kiet.begin(), kiet.end());
    }
    else {
        v_varg.assign(varg.begin(), varg.end());
        v_kiet.assign(kiet.begin(), kiet.end());
    }

    failo_formatavimas("vargsiukai.txt", v_varg, method);
    failo_formatavimas("kietiakiai.txt", v_kiet, method);

    auto end = clock_type::now();
    if (out_write_ms) {
        *out_write_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
}

template ContainerT<VectorTag, Studentas> read_all<VectorTag>(const std::string&, long long*);
template ContainerT<ListTag, Studentas>   read_all<ListTag>(const std::string&, long long*);
template ContainerT<VectorTag, Studentas> read_all<VectorTag>(const std::string&, int, long long*);
template ContainerT<ListTag, Studentas>   read_all<ListTag>(const std::string&, int, long long*);
template void split_groups<VectorTag>(ContainerT<VectorTag, Studentas>&, ContainerT<VectorTag, Studentas>&, ContainerT<VectorTag, Studentas>&, int, long long*);
template void split_groups<ListTag>(ContainerT<ListTag, Studentas>&, ContainerT<ListTag, Studentas>&, ContainerT<ListTag, Studentas>&, int, long long*);
template void sort_groups<VectorTag>(ContainerT<VectorTag, Studentas>&, ContainerT<VectorTag, Studentas>&, int, long long*);
template void sort_groups<ListTag>(ContainerT<ListTag, Studentas>&, ContainerT<ListTag, Studentas>&, int, long long*);
template void write_groups<VectorTag>(const ContainerT<VectorTag, Studentas>&, const ContainerT<VectorTag, Studentas>&, int, long long*);
template void write_groups<ListTag>(const ContainerT<ListTag, Studentas>&, const ContainerT<ListTag, Studentas>&, int, long long*);
