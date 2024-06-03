#pragma once
#include "ControllerIf.hpp"

class BBController : public ControllerIf
{
public:
    BBController(float=0);
    float control(float, float);
};
