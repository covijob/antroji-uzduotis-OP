#pragma once
#include <ostream>
#include <vector>
#include <list>
#include "studentai.hpp"

void isvesti_rezultatus(std::ostream& out,
    const std::vector<Studentas>& grupe,
    int method);

void isvesti_rezultatus(std::ostream& out,
    const std::list<Studentas>& grupe,
    int method);
