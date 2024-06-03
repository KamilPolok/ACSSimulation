#pragma once
#include "ControllerIf.hpp"
#include "BBController.hpp"
#include "PIDController.hpp"
#include "Room.hpp"
#include "Heater.hpp"
#include <stdexcept>

enum class ControllerType
{
    BB,
    PID
};
class ControllerFactory
{
public:
    static ControllerIf* createController(ControllerType, Room*, Heater*);
};
