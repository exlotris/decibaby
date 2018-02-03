#include <stdio.h>
#include <math.h>

int microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 20; // Doit avoir la meme valeur que microValue[]
int tableauValeurVolt[300] = { };
int tableauValeurVolt_leq10[300] = { };
int nouvelEmplacement = 0;
int nbValeur = 300;
int Running_Leq = 0;
int V_0=1 ; //La tension correspondant au niveau zero Decibel (*1000)
double leq=0; // Valeur du leq initiale
double leq10=0; // Valeur du leq10 initiale
double leqmax=0; //Valeur du leqmax initiale
double sum10=0; //

int main () {
   double x, ret;
   x = 5000;

   /* finding value of log1010000 */
   ret = log10(x);
   printf("log10(%lf) = %lf\n", x, ret);

   return(0);
}
