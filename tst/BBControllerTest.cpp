#include "BBController.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MockControlObject.hpp"
#include "MockActuator.hpp"

using ::testing::Return;
class BBControllerTest : public ::testing::Test
{
protected:
    BBController controller;
    MockControlObject controlObject;
    MockActuator actuator;

    void SetUp() override {
        controller.setControlObject(&controlObject);
        controller.setActuator(&actuator);
        controller.setSetpoint(20.0f);
    }
};

TEST_F(BBControllerTest, ActivatesHeaterWhenBelowSetpoint)
{
    EXPECT_CALL(controlObject, getProcessVariable()).WillOnce(Return(18.0f)); // controlObject returns temperature < setpoint
    EXPECT_CALL(actuator, setControlLevel(1.0f));

    controller.control(1.0f);
}

TEST_F(BBControllerTest, DeactivatesHeaterWhenAtOrAboveSetpoint)
{
    for (float temp : {20.0f, 22.0f}) {
        EXPECT_CALL(controlObject, getProcessVariable()).WillOnce(Return(temp)); // controlObject first returns temperature = setpoint and then > setpoint
        EXPECT_CALL(actuator, setControlLevel(0.0f));

        controller.control(1.0f);
    }
}
