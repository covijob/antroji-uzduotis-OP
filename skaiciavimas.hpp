#pragma once

#include "studentai.hpp"
#include <vector>

double vidurkis(const std::vector<int>& pazymiai);
double mediana(std::vector<int> pazymiai);

double galutinis_vidurkis(const Studentas& s);
double galutinis_mediana(const Studentas& s);

void apskaiciuoti_galutini(Studentas& s, int method);

