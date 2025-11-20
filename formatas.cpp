#include "formatas.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

void failo_formatavimas(const std::string& failo_vardas,
    const std::vector<Studentas>& grupe,
    int vartotojo_pasirinkimas)
{
    std::ofstream out(failo_vardas);
    if (!out) {
        std::cerr << "Nepavyko atidaryti failo rasymui: " << failo_vardas << "\n";
        return;
    }

    out << std::left << std::setw(20) << "Pavarde"
        << std::left << std::setw(20) << "Vardas";

    if (vartotojo_pasirinkimas == 1) {
        out << std::left << std::setw(20) << "Galutinis (Vid.)";
    }
    else if (vartotojo_pasirinkimas == 2) {
        out << std::left << std::setw(20) << "Galutinis (Med.)";
    }
    else {
        out << std::left << std::setw(20) << "Galutinis";
    }

    out << '\n';

    out << std::string(60, '-') << '\n';

    out << std::fixed << std::setprecision(2);

    for (const auto& s : grupe) {
        out << std::left << std::setw(20) << s.pavarde
            << std::left << std::setw(20) << s.vardas
            << std::setw(20) << s.galutinis
            << '\n';
    }

    std::cout << "Rezultatai issaugoti faile: " << failo_vardas << "\n";
}
