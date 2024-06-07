#pragma once
#include "ActuatorIf.hpp"
#include <gmock/gmock.h>

class MockActuator : public ActuatorIf {
public:
    MOCK_METHOD(void, setNominalControlVariableValue, (float), (override));
    MOCK_METHOD(void, setControlLevel, (float), (override));
    MOCK_METHOD(float, getControlVariableValue, (), (const, override));
    MOCK_METHOD(float, getControlLevel, (), (const, override));
};
