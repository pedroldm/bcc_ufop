#include "model.h"
#include "flux.h"
#include "system.h"

vector<ModelAbstract*> ModelBody::models;

/* Model::Model() {
    time = 0.0;
}
Model::Model(double _time, vector<FluxAbstract*> f, vector<SystemAbstract*> s){
    time = _time;
    fluxes = f;
    systems = s;
}
Model::Model(const Model& a){
    fluxes = a.fluxes;
    systems = a.systems;
}
Model::~Model() {
    for (auto f : fluxes) delete(f);
    for (auto s : systems) delete(s);

    auto i = getModelsBegin();
    for (ModelAbstract *m : models) {
        if (this == m){
            models.erase(i);
        }
        i++;
    }
}
ModelAbstract::~ModelAbstract() {} */

void ModelBody::add(FluxAbstract* FluxAbstract){
    this->fluxes.push_back(FluxAbstract); 
}

void ModelBody::add(SystemAbstract* SystemAbstract) {
    this->systems.push_back(SystemAbstract); 
}

vector<FluxAbstract*>::iterator ModelBody::getFluxesBegin(){
    return fluxes.begin();
}

vector<FluxAbstract*>::iterator ModelBody::getFluxesEnd(){
    return fluxes.end();
}

vector<SystemAbstract*>::iterator ModelBody::getSystemsBegin(){
    return systems.begin();
}

vector<SystemAbstract*>::iterator ModelBody::getSystemsEnd(){
    return systems.end();
}

vector<ModelAbstract*>::iterator ModelBody::getModelsBegin(){
    return models.begin();
}

vector<ModelAbstract*>::iterator ModelBody::getModelsEnd(){
    return models.end();
}

void ModelBody::remove(FluxAbstract* flux) { 
    for (auto i = getFluxesBegin() ; i < getFluxesEnd() ; i++)
        if (*i == flux) fluxes.erase(i);
}

void ModelBody::remove(SystemAbstract* sys) {
    for (auto i = getSystemsBegin() ; i < getSystemsEnd() ; i++)
        if (*i == sys) systems.erase(i);
}

void ModelBody::remove(ModelAbstract* model) {
    for (auto i = models.begin() ; i < models.end() ; i++)
        if (*i == model) models.erase(i);
}

SystemAbstract* ModelBody::createSystem(string name, double value) {
    SystemAbstract *s = new SystemHandle(value, name);
    add(s);
    return s;
}
FluxAbstract* ModelBody::createFlux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func) (SystemAbstract* a)) {
    FluxAbstract *f = new FluxHandle(source, target, fluxDirection, lastValue, name, func);
    add(f);
    return f;
}

ModelAbstract* ModelAbstract::createModel() {
    return ModelBody::createModel();
}

ModelAbstract* ModelBody::createModel() {
    ModelAbstract *m = new ModelHandle;
    ModelBody::models.push_back(m);
    return m;
}

void ModelBody::setTime(double _time){
    this->time = _time;
}

double ModelBody::getTime(){
    return this->time;
}

void ModelBody::execute(double start, double end, double increase){
    for (double i = start ; i < end ; i += increase){
        for(auto f : fluxes){
            f->execute();
        }
        for(auto f : fluxes){
            f->getSource()->setValue(f->getSource()->getValue() - f->getLastValue());
            f->getTarget()->setValue(f->getTarget()->getValue() + f->getLastValue());
        }
        time += increase;
    }
}

//Model & ModelBody::operator=(const Model &a) {
//    if (&a == this)
//        return *this;
//    fluxes = a.fluxes;
//    systems = a.systems;
//    return *this;
//}