#pragma once
#include <string>

class ControlObjectIf
{
public:
    ControlObjectIf(const std::string& processVariableName_="Process Variable");
    virtual ~ControlObjectIf() = default;

    virtual void update(float) = 0;
    virtual void adjustControlVariable(float) = 0;

    virtual void setProcessVariable(float);

    const std::string& getProcessVariableName() const;
    virtual float getProcessVariable() const;
protected:
    std::string processVariableName;
    float processVariable;
};
