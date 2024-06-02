#include "Simulation.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem> // requires c++17
#include <sstream>
#include <locale>

void Simulation::runSimulation(size_t iterations, float timeStep)
/*Execute the simulation.*/
{   
    // Run the iterations of simulation
    for(size_t i {}; i < iterations; ++i)
    {
        iteration(timeStep);
        records.emplace_back(i * timeStep, room.getTemperature(), heater.getCurrentPower());
        displayStatus(i);
    }

    // saveResults
    saveToCSV("results");
}

void Simulation::iteration(float timeStep)
/*Take a single step in the simulation and update the room.*/
{
    room.addHeat(heater.getEmitedHeat(timeStep));
    room.update(timeStep);
}

void Simulation::displayStatus(size_t iterationNum)
/*Display the status after given iteration*/
{
    std::ostringstream timeStream, tempStream, powerStream;

    timeStream << std::fixed << std::setprecision(2) << "Time: " << records[iterationNum].time << " s";
    tempStream << std::fixed << std::setprecision(2) << "Temperature: " << records[iterationNum].temperature << " deg C";
    powerStream << std::fixed << std::setprecision(2) << "Heater power: " << records[iterationNum].power << " W";

    std::cout << std::left
                << std::setw(25) << timeStream.str()
                << std::setw(30) << tempStream.str()
                << std::setw(30) << powerStream.str()
                << std::endl;
}

void Simulation::saveToCSV(const std::string& filename)
/*Save data into csv file*/
{
    // using filesystem library - c++17
    std::filesystem::path filepath = std::filesystem::current_path() / "build" / (filename + ".csv");
    std::ofstream file(filepath);

    if (!std::filesystem::exists(filepath.parent_path())) {
        if (!std::filesystem::create_directories(filepath.parent_path())) {
            std::cerr << "Failed to create directories for path: " << filepath << "\n";
            return;
        }
    }

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << " for writing." << std::endl;
        return;
    }

    // Using default "C" loacle
    file << "Time [s],Temperature [°C],Heater power [W]\n";

    for (const auto& record : records) {
        file << std::fixed << std::setprecision(2)
             << record.time << ","
             << record.temperature << ","
             << record.power << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filepath << std::endl;
}
