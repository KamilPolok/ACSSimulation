#include "BBController.hpp"
#include <gtest/gtest.h>

class BBControllerTest : public ::testing::Test
{
protected:
    BBController* controller;

    void SetUp() override {
        controller = new BBController;
        controller->setSetpoint(10.0);  // Example setpoint
    }
};

TEST_F(BBControllerTest, ReturnsOneWhenProcessVariableIsLessThanSetPoint)
{
    float output = controller->control(5, 1.0);  // processVariable is less than setpoint
    EXPECT_EQ(output, 1);
}

TEST_F(BBControllerTest, ReturnsZeroWhenProcessVariableIsEqualToSetPoint)
{
    float output = controller->control(10, 1.0);  // processVariable equals setpoint
    EXPECT_EQ(output, 0);
}

TEST_F(BBControllerTest, ReturnsZeroWhenProcessVariableIsGreaterThanSetPoint)
{
    float output = controller->control(15, 1.0);  // processVariable is greater than setpoint
    EXPECT_EQ(output, 0);
}
