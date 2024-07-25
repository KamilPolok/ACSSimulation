#include "Room.hpp"
#include <sstream>
#include <stdexcept>

Room::Room(float height_, float width_, float depth_,
           float initialInternalTemperature_,
           float externalTemperature_,
           float wallThickness_,
           float wallThermalConductivity_)
  : ControlObjectIf("Temperature [degC]")
  , incomingHeat(0.0f)                
{
  setDimensions(height_, width_, depth_);
  totalWallsArrea = 2 * (width + depth) * height;
  airMass = width * depth * height * airDensity;

  setInternalTemperature(initialInternalTemperature_);
  setExternalTemperature(externalTemperature_);
  setWallThickness(wallThickness_);
  setWallThermalConductivity(wallThermalConductivity_);
}

void Room::update(float dt_)
/*
  Calculates the new temperature in the room based on the incoming heat.
  Args:
    dt_ - time step - time difference between previous and current update
*/
{
  incomingHeat -= calculateHeatLoss();
  processVariable += calculateTemperatureDifference(incomingHeat, dt_);
  incomingHeat = 0.0;
}

void Room::adjustControlVariable(float q)
/*Adds a certain amount of heat (in watts) flowing into the room.*/
{
  incomingHeat += q;
}

float Room::calculateHeatLoss() const
/*Simplified model of heat flow through a wall with given parameters.*/
{
  float tempGradient = (processVariable - externalTemperature) / wallThickness;
  float heat = wallThermalConductivity * totalWallsArrea * tempGradient;
  return heat;
}

float Room::calculateTemperatureDifference(float q, float dt) const
/*Calculates the change in temperature of a medium based on its parameters and the incoming heat.
  q = m*c*dt  =>  dtemp = q/(m*c)
*/
{
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

void Room::setInternalTemperature(float temperature_)
{
  if (temperature_ < -273.15)
    setProcessVariable(-273.15f);
  else
    setProcessVariable(temperature_);
}

void Room::setExternalTemperature(float temperature_)
{
  if (temperature_ < -273.15)
    externalTemperature = -273.15f;
  else
    externalTemperature = temperature_;
}
