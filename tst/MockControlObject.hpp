#pragma once
#include "ControlObjectIf.hpp"
#include <gmock/gmock.h>

class MockControlObject : public ControlObjectIf {
public:
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(void, adjustControlVariable, (float), (override));
    MOCK_METHOD(float, getProcessVariable, (), (const, override));
};
