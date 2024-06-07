#include "ControlObjectIf.hpp"

void ControlObjectIf::setProcessVariable(float processVariable_)
{
  processVariable = processVariable_;
}

float ControlObjectIf::getProcessVariable() const
{
  return processVariable;
}
