#include "Room.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

class RoomTest : public ::testing::Test {
protected:
    Room *room;

    void SetUp() override {
        float height = 100;
        float width = 100;
        float depth = 100;

        room = new Room(height, width, depth);
        room->setWallThickness(0.4);
        room->setWallThermalConductivity(0.3);
        room->setExternalTemperature(-20);
        room->setInitialInternalTemperature(20.0);
    }

    void TearDown() override {
        delete room;
    }
};
TEST_F(RoomTest, ThrowsOnSetDimensionsNonPositiveInput)
{
    EXPECT_THROW(room->setDimensions(-1, 10, 10), std::invalid_argument);
    EXPECT_THROW(room->setDimensions(10, -1, 10), std::invalid_argument);
    EXPECT_THROW(room->setDimensions(10, 10, -1), std::invalid_argument);
    EXPECT_THROW(room->setDimensions(0, 10, 10), std::invalid_argument);
    EXPECT_THROW(room->setDimensions(10, 0, 10), std::invalid_argument);
    EXPECT_THROW(room->setDimensions(10, 10, 0), std::invalid_argument);
}

TEST_F(RoomTest, FunctionsCorrectlyOnSetDimensionsPositiveInput)
{
    EXPECT_NO_THROW(room->setDimensions(10, 10, 10));
}

TEST_F(RoomTest, ThrowsOnSetWallThicknessNonPositiveInput)
{
    EXPECT_THROW(room->setWallThickness(-1), std::invalid_argument);
    EXPECT_THROW(room->setWallThickness(0), std::invalid_argument);
}

TEST_F(RoomTest, FunctionsCorrectlyOnSetWallThicknessPositiveInput)
{
    EXPECT_NO_THROW(room->setWallThickness(0.4));
}

TEST_F(RoomTest, ThrowsOnSetWallThermalConductivityNonPositiveInput)
{
    EXPECT_THROW(room->setWallThermalConductivity(-1), std::invalid_argument);
    EXPECT_THROW(room->setWallThermalConductivity(0), std::invalid_argument);
}

TEST_F(RoomTest, FunctionsCorrectlyOnSetWallThermalConductivityPositiveInput)
{
   EXPECT_NO_THROW(room->setWallThermalConductivity(0.4));
}

TEST_F(RoomTest, SetInitialInternalTemperatureFunctionsCorrectly)
{
    room->setInitialInternalTemperature(-300);
    EXPECT_NEAR(room->getTemperature(), -273.75, 1); // minimal temperature: -273.75
    room->setInitialInternalTemperature(50);
    EXPECT_FLOAT_EQ(room->getTemperature(), 50);
}

TEST_F(RoomTest, TemperatureUpdateWhenNoAddedHeatIsCorrect)
{
    float dt = 1104.03125;

    room->update(dt);
    EXPECT_NEAR(room->getTemperature(), 19, 0.5);
}

TEST_F(RoomTest, TemperatureUpdateWhenAddedHeatIsCorrect)
{
    float q = 2083225.0;  // This should theoretically increase temp by 1°C in one second
    float dt = 1000.0;
    room->addHeat(q);  // Simulate adding the exact amount of heat that increases temperature by 1 degree

    room->update(dt);
    EXPECT_NEAR(room->getTemperature(), 21.0, 0.01);
}
