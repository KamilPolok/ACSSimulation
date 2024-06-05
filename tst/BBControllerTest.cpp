#include "BBController.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class MockRoom : public Room {
public:
    MOCK_METHOD(float, getTemperature, (), (const, override));
};

class MockHeater : public Heater {
public:
    MOCK_METHOD(void, setPowerLevel, (float), (override));
};

class BBControllerTest : public ::testing::Test
{
protected:
    BBController controller;
    MockRoom room;
    MockHeater heater;

    void SetUp() override {
        std::cout << &room << std::endl; 

        controller.setControlObject(&room);
        controller.setActuator(&heater);
        controller.setSetpoint(20.0);
    }
};

TEST_F(BBControllerTest, ActivatesHeaterWhenBelowSetpoint)
{
    EXPECT_CALL(room, getTemperature()).WillOnce(::testing::Return(18.0)); // Room returns temperature < setpoint
    EXPECT_CALL(heater, setPowerLevel(1));

    controller.control(1);
}

TEST_F(BBControllerTest, DeactivatesHeaterWhenAtOrAboveSetpoint)
{
    for (float temp : {20.0f, 22.0f}) {
        EXPECT_CALL(room, getTemperature()).WillOnce(::testing::Return(temp)); // Room fisrt returns temperature = setpoint and then > setpoint
        EXPECT_CALL(heater, setPowerLevel(0));

        controller.control(1);
    }
}
