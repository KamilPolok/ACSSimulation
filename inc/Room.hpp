#pragma once

class Room {
 public:
  Room(float height=1000, float width=1000, float depth=1000);
  
  void update(float timeStep=1.0);
  void addHeat(float heat);

  float getTemperature() const;
  float getincomingHeat() const;
 private:
  float height;
  float width;
  float depth;
  float totalWallsArrea;
  float airMass;
  float internalTemperature;
  float incomingHeat;
  const float specificHeat;
  const float airDensity;
  const float wallThickness;
  const float wallThermalConductivity;
  const float externalTemperature;

  float heatLoss() const;
  float temperatureDifference(float heat, float time=1.0) const;
};
