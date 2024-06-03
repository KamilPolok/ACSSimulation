#pragma once
#include "ControllerIf.hpp"

class BBController : public ControllerIf
{
public:
    BBController(Room*, Heater*);
    void control(float) override;
};
