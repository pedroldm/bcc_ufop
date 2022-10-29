#include "funcional_tests.h"

int main (int argc, char *argv[]){
    exponentialFunctionalTest();
    logisticalFunctionalTest();
    complexFunctionalTest();
    cout << "Testes funcionais -> OK!" << endl;
    return true;
}