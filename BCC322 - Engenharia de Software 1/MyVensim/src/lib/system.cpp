#include "system.h"

//System::System() {
//    name = "";
//    value = 0.0;
//}
//System::System(string name, double value){
//    this->name = name;
//    this->value = value;
//}
//System::System(const System& a){
//    name = a.name;
//    value = a.value;
//} 
//System::~System() {}
//SystemAbstract::~SystemAbstract() {}

void SystemBody::setValue(double value) { this->value = value; }
void SystemBody::setName(string name) { this->name = name; }

double SystemBody::getValue(){ return this->value; }
string SystemBody::getName(){ return this->name; }

//System & System::operator=(const System &a) {
//    if (&a == this)
//        return *this;
//    name = a.name;
//    value = a.value;
//    return *this;
//}
//
//void System::sysOut (ostream &out){
//    out << "Name: " << name << endl
//        << "Value: " << value;
//}
//
//ostream &operator<<(ostream &out, System &system){
//    system.sysOut(out);
//    return out;
//}