#pragma once
#include "ControlObjectIf.hpp"

class Room : public ControlObjectIf
{
public:
  Room(float, float, float, float, float=-20.0f, float=0.4f, float=0.3f);
  
  void update(float) override;
  void adjustControlVariable(float) override;

private:
  float height;                                     // [m]
  float width;                                      // [m]
  float depth;                                      // [m]
  float externalTemperature;                        // [degC]
  float wallThickness;                              // [m]
  float wallThermalConductivity;                    // [W / (m*degC)]
  float incomingHeat;                               // [J]

  static constexpr float airSpecificHeat = 721.0f;  // [J/kg * degC]
  static constexpr float airDensity = 1.225f;       // [kg/m3]

  float totalWallsArrea;     
  float airMass;

  float calculateHeatLoss() const;
  float calculateTemperatureDifference(float, float=1.0f) const;

  void setDimensions(float, float, float);
  void setWallThickness(float);
  void setWallThermalConductivity(float);
  void setInternalTemperature(float);
  void setExternalTemperature(float);
};
