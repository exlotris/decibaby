#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>//necessaire pour la fonction delay
#include <math.h>//necessaire pour la fonction log10

double microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 10; // Doit avoir la meme valeur que microValue[]
double tableauValeurVolt[40] = { };
double tableauValeurVolt_leq10[40] = { };
int indexTableau = 0;
int nbValeur = 40;
double Running_Leq = 0;
double V_0=0.001 ; //La tension correspondant au niveau zero Decibel (*1000)
double leq=0; // Valeur du leq initiale
double leq10=0; // Valeur du leq10 initiale
double leqmax=0; //Valeur du leqmax initiale
double sum =0;
double sum10=0; //

static int cmp (void const *a, void const *b)
{
   int ret = 0;
   double const *pa = a;
   double const *pb = b;
   double diff = *pb - *pa;
   if (diff > 0) {ret = 1;}
   else if (diff < 0) { ret = -1;}
   else { ret = 0;}
   return ret;
}

void AffichageTab (double *tableau) {
  int n = sizeof(tableau)/sizeof(double);
  for(int j = 0; j < n; j++) {
      printf(" %lf", a[j]);
  }
  printf("\n");
}

int main () {
  double x, ret;
  x = 5000;
  ret = log10(x);
  printf("log10(%lf) = %lf\n", x, ret);

  int looop=0;
  while (looop<nbValeur) {
    int array[NbSample];
    for(int i = 0; i < NbSample; i++)
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

    tableauValeurVolt[indexTableau]=sum/NbSample;


    for(int j = 0; j < nbValeur; j++) {
        printf(" %lf", tableauValeurVolt[j]);
    }
    printf("\n");

    printf("indexTableau %4d\n", indexTableau);
    printf("Nouvelle valeur %lf\n", tableauValeurVolt[indexTableau]);


    if (tableauValeurVolt[nbValeur-1] != 0)
    {
      if (indexTableau != 0)
      {
        Running_Leq -= tableauValeurVolt[indexTableau-1];
        Running_Leq += tableauValeurVolt[indexTableau];
      }
      else
      {
        Running_Leq -= tableauValeurVolt[nbValeur-1];
        Running_Leq += tableauValeurVolt[indexTableau];
      }
    }
    else
    {
      Running_Leq += tableauValeurVolt[indexTableau];
    }
    // Calule la running average du leq
    indexTableau++;
    if (indexTableau==nbValeur)
    {
      indexTableau=0;
    }
    for(int i=0; i<nbValeur;i++)
    {
      tableauValeurVolt_leq10[i]=tableauValeurVolt[i];
    }

    // Trie le tableau tels que les valeurs les + grandes soient en premiere position
    qsort(tableauValeurVolt_leq10, sizeof tableauValeurVolt_leq10 / sizeof *tableauValeurVolt_leq10, sizeof *tableauValeurVolt_leq10, cmp);
    for(int j = 0; j < nbValeur; j++) {
        printf(" %lf", tableauValeurVolt_leq10[j]);
    }
    printf("\n");
    AffichageTab(tableauValeurVolt_leq10);
    int sum10 =0;
    for (int i=0; i<(nbValeur/10); i++)
    {
      sum10+= tableauValeurVolt_leq10[i];
    }
    // Calcule le leq du tableau microValue
    leq = 20*log10(Running_Leq/(nbValeur*V_0));
    leq10 = 20*log10(sum10/((nbValeur/10)*V_0));
    leqmax = 20*log10((tableauValeurVolt_leq10[0])/(V_0));
    printf("leq %lf\n", leq);
    printf("leq10 %lf\n", leq10);
    printf("leqmax %lf\n", leqmax);
    looop++;
    delay(800);
  }
  return(0);
}
