#include "Room.hpp"
#include <gtest/gtest.h>

class RoomTest : public ::testing::Test {
protected:
    Room *room;

    void SetUp() override {
        float height = 100;
        float width = 100;
        float depth = 100;

        room = new Room(height, width, depth);
    }

    void TearDown() override {
        delete room;
    }
};

// Test the constructor and initial conditions
TEST_F(RoomTest, ConstructorInitializesCorrectly) {
    EXPECT_FLOAT_EQ(room->getTemperature(), 20.0);
    EXPECT_FLOAT_EQ(room->getincomingHeat(), 0.0);
}

// Test adding heat to the room
TEST_F(RoomTest, HeatAdditionIncreasesIncomingHeat) {
    room->addHeat(500);
    EXPECT_FLOAT_EQ(room->getincomingHeat(), 500);

    room->addHeat(300);
    EXPECT_FLOAT_EQ(room->getincomingHeat(), 800);  // cumulative heat
}

// Test calculation of the temperature difference
TEST_F(RoomTest, TemperatureDifferenceIsCorrect) {
    float q = 884425000;  // This should theoretically increase temp by 1°C in one second
    float dt = 1.0;
    room->addHeat(q);  // Simulate adding the exact amount of heat that increases temperature by 1 degree

    room->update(dt);
    EXPECT_NEAR(room->getTemperature(), 21.0, 0.01);  // Assuming initial temperature was 20.0
}
