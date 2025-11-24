#pragma once
#include <vector>
#include <list>

struct VectorTag {};
struct ListTag {};

template<typename Tag, typename T>
struct ContainerSelector;

template<typename T>
struct ContainerSelector<VectorTag, T> {
    using type = std::vector<T>;
};

template<typename T>
struct ContainerSelector<ListTag, T> {
    using type = std::list<T>;
};

template<typename Tag, typename T>
using ContainerT = typename ContainerSelector<Tag, T>::type;
