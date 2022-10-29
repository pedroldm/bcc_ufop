#ifndef FLUXABSTRACT_H
#define FLUXABSTRACT_H

#include "systemAbstract.h"

#include <iostream>
#include <string>

using namespace std;

class FluxAbstract {
    public:
        virtual ~FluxAbstract() {}
        virtual void setSource(SystemAbstract* source) = 0;
        virtual void setTarget(SystemAbstract* target) = 0;
        virtual void setFunc(double (*func) (SystemAbstract* a)) = 0;
        virtual void setFluxDirection(bool fluxDirection) = 0;
        virtual void setLastValue(double lastValue) = 0;
        virtual void setName(string name) = 0;
        virtual SystemAbstract* getSource() = 0;
        virtual SystemAbstract* getTarget() = 0;
        virtual bool getFluxDirection() = 0;
        virtual double getLastValue() = 0;
        virtual string getName() = 0;
        virtual void removeSource() = 0;
        virtual void removeTarget() = 0;
        virtual void execute() = 0;
};

#endif