#ifndef SYSTEMABSTRACT_H
#define SYSTEMABSTRACT_H

#include <iostream>
#include <string>

using namespace std;

//Faltando destrutor virtual = default
//Corrigir instanciação dos objetos nos testes

class SystemAbstract {
    public:
        virtual ~SystemAbstract() {}
        virtual void setValue(double value) = 0;
        virtual void setName(string name) = 0;
        virtual double getValue() = 0;
        virtual string getName() = 0;
};

#endif