#pragma once

#include "studentai.hpp"
#include <string>
#include <vector>
#include <list>

bool try_parse_int(const std::string& tok, int& out);

void ivedimas_is_konsoles(std::vector<Studentas>& grupe);

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe);

bool skaityti_is_failo(const std::string& path, std::vector<Studentas>& grupe, int method);
bool skaityti_is_failo(const std::string& path, std::list<Studentas>& grupe, int method);
