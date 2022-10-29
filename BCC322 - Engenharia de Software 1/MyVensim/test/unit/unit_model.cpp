#include "unit_model.h"

double exponencial (SystemAbstract* a) { return 0.01 * a->getValue(); }
double logistica (SystemAbstract* a) { return 0.01 * a->getValue() * (1 - a->getValue()/70); }

void test_model_constructor(){
    ModelAbstract *m = ModelAbstract::createModel();
    vector<FluxAbstract*> fluxes;
    vector<SystemAbstract*> systems;
    systems.push_back(m->createSystem("s", 100.0));
    systems.push_back(m->createSystem("t", 0.0));
    fluxes.push_back(m->createFlux(systems[0], systems[1], true, 0.0, "f", exponencial));
    int j = 0;
    for (auto i = m->getFluxesBegin() ; i < m->getFluxesEnd() ; i++){
        assert(*i==fluxes[j++]);
    }
    j = 0;
    for (auto i = m->getSystemsBegin() ; i < m->getSystemsEnd() ; i++){
        assert(*i==systems[j++]);
    }
    delete(m);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_model_destructor(){}

void test_model_execute(){
    ModelAbstract *m = ModelAbstract::createModel();
    m->execute(0.0, 100, 1);
    assert(m->getTime() == 100);
    delete(m);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_model_createSystem(){
    ModelAbstract *m = ModelAbstract::createModel();
    SystemAbstract *s = m->createSystem("pop1", 100.0);

    for(auto i = m->getSystemsBegin() ; i < m->getSystemsEnd(); i++) assert(*i==s);
    assert(s->getName() == "pop1");
    assert(s->getValue() == 100.0);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_model_createFlux(){
    ModelAbstract *m = ModelAbstract::createModel();
    SystemAbstract *s1 = m->createSystem("s", 0.0);
    SystemAbstract *s2 = m->createSystem("t", 10.0);
    FluxAbstract *f = m->createFlux(s1, s2, true, 0.0, "f", exponencial);

    for (auto i = m->getFluxesBegin() ; i < m->getFluxesEnd() ; i++) assert(*i==f);
    assert(f->getSource() == s1);
    assert(f->getTarget() == s2);
    assert(f->getName() == "f");
    assert(f->getLastValue() == 0.0);
    assert(f->getFluxDirection() == true);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void test_model_createModel(){
    ModelAbstract *model1 = ModelAbstract::createModel();
    bool contains = false;
    for (auto i = model1->getModelsBegin() ; i < model1->getModelsEnd() ; i++) if (*i == model1) contains = true;
    assert(contains);
    cout << __PRETTY_FUNCTION__ << "-> OK!" << endl;
}

void run_unit_tests_model(){
    test_model_constructor();
    test_model_destructor();
    test_model_execute();
    test_model_createSystem();
    test_model_createFlux();
    test_model_createModel(); 
}