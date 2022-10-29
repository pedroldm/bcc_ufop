#ifndef FUNCIONAL_TESTS_H
#define FUNCIONAL_TESTS_H

#include "../../src/lib/modelAbstract.h"
#include "../../src/lib/fluxAbstract.h"
#include "../../src/lib/systemAbstract.h"

#include <cassert>  
#include <cmath>

void exponentialFunctionalTest();
void logisticalFunctionalTest();
void complexFunctionalTest();

double exponencial (SystemAbstract* a);
double logistica (SystemAbstract* a);

#endif