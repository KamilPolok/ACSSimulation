#include "Simulation.hpp"
#include <iostream>

Record::Record(float time_, float processVariable_, float controlVariable_)
    : time(time_)
    , processVariable(processVariable_)
    , controlVariable(controlVariable_)
{
}

Records::Records(std::string name1, std::string name2, std::string name3)
{
    columnNames = {name1, name2, name3};
}

void Records::addRecord(int val1, int val2, int val3)
{
    records.emplace_back(val1, val2, val3);
}

std::array<std::string, 3> Records::getColumnNames() const
{
    return columnNames;
}

const std::vector<Record>& Records::getRecords() const
{
    return records;
}

Simulation::Simulation(ControlObjectIf* const controlObject_, ActuatorIf* const actuator_)
    : controlObject(controlObject_)
    , actuator(actuator_)
    , controller(nullptr)
    , records("Time [s]", controlObject_->getProcessVariableName(), actuator_->getControlVariableName())
{
}

void Simulation::runSimulation(size_t iterations, float timeStep)
/*Execute the simulation.*/
{   
    // Run the iterations of simulation
    for(size_t i {}; i < iterations; ++i)
    {
        records.addRecord(i * timeStep, controlObject->getProcessVariable(), actuator->getControlVariableValue());
        iteration(timeStep);
    }
}

void Simulation::iteration(float timeStep)
/*Take a single step in the simulation and update the controlObject.*/
{
    controlObject->adjustControlVariable(actuator->getControlVariableValue() * timeStep);
    controlObject->update(timeStep);
    if (controller);
        controller->control(timeStep);
}

void Simulation::setController(std::unique_ptr<ControllerIf> controller)
{    
    this->controller = std::move(controller);
    this->controller->setControlObject(controlObject);
    this->controller->setActuator(actuator);
}

ControllerIf* const Simulation::getController()
{
    return controller.get();
}

const Records& Simulation::getRecords() const
{
    return records;
}

bool Simulation::isControllerSet()
{
    return controller != nullptr;
}
