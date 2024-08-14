#include "Room.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>

class RoomTest : public ::testing::Test {
protected:
    std::unique_ptr<Room> room;

    void SetUp() override {
        float height{100.0f};
        float width {100.0f};
        float depth {100.0f};
        float initialInternalTemperature {20.0f};
        float externalTemperature {-20.0f};
        float wallThickness {0.4f};
        float wallThermalConductivity {0.3f};

        room = std::make_unique<Room>(height, width, depth, initialInternalTemperature, externalTemperature, wallThickness, wallThermalConductivity);
    }
};

TEST(RoomSetDimensionsTest, ThrowsOnSetDimensionsNonPositiveInput)
{
    EXPECT_THROW(Room(-1, 10, 10, 20), std::invalid_argument);
    EXPECT_THROW(Room(-1, -1, 10, 20), std::invalid_argument);
    EXPECT_THROW(Room(10, 10, -1, 20), std::invalid_argument);
    EXPECT_THROW(Room(0, 10, 10, 20), std::invalid_argument);
    EXPECT_THROW(Room(10, 0, 10, 20), std::invalid_argument);
    EXPECT_THROW(Room(10, 10, 0, 20), std::invalid_argument);
    
}

TEST(RoomSetDimensionsTest, FunctionsCorrectlyOnSetDimensionsPositiveInput)
{
    EXPECT_NO_THROW(Room(10, 10, 10, 20));
}

TEST(RoomSetWallThicknessTest, ThrowsOnSetWallThicknessNonPositiveInput)
{
    EXPECT_THROW(Room(10, 10, 10, 20, -20, -1), std::invalid_argument);
    EXPECT_THROW(Room(10, 10, 10, 20, -20, 0), std::invalid_argument);
}

TEST(RoomSetWallThicknessTest, FunctionsCorrectlyOnSetWallThicknessPositiveInput)
{
    EXPECT_NO_THROW(Room(10, 10, 10, 20, -20, 0.4));
}

TEST(RoomSetWallThermalConductivityTest, ThrowsOnSetWallThermalConductivityNonPositiveInput)
{
    EXPECT_THROW(Room(10, 10, 10, 20, -20, 0.4, -1), std::invalid_argument);
    EXPECT_THROW(Room(10, 10, 10, 20, -20, 0.4, 0), std::invalid_argument);
}

TEST(RoomSetWallThermalConductivityTest, FunctionsCorrectlyOnSetWallThermalConductivityPositiveInput)
{
   EXPECT_NO_THROW(Room(10, 10, 10, 20, -20, 0.4, 0.3));
}

TEST(RoomSetTemperatureTest, SetTemperatureFunctionsCorrectly)
{
    Room room1(10, 10, 10, -300);
    EXPECT_NEAR(room1.getProcessVariable(), -273.75, 1); // minimal temperature: -273.75
    Room room2(10, 10, 10, 50);
    EXPECT_FLOAT_EQ(room2.getProcessVariable(), 50);
}

TEST_F(RoomTest, TemperatureUpdateWhenNoAddedHeatIsCorrect)
{
    float dt = 1104.03125f;

    room->update(dt);
    EXPECT_NEAR(room->getProcessVariable(), 19, 0.5);
}

TEST_F(RoomTest, TemperatureUpdateWhenAddedHeatIsCorrect)
{
    float q = 2083225.0f;  // This should theoretically increase temp by 1°C in one second
    float dt = 1000.0;
    room->adjustControlVariable(q);  // Simulate adding the exact amount of heat that increases temperature by 1 degree

    room->update(dt);
    EXPECT_NEAR(room->getProcessVariable(), 21.0, 0.01);
}
