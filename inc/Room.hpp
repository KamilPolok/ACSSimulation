#pragma once

class Room {
 public:
  Room(float height=10, float width=10, float depth=10);
  
  void update(float timeStep);
  void addHeat(float heat);

  float getTemperature() const;

  void setDimensions(float, float, float);
  void setWallThickness(float);
  void setWallThermalConductivity(float= 0.3);
  void setExternalTemperature(float);
  void setInitialInternalTemperature(float);

 private:
  float height;
  float width;
  float depth;
  float totalWallsArrea;
  float airMass;
  float internalTemperature;
  float incomingHeat;

  static constexpr float airSpecificHeat = 721; // J/kg * degC
  static constexpr float airDensity = 1.225;    // kg/m3

  float wallThickness;
  float wallThermalConductivity;
  float externalTemperature;

  float heatLoss() const;
  float temperatureDifference(float heat, float time=1.0) const;
};
