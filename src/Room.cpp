#include "Room.hpp"

Room::Room(float height_, float width_, float depth_)
 : height(height_)                  // m
 , width(width_)                    // m
 , depth(depth_)                    // m
 , incomingHeat(0)                  // W
 , specificHeat(721)                // J/kg * degC
 , airDensity(1.225)                // kg/m3
 , wallThickness(0.4)               // m
 , wallThermalConductivity(0.3)     // W / (m*degC)
 , externalTemperature(-20.0)       // degC
 , internalTemperature(20.0)        // degC
{
  totalWallsArrea = 2 * (width + depth) * height;
  airMass = width * depth * height * airDensity;
}

void Room::update(float dt) 
{
  /*Calculates the new temperature in the room based on the incoming heat.*/
  incomingHeat -= heatLoss();
  internalTemperature += temperatureDifference(incomingHeat, dt);
  incomingHeat = 0.0;
}

void Room::addHeat(float q)
{
  /*Adds a certain amount of heat (in watts) flowing into the room.*/
  incomingHeat += q;
}

float Room::getTemperature() const
{
  return internalTemperature;
}

float Room::getincomingHeat() const
{
  return incomingHeat;
}

float Room::heatLoss() const
{
  /*Simplified model of heat flow through a wall with given parameters.*/
  float tempGradient = (internalTemperature - externalTemperature) / wallThickness;
  float heat = wallThermalConductivity * totalWallsArrea * tempGradient;
  return heat;
}

float Room::temperatureDifference(float q, float dt) const
{
  /*Calculates the change in temperature of a medium based on its parameters and the incoming heat.
    q = m*c*dt  =>  dtemp = q/(m*c)
  */
  return q / (airMass * specificHeat) * dt;
}
