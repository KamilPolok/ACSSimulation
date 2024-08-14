#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <filesystem> // requires c++17

#include "Simulation.hpp"

void saveResults(const Records& records)
{
    std::string filename = "results";
    std::filesystem::path filepath = std::filesystem::current_path() / "build" / (filename + ".csv");

    if (!std::filesystem::exists(filepath.parent_path())) {
        if (!std::filesystem::create_directories(filepath.parent_path())) {
            std::cerr << "Failed to create directories for path: " << filepath << "\n";
            return;
        }
    }

    std::ofstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath.c_str() << " for writing." << std::endl;
        return;
    }

    // Using default "C" locale
    for (size_t i = 0; i < records.getColumnNames().size(); ++i)
    {
        file << records.getColumnNames()[i];
        if (i < records.getColumnNames().size() - 1)
            file << ",";
    }
    
    file << std::endl;

    for (const auto& record : records.getRecords()) {
        file << std::fixed << std::setprecision(2)
             << record.time << ","
             << record.processVariable << ","
             << record.controlVariable << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filepath << std::endl;
}
