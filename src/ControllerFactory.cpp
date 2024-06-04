#include "ControllerFactory.hpp"

ControllerIf* ControllerFactory::createController(ControllerType type, const PIDConstants* constants)
{
    switch(type) {
        case ControllerType::BB:
            return new BBController;
        case ControllerType::PID:
            if (constants)
                return new PIDController(constants->kp, constants->ki, constants->kd);
            else
                return new PIDController();
        default:
            throw std::invalid_argument("Unknown controller type");
    }
}