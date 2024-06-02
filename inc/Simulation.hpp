
#pragma once
#include <cstddef>
#include "Room.hpp"
#include "Heater.hpp"

class Simulation
{
public:
    Simulation() = default;
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;

    void iteration(float timeStep);
    void process(size_t iterations, float timeStep);

    Simulation& operator=(Simulation) = delete;
private:
    Room room;
    Heater heater;
};
