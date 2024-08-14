#pragma once
#include "ControllerIf.hpp"

class BBController : public ControllerIf
{
public:
    void control(float) override;
};
