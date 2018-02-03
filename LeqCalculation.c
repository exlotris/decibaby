#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>//necessaire pour la fonction delay
#include <math.h>//necessaire pour la fonction log10
#include "data.csv"

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

void AffichageTab (double tableau[], int length) {
  for(int j = 0; j < length; j++) {
      printf(" %lf", tableau[j]);
  }
  printf("\n");
}
double* LireCSV(const char *filename, int lenght)
{
  double tmp = 0;
  static double tab[lenght];
  int i = 0;
  FILE *f;
  if((f = fopen(filename, "r")) == NULL)
  {exit(-1);}
  while(!feof(f))
  {
    fscanf(f, "%lf", &tmp);
    printf("tmp = %f \n", tmp);
    tab[i] = tmp;
    i++;
  }
    fclose(f);
    return tab;
}

int main () {
  int looop=0;
  int i;

  // Pointer to store array
  int * num;
  double data[];
  // Call getArray function to get pointer to array
  num = LireCSV(data.csv, 431);
  for (int i = 0; i < 431; ++i)
  {
    data[i] =  num[i];
  }
  AffichageTab(data, sizeof(data)/sizeof(double));
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

    AffichageTab(tableauValeurVolt, sizeof(tableauValeurVolt)/sizeof(double));


    // Calule la running average du leq
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





    indexTableau++;
    if (indexTableau==nbValeur)
    {
      indexTableau=0;
    }



    //copie tableau
    for(int i=0; i<nbValeur;i++)
    {
      tableauValeurVolt_leq10[i]=tableauValeurVolt[i];
    }

    // Trie le tableau tels que les valeurs les + grandes soient en premiere position
    qsort(tableauValeurVolt_leq10, sizeof tableauValeurVolt_leq10 / sizeof *tableauValeurVolt_leq10, sizeof *tableauValeurVolt_leq10, cmp);

    AffichageTab(tableauValeurVolt_leq10, sizeof(tableauValeurVolt_leq10)/sizeof(double));

    //somme les valeurs utile pour le Leq10
    int sum10 =0;
    for (int i=0; i<(nbValeur/10); i++)
    {
      sum10+= tableauValeurVolt_leq10[i];
    }

    // Calcule les leq
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
