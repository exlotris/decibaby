#include "SparkFunBarGraph.h"
#include "ArduinoSort.h"
#include <math.h>
#include "SPI.h"

// Info :

//Pin declaration*******************************************************
byte microPin = A0;          // select the input pin for the micro input
//byte Led_Leq_Max_Pin = 7;      // LED of the Leq Max
//byte Led_Leq_10_Pin = 6;      // LED Leq10
//byte Led_Leq_Pin = 5;         //LED leq
//**********************************************************************
//Declaration des valeurs de parametre

int microValue[20] = { }; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 20; // Doit avoir la meme valeur que microValue[]
int tableauValeurVolt[300] = { };
int tableauValeurVolt_leq10[300] = { };
int nouvelEmplacement = 0;
int nbValeur = 300;
int Running_Leq = 0;
const int V_0=1 ; //La tension correspondant au niveau zero Decibel (*1000)                    ----> A modifier

// Seuils de nouvelle évaluation de l'affichage.
int delta_leq =1; //La difference en dBA entre le leq actuel et precedent qui declenche nouvelle evaluation de l'affichage
int delta_leq10 =5; //La difference en dBA entre le leq10 actuel et precedent qui declenche nouvelle evaluation de l'affichage
int delta_leqmax =5; //La différence en dBA entre le leqmax actuel et precedent qui déclenche nouvelle evaluation de l'affichage

const int Running_Average_Count_Leq = 300;  //Constante du nombre de valeurs
const int Running_Average_Count_Leq10 = 300;  //To be defined
//*********************************************************************

//declaration of constant***********************************************
//**********************************************************************
double leq=0; // Valeur du leq initiale
double previous_leq=0; //Valeur utilisée pour le determiner si nouvelle evaluation de l'affichage
double leq10=0; // Valeur du leq10 initiale
double previous_leq10=0; //Valeur utilisée pour le determiner si nouvelle evaluation de l'affichage
double leqmax=0; //Valeur du leqmax initiale
double previous_leqmax=0; //Valeur utilisée pour le determiner si nouvelle evaluation de l'affichage
double sum10=0; //


//get the index of the minimum value in the array

int getIndexOfMin(int * array, int size){
    int min = *array;
    int i = 0 ;
    int index = 0;
    for (i = 0 ; i < size; i++){
        if (min > *(array+i)){
            min = *(array+i);
            index = i;
        }
    }
    return index;
}

//remove the minimum value from the array

void removeAnIndexFromArray(int* array, int size, int index){
    *(array + index) = 0;
    if (index != (size-1)){
        int i = index;
        for (i = index; i < (size -1); i++){
            *(array + i) = *(array + (i+1));
        }
    }
}
//code pour trier tableau
int* sortArray(int* array, int size){
    int min  = *array;
    int originalSize = size;
    int * temp;
    temp = (int* )malloc(sizeof(int) * size);
    int i = size-1;
    int index;
    while(size > 0){
        index = getIndexOfMin(array,size);
        temp[i--] = array[index];
        removeAnIndexFromArray(array, size --,index);
    }
    return temp;
}

//*********************************************************************************
//*********************************************************************************
void main()
{
                                      // read the value from the micro after filtering:
for(int i=0; i<NbSample; i++) {
microValue[i] = analogRead(microPin); // Lit les valeurs du micro et les stock dans le tableau microValue[],
                                      // ces valeurs sont sous forme de voltage
}

                                      // Calcule la moyenne des valeurs de microValue
int sum =0;
for (int i=0; i<NbSample; i++)
{ sum+= microValue[i]; }

tableauValeurVolt[nouvelEmplacement]=(int)sum/NbSample;

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
if (nouvelEmplacement==nbValeur) {
  nouvelEmplacement=0;
}
for(int i=0; i<nbValeur;i++){
tableauValeurVolt_leq10[i]=tableauValeurVolt[i];
}




                                      // Trie le tableau tels que les valeurs les + grandes soient en premiere position
NewValue_Leq10 = sortArray(NewValue_Leq10,NbTotalSample);
int sum10 =0;
for (int i=0; i<(nbValeur/10); i++)
  {
    sum10+= tableauValeurVolt_leq10[i];
  }


                                      // Calcule le leq du tableau microValue
leq = 20*log10(Running_Leq/(nbValeur*V_0/1000));
                                      // Modification du calcul du leq

leq10 = 20*log10(sum10/((nbValeur/10)*V_0/1000));

                                      // Calcule le leqmax du tableau microValue
leqmax = 20*log10((tableauValeurVolt_leq10[0]+tableauValeurVolt_leq10[1])/(2*V_0/1000));
}
