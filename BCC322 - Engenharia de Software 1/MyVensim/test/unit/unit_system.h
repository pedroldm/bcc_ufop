#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include "../../src/lib/system.h"

#include <cassert>  
#include <cmath>

void test_system_constructor1(); // OK
void test_system_constructor2(); // OK
void test_system_destructor(); // ---------- ? 
void test_system_setValue(); // OK
void test_system_setName(); // OK
void test_system_getValue(); // OK
void test_system_getName(); // OK

void run_unit_tests_system();

#endif