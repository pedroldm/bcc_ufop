#include "unit_system.h"

void test_system_constructor1(){
    SystemAbstract *v = new SystemHandle;
    assert(v->getName() == "");
    assert(v->getValue() == 0.0);
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_system_constructor2(){
    SystemAbstract *v = new SystemHandle(150.0, "Sistema1");
    assert(v->getName() == "Sistema1");
    assert(v->getValue() == 150.0);
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_system_destructor(){}

void test_system_setValue(){
    SystemAbstract *v = new SystemHandle;
    v->setValue(150.0);
    assert(v->getValue() == 150.0);
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_system_setName(){
    SystemAbstract *v= new SystemHandle;
    v->setName("Sistema1");
    assert(v->getName() == "Sistema1");
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_system_getValue(){
    SystemAbstract *v = new SystemHandle(150.0, "Sistema1");
    assert(v->getValue() == 150.0);
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_system_getName(){
    SystemAbstract *v = new SystemHandle(150.0, "Sistema1");
    assert(v->getName() == "Sistema1");
    delete(v);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void run_unit_tests_system(){
    test_system_constructor1(); // OK
    test_system_constructor2(); // OK
    test_system_destructor(); // ---------- ? 
    test_system_setValue(); // OK
    test_system_setName(); // OK
    test_system_getValue(); // OK
    test_system_getName();     
}