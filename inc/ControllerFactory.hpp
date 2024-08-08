#pragma once
#include "ControllerIf.hpp"
#include <memory>

#include "Room.hpp"
#include "Heater.hpp"

enum class ControllerType
{
    BB,
    PID
};

struct PIDConstants
{
    float kp;
    float ki;
    float kd;

    PIDConstants(float kp_, float ki_, float kd_)
        : kp(kp_), ki(ki_), kd(kd_){}
};

class ControllerFactory
{
public:
    static std::unique_ptr<ControllerIf> createController(ControllerType, const PIDConstants* constants=nullptr);
};
