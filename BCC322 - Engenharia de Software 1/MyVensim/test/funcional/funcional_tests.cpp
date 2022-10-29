#include "funcional_tests.h"

double exponencial (SystemAbstract* a) { return 0.01 * a->getValue(); }
double logistica (SystemAbstract* a) { return 0.01 * a->getValue() * (1 - a->getValue()/70); }

void exponentialFunctionalTest() {
    ModelAbstract *model1 = ModelAbstract::createModel();
    SystemAbstract *pop1 = model1->createSystem("pop1", 100.0);
    SystemAbstract *pop2 = model1->createSystem("pop2", 0.0);
    FluxAbstract *fexponencial = model1->createFlux(pop1, pop2, true, 0.0, "exponencial", exponencial);

    model1->execute(0.0, 100, 1);

    assert(fabs(pop1->getValue() - 36.6032) < 0.0001);
    assert(fabs(pop2->getValue() - 63.3968) < 0.0001);

    delete(model1);
}

void logisticalFunctionalTest() {
    ModelAbstract *model2 = ModelAbstract::createModel();
    SystemAbstract *p1 = model2->createSystem("p1", 100.0);
    SystemAbstract *p2 = model2->createSystem("p2", 10.0);
    FluxAbstract *flogistica = model2->createFlux(p1, p2, false, 0.0, "Fluxo 2", logistica);

    model2->execute(0.0, 100, 1);

    assert(fabs(p1->getValue() - 88.2167) < 0.0001);
    assert(fabs(p2->getValue() - 21.7833) < 0.0001);

    delete(model2);
}

void complexFunctionalTest() {
    ModelAbstract *model3 = ModelAbstract::createModel();

    SystemAbstract *Q1 = model3->createSystem("Q1", 100.0);
    SystemAbstract *Q2 = model3->createSystem("Q2", 0);
    SystemAbstract *Q3 = model3->createSystem("Q3", 100);
    SystemAbstract *Q4 = model3->createSystem("Q4", 0);
    SystemAbstract *Q5 = model3->createSystem("Q5", 0);
    FluxAbstract *v = model3->createFlux(Q4, Q1, true, 0.0, "v", exponencial);
    FluxAbstract *u = model3->createFlux(Q3, Q4, true, 0.0, "u", exponencial);
    FluxAbstract *g = model3->createFlux(Q1, Q3, true, 0.0, "g", exponencial);
    FluxAbstract *f = model3->createFlux(Q1, Q2, true, 0.0, "f", exponencial);
    FluxAbstract *r = model3->createFlux(Q2, Q5, true, 0.0, "r", exponencial);
    FluxAbstract *t = model3->createFlux(Q2, Q3, true, 0.0, "t", exponencial);

    model3->execute(0.0, 100, 1);

    assert(fabs(Q1->getValue() - 31.8513) < 0.0001);
    assert(fabs(Q2->getValue() - 18.4003) < 0.0001);
    assert(fabs(Q3->getValue() - 77.1143) < 0.0001);
    assert(fabs(Q4->getValue() - 56.1728) < 0.0001);
    assert(fabs(Q5->getValue() - 16.4612) < 0.0001);

    delete(model3);
}

