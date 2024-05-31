#include "Simulation.hpp"
#include <iostream>

void Simulation::process(size_t iterations, float timeStep)
/*Simulate the process of time flow.*/
{
    for(size_t i {}; i < iterations; ++i)
        iteration(timeStep);
}

void Simulation::iteration(float timeStep)
/*Take a single step in the simulation and update the room.*/
{
    room.update(timeStep);
    std::cout << room.getTemperature() << std::endl;
}
