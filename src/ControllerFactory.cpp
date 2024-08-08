#include "ControllerFactory.hpp"
#include <stdexcept>

#include "BBController.hpp"
#include "PIDController.hpp"

std::unique_ptr<ControllerIf> ControllerFactory::createController(ControllerType type, const PIDConstants* constants)
{
    switch(type) {
        case ControllerType::BB:
            return std::make_unique<BBController>();
        case ControllerType::PID:
            if (constants)
                return std::make_unique<PIDController>(constants->kp, constants->ki, constants->kd);
            else
                return std::make_unique<PIDController>();
        default:
            throw std::invalid_argument("Unknown controller type");
    }
}
