#include "PIDController.hpp"
#include "Room.hpp"
#include "Heater.hpp"

#include <gtest/gtest.h>

TEST(PIDControllerTest, ControlFunctionIntegration)
{
    // Test how well the control integrates the PID terms
    Room room;
    float nominalPower = 100.0;
    Heater heater(nominalPower); // nominal power 100 W
    PIDController controller(&room, &heater);
    controller.setSetpoint(20.2);

    controller.control(1.0); // setpoint = 19.8, processVariable = 20.0, dt = 1
    float output = heater.getCurrentPower();
    float expected = (0.8 + 0.04 - 0.02) * nominalPower; // (Up + Ui + Ud) * P
    EXPECT_NEAR(output, expected, 0.5);
}
