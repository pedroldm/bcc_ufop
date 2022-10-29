#ifndef UNIT_FLUX_H
#define UNIT_FLUX_H

#include "../../src/lib/system.h"
#include "../../src/lib/flux.h"

#include <cassert>  
#include <cmath>

void test_flux_constructor1(); // OK
void test_flux_constructor2(); // OK
void test_flux_destructor(); // OK
void test_flux_setSource(); // OK
void test_flux_setTarget(); // OK
void test_flux_setFluxDirection(); // OK
void test_flux_setLastValue(); // OK
void test_flux_setName(); // OK
void test_flux_getSource(); // OK
void test_flux_getTarget(); // OK
void test_flux_getFluxDirection(); // OK
void test_flux_getLastValue(); // OK
void test_flux_removeSource(); // OK
void test_flux_removeTarget(); // OK
void test_flux_execute(); // OK

void run_unit_tests_flux();

#endif