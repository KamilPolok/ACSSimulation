#include "Simulation.hpp"
#include <string>
#include <iostream>
#include <filesystem> // requires c++17

void saveResults(const Simulation& simulation)
{
    std::string filename = "results";
    std::filesystem::path filepath = std::filesystem::current_path() / "build" / (filename + ".csv");

    if (!std::filesystem::exists(filepath.parent_path())) {
        if (!std::filesystem::create_directories(filepath.parent_path())) {
            std::cerr << "Failed to create directories for path: " << filepath << "\n";
            return;
        }
    }

    simulation.saveToCSV(filepath.c_str());
}

int main()
{
    Room room(10, 10, 10, 20, -20, 0.4, 03);
    Heater heater(100);
    Simulation simulation(&room, &heater);
    simulation.setController(ControllerType::PID);
    simulation.getController()->setSetpoint(100);
    simulation.runSimulation(40, 5);
    saveResults(simulation);
}
