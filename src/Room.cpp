#include "Room.hpp"
#include <sstream>
#include <stdexcept>

Room::Room(float h, float w, float d)
 : incomingHeat(0)                  // W
 , wallThickness(0.4)               // m
 , wallThermalConductivity(0.3)     // W / (m*degC)
 , externalTemperature(-20.0)       // degC
 , internalTemperature(20.0)        // degC
{
  setDimensions(h, w, d);
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
  return q / (airMass * airSpecificHeat) * dt;
}

void Room::setDimensions(float h, float w, float d)
{
  if ((h <= 0) || (w <= 0) || (d <= 0))
  {
    std::ostringstream info;
    info << "Room dimensions have to be positive numbers: " 
         << "height: " << h
         << "width: " << w
         << "depth: " << d;

    throw std::invalid_argument(info.str());
  }

  height = h;
  width = w;
  depth = d;
}

void Room::setWallThickness(float thickness)
{
  if (thickness <= 0)
  {
    std::ostringstream info;
    info << "Wall thickness has to be a positive number: " << thickness;
    throw std::invalid_argument(info.str());
  }
  wallThickness = thickness;
}

void Room::setWallThermalConductivity(float thermalConductivity)
{
  if (thermalConductivity <= 0)
  {
    std::ostringstream info;
    info << "Wall thermal conductivity has to be a positive number: " << thermalConductivity;
    throw std::invalid_argument(info.str());
  }
  wallThermalConductivity = thermalConductivity;
}

void Room::setExternalTemperature(float temperature)
{
  if (temperature < -273.15)
    externalTemperature = -273.15;
  else
    externalTemperature = temperature;
}

void Room::setInitialInternalTemperature(float temperature)
{
  if (temperature < -273.15)
    internalTemperature = -273.15;
  else
    internalTemperature = temperature;
}
