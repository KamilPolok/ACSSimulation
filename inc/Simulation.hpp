
#pragma once
#include <cstddef>
#include <vector>
#include <string>
#include "Room.hpp"
#include "Heater.hpp"
#include "ControllerIf.hpp"
#include "ControllerFactory.hpp"
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
    Simulation();
    ~Simulation();
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;

    void setController(ControllerType type);
    void runSimulation(size_t, float);
    void saveToCSV(const std::string&) const;

    Simulation& operator=(Simulation) = delete;
private:
    std::vector<DataRecord> records;

    Room room;
    Heater heater;
    ControllerIf* controller;

    void iteration(float);

    void displayStatus(size_t) const;
};
