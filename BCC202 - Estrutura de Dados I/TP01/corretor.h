#ifndef corretor_h
#define corretor_h

    typedef struct tentativa TADtentativa;

    void contarTentativas (int *n);
    void lerTentativas (int n, TADtentativa* vetorTentativas);
    int contabilizarAcertos (int n, TADtentativa* vetorTentativas);
    int somarTempo (int n, TADtentativa* vetorTentativas);
    void printResultado (int s, int p);
    TADtentativa* alocarTADtentativa (int n, TADtentativa* vetorTentativas);
    TADtentativa* desalocarTADtentativa (TADtentativa* vetorTentativas);

#endif