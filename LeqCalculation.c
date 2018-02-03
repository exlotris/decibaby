#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <math.h>

double microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 2; // Doit avoir la meme valeur que microValue[]
double tableauValeurVolt[5] = { };
double tableauValeurVolt_leq10[5] = { };
int nouvelEmplacement = 0;
int nbValeur = 5;
double Running_Leq = 0;
double V_0=0.001 ; //La tension correspondant au niveau zero Decibel (*1000)
double leq=0; // Valeur du leq initiale
double leq10=0; // Valeur du leq10 initiale
double leqmax=0; //Valeur du leqmax initiale
double sum =0;
double sum10=0; //

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main () {
  double x, ret;
  x = 5000;
  ret = log10(x);
  printf("log10(%lf) = %lf\n", x, ret);

  int looop=0;
  while (looop<20) {
    int array[2];
    for(int i = 0; i < 2; i++)
    {
      array[i] = (rand() % 500)+1;
      printf("%4d\n", array[i]);
    }

    sum = 0;
    for (int i=0; i<NbSample; i++)
    {
      sum+= array[i]/100;
    }
    printf("sum %lf\n", sum);

    tableauValeurVolt[nouvelEmplacement]=sum/NbSample;
    printf("Nouvelle valeur %lf\n", tableauValeurVolt[nouvelEmplacement]);


    if (tableauValeurVolt[nbValeur-1] != 0)
    {
      if (nouvelEmplacement != 0)
      {
        Running_Leq -= tableauValeurVolt[nouvelEmplacement-1];
        Running_Leq += tableauValeurVolt[nouvelEmplacement];
      }
      else
      {
        Running_Leq -= tableauValeurVolt[nbValeur-1];
        Running_Leq += tableauValeurVolt[nouvelEmplacement];
      }
    }
    else
    {
      Running_Leq += tableauValeurVolt[nouvelEmplacement];
    }
    // Calule la running average du leq
    nouvelEmplacement += 1;
    if (nouvelEmplacement==nbValeur)
    {
      nouvelEmplacement=0;
    }
    for(int i=0; i<nbValeur;i++)
    {
      tableauValeurVolt_leq10[i]=tableauValeurVolt[i];
    }

    // Trie le tableau tels que les valeurs les + grandes soient en premiere position
    for(int j = 0; j < nbValeur; j++) {
        printf("%d ", tableauValeurVolt_leq10[j]);
    }
    qsort(tableauValeurVolt_leq10, nbValeur, sizeof(int), cmpfunc);
    int sum10 =0;
    for (int i=0; i<(nbValeur/10); i++)
    {
      sum10+= tableauValeurVolt_leq10[i];
    }
    // Calcule le leq du tableau microValue
    leq = 20*log10(Running_Leq/(nbValeur*V_0));
    leq10 = 20*log10(sum10/((nbValeur/10)*V_0));
    leqmax = 20*log10((tableauValeurVolt_leq10[0])/(V_0));
    printf("leq %4d\n", leq);
    printf("leq10 %4d\n", leq10);
    printf("leqmax %4d\n", leqmax);
    looop++;
    delay(800);
  }
  return(0);
}
