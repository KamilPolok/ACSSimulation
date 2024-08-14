#include <Simulation.hpp>
#include <ControllerFactory.hpp>
#include <Room.hpp>
#include <Heater.hpp>

#include "saveResults.hpp"

int main()
{
    // Setup Simulation
    Room room(10, 10, 10, 20, -20, 0.4, 03);
    Heater heater(100);
    Simulation simulation(&room, &heater);

    // Create and setup Controller
    auto bbController = ControllerFactory::createController(ControllerType::BB);
    bbController->setSetpoint(100);
    simulation.setController(std::move(bbController));

    // Run simulation
    simulation.runSimulation(40, 5);
    saveResults(simulation.getRecords());
}
