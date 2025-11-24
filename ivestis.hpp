#pragma once
#include <vector>
#include <list>
#include <string>
#include "studentai.hpp"

bool skaityti_is_failo(const std::string& failas, std::vector<Studentas>& grupe);
bool skaityti_is_failo(const std::string& failas, std::list<Studentas>& grupe);

Studentas nuskaityti_studenta(const std::string& eilute);
