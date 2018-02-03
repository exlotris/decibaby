#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>//necessaire pour la fonction delay
#include <math.h>//necessaire pour la fonction log10

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define ADDRESS 0x04 //adress de l'arduino
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";

double microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 10; // Doit avoir la meme valeur que microValue[]
double tableauValeurVolt[40] = { };
double tableauValeurVolt_leq10[40] = { };
int indexTableau = 0;
int nbValeur = 40;
double Running_Leq = 0;
double V_0=0.000348 ; //La tension correspondant au niveau zero Decibel (*1000)
double leq=0; // Valeur du leq initiale
double leq10=0; // Valeur du leq10 initiale
double leqmax=0; //Valeur du leqmax initiale
double sum =0;
double sum10=0; //
int AnalogReadArduino=0;


//fonction pour le tri du tableau
static int cmp (void const *a, void const *b)
{
   int ret = 0;
   double const *pa = a;
   double const *pb = b;
   double diff = *pb - *pa;//ce qui defini si c'est croissant ou decroissant
   if (diff > 0) {ret = 1;}
   else if (diff < 0) { ret = -1;}
   else { ret = 0;}
   return ret;
}


//permet d'afficher un tableau sur une ligne
void AffichageTab (double tableau[], int length) {
  for(int j = 0; j < length; j++) {
      printf(" %lf", tableau[j]);
  }
  printf("\n");
}


//permet de lire un fichier csv
double* LireCSV(const char *filename)
{
  double tmp = 0;
  static double tab[431];
  int i = 0;
  FILE *f;
  if((f = fopen(filename, "r")) == NULL)
  {exit(-1);}
  while(!feof(f))
  {
    fscanf(f, "%lf", &tmp);
    //printf("tmp = %f \n", tmp);
    tab[i] = tmp;
    i++;
  }
    fclose(f);
    return tab;
}

int main () {
  //*********************************************************************
  //lecture d'un fichier destiné à être remplacer par la lecture du micro
  //*********************************************************************

  int looop=0; //au final le loop sera infini

  // Pointer to store array
  double * num;
  double data[431];
  // Call getArray function to get pointer to array
  num = LireCSV("data.csv");
  for (int i = 0; i < 431; ++i)
  {
    data[i] =  num[i];
  }
  //AffichageTab(data, sizeof(data)/sizeof(double));
  //*********************************************************************
  //*********************************************************************

  //*********************************************************************
  //lecture de l'arduino destiné à être remplacer par un adc
  //*********************************************************************
  printf("I2C: Connecting\n");
  int file;

  if ((file = open(devName, O_RDWR)) < 0) {
    fprintf(stderr, "I2C: Failed to access %d\n", devName);
    exit(1);
  }

  printf("I2C: acquiring buss to 0x%x\n", ADDRESS);

  if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
    fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
    exit(1);
  }
  //*********************************************************************
  //*********************************************************************


  while (looop<1000) {
    /*int array[NbSample];
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
    */
    //tableauValeurVolt[indexTableau]=data[looop];

    //AffichageTab(tableauValeurVolt, sizeof(tableauValeurVolt)/sizeof(double));
    int val;
    unsigned char cmd[16];
    cmd[0] = 1;
        // As we are not talking to direct hardware but a microcontroller we
        // need to wait a short while so that it can respond.
        //
        // 1ms seems to be enough but it depends on what workload it has

    if (write(file, cmd, 1) == 1) {
        usleep(10000);
        char buf[2];
        char a,b;
        read(file, buf, 2);
        printf("Received %d\n", buf[0]);
        a = buf[0];
        printf("Received %d\n", buf[1]);
        b = buf[1];
        AnalogReadArduino = a;
        AnalogReadArduino = AnalogReadArduino << 8 | b;
        //AnalogReadArduino = (int) buf[0];
        printf("Received %lf\n", AnalogReadArduino/204.8);
        }

    tableauValeurVolt[indexTableau]=AnalogReadArduino/204.8;
    //AffichageTab(tableauValeurVolt, sizeof(tableauValeurVolt)/sizeof(double));

    // Calule la moyenne du leq
      if (indexTableau != nbValeur-1)
      {
        Running_Leq -= tableauValeurVolt[indexTableau+1];
        Running_Leq += tableauValeurVolt[indexTableau];
      }
      else
      {
        Running_Leq -= tableauValeurVolt[0];
        Running_Leq += tableauValeurVolt[indexTableau];
      }

    //augmente l'index du tableau de valeur principale, et le retourne a zero si necessaire
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

    //AffichageTab(tableauValeurVolt_leq10, sizeof(tableauValeurVolt_leq10)/sizeof(double));

    //somme les valeurs utile pour le Leq10
    sum10=0;
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
    delay(70);
  }
  return(0);
}
