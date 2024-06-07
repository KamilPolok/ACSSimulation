#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PIDController.hpp"
#include "MockActuator.hpp"
#include "MockControlObject.hpp"

using ::testing::Return;
using ::testing::FloatNear;
using ::testing::_;

class PIDControllerTest : public ::testing::Test {
protected:
    PIDController* controller;
    MockActuator actuator;
    MockControlObject controlObject;

    void TearDown() override
    {
        delete controller;
        controller = nullptr;
    }

    // Factory method to create a controller with specific gains
    PIDController* createController(float kp, float ki, float kd) {
        PIDController* ctrl = new PIDController(kp, ki, kd);
        ctrl->setActuator(&actuator);
        ctrl->setControlObject(&controlObject);
        return ctrl;
    }
};

// Example Test Cases

TEST_F(PIDControllerTest, ProportionalTerm) {
    controller = createController(2.0f, 0.0f, 0.0f);

    float setpoint = 10.0f;
    float processVariable = 7.0f;
    float expectedOutput = 2 * (setpoint - processVariable);

    EXPECT_CALL(controlObject, getProcessVariable()).WillOnce(Return(processVariable));
    EXPECT_CALL(actuator, setControlLevel(FloatNear(expectedOutput, 0.01)));

    controller->setSetpoint(setpoint);
    controller->control(1.0); // Time step does not impact proportional control
}

TEST_F(PIDControllerTest, IntegralTermOnly) {
    controller = createController(0.0f, 0.5f, 0.0f);

    float setpoint = 10.0f;
    float processVariable = 7.0f;
    float dt = 1.0f; // time step to see integral accumulation
    float error = setpoint - processVariable;
    float expectedOutput = 0.5 * error * dt; // I = ki * integral of error over time

    EXPECT_CALL(controlObject, getProcessVariable()).WillOnce(Return(processVariable));
    EXPECT_CALL(actuator, setControlLevel(FloatNear(expectedOutput, 0.01)));

    controller->setSetpoint(setpoint);
    controller->control(dt);
}

TEST_F(PIDControllerTest, DerivativeTermOnly) {
    controller = createController(0.0f, 0.0f, 1.0f);

    float setpoint = 10.0f;
    float initialProcessVariable = 7.0f;
    float newProcessVariable = 8.0f;
    float dt = 1.0f; // Time step
    float initialError = setpoint - initialProcessVariable;
    float newError = setpoint - newProcessVariable;
    float expectedDerivative = (newError - initialError) / dt;
    float expectedOutput = 1.0 * expectedDerivative; // D = kd * derivative of error

    EXPECT_CALL(actuator, setControlLevel(_));

    EXPECT_CALL(controlObject, getProcessVariable())
        .WillOnce(Return(initialProcessVariable))
        .WillOnce(Return(newProcessVariable));

    controller->setSetpoint(setpoint);
    controller->control(dt); // First call to establish previous error

    EXPECT_CALL(actuator, setControlLevel(FloatNear(expectedOutput, 0.01)));
    controller->control(dt); // Second call to calculate derivative
}
