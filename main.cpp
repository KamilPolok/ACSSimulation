#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <filesystem> // requires c++17

#include "Simulation.hpp"
#include "Room.hpp"
#include "Heater.hpp"

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

int main()
{
    Room room(10, 10, 10, 20, -20, 0.4, 03);
    Heater heater(100);
    Simulation simulation(&room, &heater);
    simulation.setController(ControllerType::PID);
    simulation.getController()->setSetpoint(100);
    simulation.runSimulation(40, 5);
    saveResults(simulation.getRecords());
}
