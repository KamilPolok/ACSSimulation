#include "PIDController.hpp"
#include <gtest/gtest.h>

TEST(PIDControllerTest, ControlFunctionIntegration)
{
    // Test how well the control integrates the PID terms
    PIDController controller;
    controller.setSetpoint(10.0);

    float output = controller.control(9.5, 1.0); // setpoint = 10.0, processVariable = 9.5, dt = 1
    float expected = 2.0 + 0.01 - 0.05; // Up + Ui + Ud
    EXPECT_NEAR(output, expected, 0.001);
}
