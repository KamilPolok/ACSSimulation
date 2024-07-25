#include "ControlObjectIf.hpp"

ControlObjectIf::ControlObjectIf(const std::string& processVariableName_)
  : processVariableName(processVariableName_)
{
}

void ControlObjectIf::setProcessVariable(float processVariable_)
{
  processVariable = processVariable_;
}

float ControlObjectIf::getProcessVariable() const
{
  return processVariable;
}

const std::string& ControlObjectIf::getProcessVariableName() const
{
  return processVariableName;
}
