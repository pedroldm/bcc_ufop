#include "unit_flux.h"

double exp (SystemAbstract* a) { return 0.01 * a->getValue(); }

void test_flux_constructor1(){
    FluxAbstract *f = new FluxHandle;
    assert(f->getTarget() == NULL);
    assert(f->getSource() == NULL);
    assert(f->getLastValue() == 0.0);
    assert(f->getName() == "");
    assert(f->getFluxDirection() == true);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_constructor2(){
    SystemAbstract *s1;
    SystemAbstract *s2;
    FluxAbstract *f = new FluxHandle(s1, s2, true, 150.0, "Fluxo1", exp);
    assert(f->getSource() == s1);
    assert(f->getTarget() == s2);
    assert(f->getFluxDirection() == true);
    assert(f->getLastValue() == 150.0);
    assert(f->getName() == "Fluxo1");
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_destructor(){}

void test_flux_setSource(){
    SystemAbstract *a;
    FluxAbstract *f = new FluxHandle;
    f->setSource(a);
    assert(f->getSource() == a);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_setTarget(){
    SystemAbstract *a;
    FluxAbstract *f = new FluxHandle;
    f->setTarget(a);
    assert(f->getTarget() == a);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_setFluxDirection(){
    FluxAbstract *f = new FluxHandle;
    f->setFluxDirection(true);
    assert(f->getFluxDirection() == true);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_setLastValue(){
    FluxAbstract *f = new FluxHandle;
    f->setLastValue(123);
    assert(f->getLastValue() == 123);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_setName(){
    FluxAbstract *f = new FluxHandle;
    f->setName("Teste");
    assert(f->getName() == "Teste");
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_getSource(){
    SystemAbstract *a;
    FluxAbstract *f = new FluxHandle(a, NULL, true, 0.0, "", exp);
    assert(f->getSource() == a);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_getTarget(){
    SystemAbstract *a;
    FluxAbstract *f = new FluxHandle(NULL, a, true, 0.0, "", exp);
    assert(f->getTarget() == a);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_getFluxDirection(){
    FluxAbstract *f = new FluxHandle;
    f->setFluxDirection(true);
    assert(f->getFluxDirection() == true);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_getLastValue(){
    FluxAbstract *f = new FluxHandle;
    f->setLastValue(123);
    assert(f->getLastValue() == 123);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_removeSource(){
    SystemAbstract *a, *b;
    FluxAbstract *f = new FluxHandle(a, b, true, 150.0, "Fluxo1", exp);
    f->removeSource();
    assert(f->getSource() == NULL);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_removeTarget(){
    SystemAbstract *a, *b;
    FluxAbstract *f = new FluxHandle(a, b, true, 150.0, "Fluxo1", exp);
    f->removeTarget();
    assert(f->getTarget() == NULL);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_flux_execute(){
    SystemAbstract *a = new SystemHandle(100, "a"); 
    SystemAbstract *b = new SystemHandle(100, "b");
    FluxAbstract *f = new FluxHandle(a, b, true, 0.0, "Fluxo1", exp);
    f->execute();
    assert(f->getLastValue() == 1.0);
    delete(a);
    delete(b);
    delete(f);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void run_unit_tests_flux(){
    test_flux_constructor1();
    test_flux_constructor2();
    test_flux_destructor();
    test_flux_setSource();
    test_flux_setTarget();
    test_flux_setFluxDirection();
    test_flux_setLastValue();
    test_flux_setName();
    test_flux_getSource();
    test_flux_getTarget();
    test_flux_getFluxDirection();
    test_flux_getLastValue();
    test_flux_removeSource();
    test_flux_removeTarget();
    test_flux_execute();
}