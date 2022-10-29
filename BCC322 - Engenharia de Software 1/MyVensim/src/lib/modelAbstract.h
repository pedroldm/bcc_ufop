#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include "systemAbstract.h"
#include "fluxAbstract.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ModelAbstract {
    protected:
        //virtual void add(SystemAbstract* system) = 0;
        //virtual void add(FluxAbstract* flux) = 0;
        //static void add(ModelAbstract* model);
        virtual void remove(SystemAbstract* sys) = 0;
        virtual void remove(FluxAbstract* flux) = 0;
        virtual void remove (ModelAbstract* model) = 0;
    public:
        virtual ~ModelAbstract() {}
        virtual SystemAbstract* createSystem(string name, double value) = 0;
        virtual FluxAbstract* createFlux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func) (SystemAbstract* a)) = 0;
        static ModelAbstract* createModel();
        virtual void execute(double start, double end, double increase) = 0;
        virtual void setTime(double time) = 0;
        virtual double getTime() = 0;
        virtual vector<FluxAbstract*>::iterator getFluxesBegin() = 0;
        virtual vector<FluxAbstract*>::iterator getFluxesEnd() = 0;
        virtual vector<SystemAbstract*>::iterator getSystemsBegin()= 0;
        virtual vector<SystemAbstract*>::iterator getSystemsEnd()= 0;
        virtual vector<ModelAbstract*>::iterator getModelsBegin()= 0;
        virtual vector<ModelAbstract*>::iterator getModelsEnd()= 0;
};

#endif