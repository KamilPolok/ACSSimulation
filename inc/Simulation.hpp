
#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include "Room.hpp"
#include "Heater.hpp"

struct DataRecord {
    float time;
    float temperature;
    float power;

    DataRecord(float time_, float temperature_, float power_)
        : time(time_), temperature(temperature_), power(power_) {}
};

class Simulation
{
public:
    Simulation() = default;
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;

    void runSimulation(size_t, float);

    Simulation& operator=(Simulation) = delete;
private:
    std::vector<DataRecord> records;

    Room room;
    Heater heater;

    void iteration(float);

    void displayStatus(size_t);
    void saveToCSV(const std::string&);
};
