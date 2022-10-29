#include "unit_model.h"
#include "unit_flux.h"
#include "unit_system.h"

int main (int argc, char *argv[]){
    run_unit_tests_flux();
    run_unit_tests_model();
    run_unit_tests_system();
    cout << "Testes unitários -> OK!" << endl;
    return true;
}