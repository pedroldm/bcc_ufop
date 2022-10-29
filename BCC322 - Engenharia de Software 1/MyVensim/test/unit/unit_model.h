#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

#include "../../src/lib/systemAbstract.h"
#include "../../src/lib/fluxAbstract.h"
#include "../../src/lib/modelAbstract.h"

#include <cassert>  
#include <cmath>

void test_model_constructor1();
void test_model_constructor2();
void test_model_destructor();
void test_model_execute();
void test_model_createSystem();
void test_model_createFlux();
void test_model_createModel();

void run_unit_tests_model();

#endif