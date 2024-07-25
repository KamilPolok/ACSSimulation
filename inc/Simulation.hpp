
#pragma once
#include <cstddef>
#include <vector>
#include <array>
#include <string>
#include "ControllerIf.hpp"
#include "ControlObjectIf.hpp"
#include "ActuatorIf.hpp"
#include "ControllerFactory.hpp"

struct Record
/*Store record of one iteration*/
{
    float time;
    float processVariable;
    float controlVariable;

    Record(float, float, float);
};

class Records
/*Store all records of the Simulation*/
{
public:
    Records(std::string, std::string, std::string);

    void addRecord(int, int, int);

    std::array<std::string, 3> getColumnNames() const;
    const std::vector<Record>& getRecords() const;
private:
    std::array<std::string, 3> columnNames;
    std::vector<Record> records;
};

class Simulation
{
public:
    Simulation(ControlObjectIf* const, ActuatorIf* const);
    ~Simulation();
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;

    void runSimulation(size_t, float);

    void setController(ControllerType, const PIDConstants* = nullptr);
    
    ControllerIf* const getController() ;
    const Records& getRecords() const;

    bool isControllerSet();

    Simulation& operator=(Simulation) = delete;
private:
    Records records;

    ControlObjectIf* controlObject;
    ActuatorIf* actuator;
    ControllerIf* controller;

    void iteration(float);
};
