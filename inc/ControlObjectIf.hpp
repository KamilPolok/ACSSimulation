#pragma once

class ControlObjectIf
{
public:
    ControlObjectIf() = default;

    virtual void update(float) = 0;
    virtual void adjustControlVariable(float) = 0;
    virtual void setProcessVariable(float);
    virtual float getProcessVariable() const;
protected:
    float processVariable;
};
