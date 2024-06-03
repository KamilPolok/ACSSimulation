#include "ControllerFactory.hpp"

ControllerIf* ControllerFactory::createController(ControllerType type, Room* room, Heater* heater)
{
    switch(type) {
        case ControllerType::BB:
            return new BBController(room, heater);
        case ControllerType::PID:
            return new PIDController(room, heater);
        default:
            throw std::invalid_argument("Unknown controller type");
    }
}