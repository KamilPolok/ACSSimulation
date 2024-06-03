#include "Simulation.hpp"

int main()
{
    Simulation simulation;
    simulation.setController(ControllerType::BB);
    simulation.runSimulation(20, 30);
}
