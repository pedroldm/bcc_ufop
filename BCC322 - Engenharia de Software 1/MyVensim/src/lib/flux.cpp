#include "flux.h"

/* Flux::Flux() {
    target = NULL;
    source = NULL;
    lastValue = 0.0;
    name = "";
    fluxDirection = false;
}
Flux::Flux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func)(SystemAbstract* a)) : source(source), target(target), fluxDirection(fluxDirection), lastValue(lastValue), name(name), func(func) {}
Flux::Flux(const Flux& rhs){
    target = rhs.target;
    source = rhs.source;
    lastValue = rhs.lastValue;
    name = rhs.name;
}
Flux::~Flux() {}
FluxAbstract::~FluxAbstract() {} */

void FluxBody::setSource(SystemAbstract* source) { this->source = source; }
void FluxBody::setTarget(SystemAbstract* target) { this->target = target; }
void FluxBody::setFluxDirection(bool fluxDirection) { this->fluxDirection = fluxDirection; }
void FluxBody::setLastValue(double lastValue) { this->lastValue = lastValue; }
void FluxBody::setName(string name) { this->name = name; }
void FluxBody::setFunc(double (*func) (SystemAbstract* a)){ this->func = func; }

SystemAbstract* FluxBody::getSource() { return this->source; }
SystemAbstract* FluxBody::getTarget() { return this->target; }
bool FluxBody::getFluxDirection() { return this->fluxDirection; }
double FluxBody::getLastValue() { return this->lastValue; }
string FluxBody::getName() { return this->name; }

void FluxBody::removeSource() { this->source = NULL; }
void FluxBody::removeTarget() { this->target = NULL; }

void FluxBody::execute() {
    (fluxDirection) ? this->setLastValue(func(this->getSource())) : this->setLastValue(func(this->getTarget()));
}

//Flux & Flux::operator=(const Flux& a) {
//    if (&a == this)
//        return *this;
//    target = a.target;
//    source = a.source;
//    fluxDirection = a.fluxDirection;
//    lastValue = a.lastValue;
//    name = a.name;
//    return *this;
//}
//
//void Flux::fluxOut (ostream &out){
//    out << "- Source: " << source << endl
//        << "- Target: " << target << endl
//        << "Name: " << name << endl
//        << "Flux Direction: " << fluxDirection << endl
//        << "Last Value: " << lastValue;
//}
//
//ostream &operator<<(ostream &out, Flux &flux){
//    flux.fluxOut(out);
//    return out;
//}
//