#include "Heater.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

class HeaterTest : public ::testing::Test
{
protected:
    Heater* heater;

    void SetUp() override {
        float nominalPower = 50.0;

        heater = new Heater(nominalPower); // Heater with nominal power 50 W
    }

    void TearDown() override {
        delete heater;
    }
};

TEST_F(HeaterTest, setNominalPowerThrowsOnNonPositiveInput)
{
    Heater heater;
    EXPECT_THROW(heater.setNominalPower(0), std::invalid_argument);
    EXPECT_THROW(heater.setNominalPower(-1), std::invalid_argument);
}

TEST_F(HeaterTest, setNominalPowerFunctionsCorrectlyOnPositiveInput)
{
    Heater heater;
    EXPECT_NO_THROW(heater.setNominalPower(1));
}

TEST_F(HeaterTest, ConstructorInitializesPowerLevelCorrectly)
{
    EXPECT_FLOAT_EQ(heater->getPowerLevel(), 0.0); // On default power is level is set to 0%
}

TEST_F(HeaterTest, SetPowerLevelFunctionsCorrectly)
{
    heater->setPowerLevel(0.5);
    EXPECT_FLOAT_EQ(heater->getPowerLevel(), 0.5);  // 50W * 50% power level

    heater->setPowerLevel(1.5);  // Test clamping to 1
    EXPECT_FLOAT_EQ(heater->getPowerLevel(), 1.0);

    heater->setPowerLevel(-0.1);  // Test clamping to 0
    EXPECT_FLOAT_EQ(heater->getPowerLevel(), 0);
}

TEST_F(HeaterTest, CalculatesCurrentPowerCorrectly)
{
    heater->setPowerLevel(0.75);    // Set power level to 75%
    float expectedPower = 50 * 0.75;    // 50W * 75%  
    EXPECT_FLOAT_EQ(heater->getCurrentPower(), expectedPower);
}

TEST_F(HeaterTest, CalculatesEmittedHeatCorrectly)
{
    heater->setPowerLevel(0.75);  // Set power level to 75%
    float time = 2;  // 2 seconds
    float expectedHeat = 50 * 0.75 * time;  // 50W * 75% * 2s
    EXPECT_FLOAT_EQ(heater->getEmitedHeat(time), expectedHeat);
}
