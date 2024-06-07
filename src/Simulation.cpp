#include "Simulation.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <locale>

Simulation::Simulation(ControlObjectIf* const controlObject_, ActuatorIf* const actuator_)
    : controlObject(controlObject_)
    , actuator(actuator_)
    , controller(nullptr)
{
}

Simulation::~Simulation()
{
    delete controller;
}

void Simulation::runSimulation(size_t iterations, float timeStep)
/*Execute the simulation.*/
{   
    // Run the iterations of simulation
    for(size_t i {}; i < iterations; ++i)
    {
        records.emplace_back(i * timeStep, controlObject->getProcessVariable(), actuator->getControlVariableValue());
        displayStatus(i);
        iteration(timeStep);
    }
}

void Simulation::setController(ControllerType type, const PIDConstants* constants)
{
    delete controller;
    controller = ControllerFactory::createController(type, constants);
    controller->setControlObject(controlObject);
    controller->setActuator(actuator);
}

void Simulation::iteration(float timeStep)
/*Take a single step in the simulation and update the controlObject.*/
{
    controlObject->adjustControlVariable(actuator->getControlVariableValue() * timeStep);
    controlObject->update(timeStep);
    if (controller);
        controller->control(timeStep);
}

void Simulation::displayStatus(size_t iterationNum) const
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

void Simulation::saveToCSV(const std::string& filepath) const
/*Save data into csv file*/
{
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << " for writing." << std::endl;
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


ControllerIf* const Simulation::getController()
{
    return controller;
}

bool Simulation::isControllerSet()
{
    return controller;
}