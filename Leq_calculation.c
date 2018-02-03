#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 20; // Doit avoir la meme valeur que microValue[]
int tableauValeurVolt[300] = { };
int tableauValeurVolt_leq10[300] = { };
int nouvelEmplacement = 0;
int nbValeur = 300;
int Running_Leq = 0;
const int V_0=1 ; //La tension correspondant au niveau zero Decibel (*1000)
double leq=0; // Valeur du leq initiale
double leq10=0; // Valeur du leq10 initiale
double leqmax=0; //Valeur du leqmax initiale
double sum10=0; //
//*********************************************************************************
//*********************************************************************************
int main()
  {

   return(0);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
