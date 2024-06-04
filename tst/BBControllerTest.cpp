#include "BBController.hpp"
#include <gtest/gtest.h>
#include "Room.hpp"
#include "Heater.hpp"

class BBControllerTest : public ::testing::Test
{
protected:
    BBController* controller;
    Room* room;
    Heater* heater;

    void SetUp() override {
        room = new Room;
        heater = new Heater(100); // nominal power 100 W
        controller = new BBController();
        controller->setControlObject(room);
        controller->setActuator(heater);
    }
};

TEST_F(BBControllerTest, ReturnsOneWhenProcessVariableIsLessThanSetPoint)
{
    controller->setSetpoint(30.0);  // setpoint = 30.0, processVariable = 20.0;
    controller->control(1);  // processVariable is less than setpoint -> currentPower = 100; 
    float output = heater->getCurrentPower();
    EXPECT_EQ(output, 100);
}

TEST_F(BBControllerTest, ReturnsZeroWhenProcessVariableIsEqualToSetPoint)
{
    controller->setSetpoint(20.0);  // setpoint = 10.0, processVariable = 20.0;
    controller->control(1);  // processVariable equals setpoint -> currentPower = 0
    float output = heater->getCurrentPower();
    EXPECT_EQ(output, 0);
}

TEST_F(BBControllerTest, ReturnsZeroWhenProcessVariableIsGreaterThanSetPoint)
{
    controller->setSetpoint(10.0);  // setpoint = 10.0, processVariable = 20.0;
    controller->control(1);  // processVariable is greater than setpoint -> currentPower = 0
    float output = heater->getCurrentPower();
    EXPECT_EQ(output, 0);
}
