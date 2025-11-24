#include "formatas.hpp"
#include <iomanip>

void isvesti_rezultatus(std::ostream& out,
    const std::vector<Studentas>& grupe,
    int method)
{
    out << std::left << std::setw(15) << "Pavarde"
        << std::setw(15) << "Vardas"
        << std::setw(10) << "Galutinis"
        << "\n";

    for (const auto& s : grupe) {
        out << std::left << std::setw(15) << s.pavarde()
            << std::setw(15) << s.vardas()
            << std::setw(10) << std::fixed << std::setprecision(2)
            << s.galutinis(method)
            << "\n";
    }
}

void isvesti_rezultatus(std::ostream& out,
    const std::list<Studentas>& grupe,
    int method)
{
    out << std::left << std::setw(15) << "Pavarde"
        << std::setw(15) << "Vardas"
        << std::setw(10) << "Galutinis"
        << "\n";

    for (const auto& s : grupe) {
        out << std::left << std::setw(15) << s.pavarde()
            << std::setw(15) << s.vardas()
            << std::setw(10) << std::fixed << std::setprecision(2)
            << s.galutinis(method)
            << "\n";
    }
}
