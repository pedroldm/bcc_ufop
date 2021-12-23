#include <stdio.h>

int main ()
{
	int Ano, A, B, C, D, E, F, G, H, I, K, L, M, Mes, Dia, Janeiro, Fevereiro, Marco, Abril, Maio, Junho, Julho, NumeroPascoa, NumeroCC, DiaCC, MesCC, NumeroSS, DiaSS, MesSS, NumeroC, DiaC, MesC, Bissexto;
	printf("Insira o Ano: ");
	scanf ("%d", &Ano);

    Janeiro = 31;
	if ( ( Ano % 4 == 0 && Ano % 100 != 0 ) || ( Ano % 400 == 0 ) ){
        	Fevereiro = 29;
        	Bissexto = 1;
	}
    else { Fevereiro = 28;
           Bissexto = 0;
    }
    
	Marco = 31;
	Abril = 30;
	Maio = 31;
	Junho = 30;
	Julho = 31;
	A = Ano % 19;
	B = Ano / 100;
	C = Ano % 100;
	D = B / 4;
	E = B % 4;
	F = (B + 8) / 25;
	G = (B - F + 1) / 3;
	H = (19 * A + B - D - G + 15) % 30;
	I = C / 4;
	K = C % 4;
	L = (32 + 2 * E + 2 * I - H - K) % 7;
	M = (A + 11 * H + 22 * L) / 451;
	Mes = (H + L - 7 * M + 114) / 31;
	Dia = (H + L - 7 * M + 114) % 31 + 1;

    if ( Mes == 3 ){
        NumeroPascoa = Janeiro + Fevereiro + Dia;
    }
    if ( Mes == 4 ){
        NumeroPascoa = Janeiro + Fevereiro + Marco + Dia;
    }

    NumeroCC = NumeroPascoa + 60;
    
    // Intervalos Ano Comum: 1 - 31 = Janeiro, 32 - 59 = Fevereiro, 60 - 90 = Março, 91 - 120 = Abril, 121 - 151 = Maio, 152 - 181 = Junho, 182 - 212 = Julho.
    // Intervalos Anos Bissextos: 1 - 31 = Janeiro, 32 - 60 = Fevereiro, 61 - 91 = Março, 92 - 121 = Abril, 122 - 152 = Maio, 153 - 182 = Junho, 183 - 213 Julho.
    // Intervalo de Páscoa = 22/03 a 25/04
    
    if ( Bissexto == 0 ){
        if ( 141 <= NumeroCC && NumeroCC <= 151 ){
            MesCC = 5;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril);
        }
        else if ( 151 < NumeroCC && NumeroCC <= 181 ){
            MesCC = 6;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril + Maio);
        }
        else if ( 181 < NumeroCC && NumeroCC <= 212 ){
            MesCC = 7;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril + Maio + Junho);
        }
    }
    else if ( Bissexto == 1 );{
         if ( 142 <= NumeroCC && NumeroCC <= 152 ){
            MesCC = 5;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril);
        }
        else if ( 152 < NumeroCC && NumeroCC <= 182 ){
            MesCC = 6;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril + Maio);
        }
        else if ( 182 < NumeroCC && NumeroCC <= 213 ){
            MesCC = 7;
            DiaCC = NumeroCC - (Janeiro + Fevereiro + Marco + Abril + Maio + Junho);
        }
    }
    NumeroSS = NumeroPascoa - 2;
    if ( Bissexto == 0 ){
        if ( 60 <= NumeroSS && NumeroSS <= 90 ){
            MesSS = 3;
            DiaSS = NumeroSS - (Janeiro + Fevereiro);
        }
        else if ( 90 < NumeroSS && NumeroSS <= 120 ){
            MesSS = 4;
            DiaSS = NumeroSS - (Janeiro + Fevereiro + Marco);
        }
    }
    else if ( Bissexto == 1 ){
        if ( 61 <= NumeroSS && NumeroSS <= 91 ){
            MesSS = 3;
            DiaSS = NumeroSS - (Janeiro + Fevereiro);
        }
        else if ( 92 < NumeroSS && NumeroSS <= 121 ){
            MesSS = 4;
            DiaSS = NumeroSS - (Janeiro + Fevereiro + Marco);
        }
    }
    NumeroC = NumeroPascoa - 47;
    if ( Bissexto == 0 ){
        if ( 32 <= NumeroC && NumeroC <= 59 ){
            MesC = 2;
            DiaC = NumeroC - Janeiro;
        }
        else if ( 59 < NumeroC && NumeroC <= 90 ){
            MesC = 3;
            DiaC = NumeroC - (Janeiro + Fevereiro);
        }
        else if ( 90 < NumeroC && NumeroC <= 120){
            MesC = 4;
            DiaC = NumeroC - (Janeiro + Fevereiro + Marco);
        }
        
    }
    else if ( Bissexto == 1 ){
        if ( 32 <= NumeroC && NumeroC <= 60 ){
            MesC = 2;
            DiaC = NumeroC - Janeiro;
        }
        else if ( 60 < NumeroC && NumeroC <= 91 ){
            MesC = 3;
            DiaC = NumeroC - (Janeiro + Fevereiro);
        }
        else if ( 91 < NumeroC && NumeroC <= 121){
            MesC = 4;
            DiaC = NumeroC - (Janeiro + Fevereiro + Marco);
        }
    }
	printf("\nCarnaval: %d/%d\nSexta-feira Santa: %d/%d\nPáscoa: %d/%d\nCorpus Christi: %d/%d", DiaC, MesC, DiaSS, MesSS, Dia, Mes, DiaCC, MesCC);
    return 0;
}