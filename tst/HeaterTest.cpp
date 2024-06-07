#include "Heater.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

class HeaterTest : public ::testing::Test
{
protected:
    Heater* heater;
    float nominalPower;
    float powerLevel;

    void SetUp() override {
        nominalPower = 50.0f;
        heater = new Heater;
    }

    void TearDown() override {
        delete heater;
    }
};

TEST_F(HeaterTest, setNominalControlVariableValueThrowsOnNonPositiveInput)
{   
    nominalPower = 0.0f;
    EXPECT_THROW(heater->setNominalControlVariableValue(nominalPower), std::invalid_argument);
    nominalPower = -1.0f;
    EXPECT_THROW(heater->setNominalControlVariableValue(nominalPower), std::invalid_argument);
}

TEST_F(HeaterTest, setNominalControlVariableValueFunctionsCorrectlyOnPositiveInput)
{
    EXPECT_NO_THROW(heater->setNominalControlVariableValue(nominalPower));
}

TEST_F(HeaterTest, ConstructorInitializesControlLevelCorrectly)
{
    EXPECT_FLOAT_EQ(heater->getControlLevel(), 0.0);   // On default level is set to 0%
}

TEST_F(HeaterTest, setControlLevelFunctionsCorrectly)
{
    powerLevel = 0.5f;
    heater->setControlLevel(powerLevel);
    EXPECT_FLOAT_EQ(heater->getControlLevel(), 0.5);   // Test for level in range 0-1

    powerLevel = 1.5f;
    heater->setControlLevel(powerLevel);  // Test clamping to 1
    EXPECT_FLOAT_EQ(heater->getControlLevel(), 1.0);

    powerLevel = -0.1f;
    heater->setControlLevel(powerLevel);  // Test clamping to 0
    EXPECT_FLOAT_EQ(heater->getControlLevel(), 0.0);
}

TEST_F(HeaterTest, CalculatesControlVariableValueCorrectly)
{
    powerLevel = 0.75f;
    heater->setNominalControlVariableValue(nominalPower);
    heater->setControlLevel(powerLevel); // Set level to 75%
    float expectedPower = nominalPower * powerLevel;  // 50W * 75%  
    EXPECT_FLOAT_EQ(heater->getControlVariableValue(), expectedPower);
}
