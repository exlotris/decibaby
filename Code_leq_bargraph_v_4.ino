#include <SparkFunBarGraph.h>
#include <ArduinoSort.h>
#include <math.h>
#include <SPI.h>

// Info : 

//Pin declaration*******************************************************
byte microPin = A0;          // select the input pin for the micro input
//byte Led_Leq_Max_Pin = 7;      // LED of the Leq Max
//byte Led_Leq_10_Pin = 6;      // LED Leq10
//byte Led_Leq_Pin = 5;         //LED leq
//**********************************************************************
//Declaration des valeurs de parametre

int microValue[20]; // Le nombre de valeurs considerees dans le calcul du Leq
int NbSample = 20; // Doit avoir la meme valeur que microValue[]
int averageMicroValue[300]
int NbTotalSample = 300;
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
const int numbargraphs = 1;// Number of Bargraph board, ne doit pas être changé

// Declaration du tableau qui collecte toutes les valeurs dans Leq
double Running_Average_Buffer_Leq[Running_Average_Count_Leq];
int Next_Running_Average_Leq;
// Declaration du tableau qui collecte toutes les valeurs dans leq10
double Running_Average_Buffer_Leq10[Running_Average_Count_Leq10];
int Next_Running_Average_Leq10;
// Declaration du tableau qui collecte les 2 valeurs du Leqmax
double LeqMaxBuffer[2] = {0,0}; 

// Bargraph object : we call it BG
SFEbarGraph BG;

void setup() {
//declare which pin is for input and output
//pinMode(Led_Leq_Max_Pin, OUTPUT);
//pinMode(Led_Leq_10_Pin, OUTPUT);
//pinMode(Led_Leq_Pin, OUTPUT);
Serial.begin(115200);
  // Without parameters, it defaults to one bargraph board and LATch pin set to 10 on Uno, or 53 on Mega.
  // You can also call it with the number of daisy-chained boards (1-8, default 1), using the default LATch pin.
  // Or you can call it with both the number of boards and the LATch pin you wish to use.
  // For two bargraphs and pin 9 for the latch pin, call BG.begin(2,9);
  BG.begin(numbargraphs); //LATch pin set to 10 on Uno, or 53 on Mega.
}
//*********************************************************************************
//*********************************************************************************
void loop()
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

NewValue[nouvelEmplacement]=(int)sum/NbSample;
nouvelEmplacement++
if nouvelEmplacement >  nbSample {
  nouvelEmplacement=0;
}
for(){
NewValue_Leq10[]=NewValue[];
}


if (AssezDeValeur >= NbTotalSample)
  {
    Running_Leq -= LastValue;
    Running_Leq += NewValue;
  }
else
  {
    Running_Leq += NewValue
  }
                                      // Calule la running average du leq


                                      // Trie le tableau tels que les valeurs les + grandes soient en premiere position
sortArrayReverse(NewValue_Leq10,NbTotalSample); 

sum10=10%NewValue_Leq10




                                      // Calcule le leq du tableau microValue
leq = 20*log10(Running_Leq/(NbSample*V_0/1000)); 
                                      // Modification du calcul du leq



                                      // Calcule le leq10 du tableau microValue
//for (int j=0; j<(10/100)*NbSample; j++)
//{ sum10 +=  microValue[j];}           // calcule la somme de 10% des valeurs les + elevees du tableau

leq10 = 20*log10(sum10/(0.1*NbSample*V_0/1000)); 




                                      // Calcule le leqmax du tableau microValue
leqmax = 20*log10((NewValue_Leq10[0]+NewValue_Leq10[1])/(2*V_0/1000));  





















/////Affichage des bargraph/////
                                      // Declaration des constantes pour leds à eclairer bargraph
unsigned char spot;
unsigned char spot10;
unsigned char spotleq;

int delta_leq_abs = abs(previous_leq - leq); // calculate the absolute value of the difference btw prevous and current leq value
int delta_leq_10_abs = abs(previous_leq10 - leq10); // calculate the absolute value of the difference btw prevous and current leq value
int delta_leq_max_abs = abs(previous_leqmax - leqmax); // calculate the absolute value of the difference btw prevous and current leq value

//Leq Bargraph
if (delta_leq >= delta_leq_abs) // Si la difference entre valeur precedente et nouvelle valeur du leq est assez grande > Reevaluation des leds
{
   if (leq >= 90) 
   {
    for (spotleq = 1; spotleq <= 10; spotleq++)
      {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
      }
    }

   if ( (leq >= 85) && (leq < 90) )
   {
    for (spotleq = 1; spotleq <= 9; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
   }
   if ((leq >= 80) && (leq < 85) )
   {
    for (spotleq = 1; spotleq <= 8; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
   }
    if ((leq >= 75) && (leq < 80))
   {
    for (spotleq = 1; spotleq <= 7; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
    }
    if ((leq >= 70) && (leq < 75)) 
   {
    for (spotleq = 1; spotleq <= 6; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
    }

    if ((leq >= 65) && (leq < 70)) 
   {
    for (spotleq = 1; spotleq <= 5; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
   }
    if ((leq >= 60) && (leq < 65)) 
   {
    for (spotleq = 1; spotleq <= 4; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
   }

     if((leq >= 55) && (leq < 60))
   {
    for (spotleq = 1; spotleq <= 3; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
    }
    if ((leq >= 55) && (leq < 55))
   {
    for (spotleq = 1; spotleq <= 2; spotleq++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spotleq,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

    if ((leq >= 45) && (leq < 50)) 
   {
      //BG.clear(); // Clear the canvas
      BG.paint(1,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
}

// LeqMax Bargraph
if (delta_leqmax >= delta_leq_max_abs) // Si la difference entre valeur precedente et nouvelle valeur du leqmax est assez grande > Reevaluation des leds
{ 
 if ( (leqmax >= 105) ) 
 {
    for (spot = 21; spot <= 30; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
  
  if ( (leqmax >= 100) && (leqmax < 105) ) 
  {
    for (spot = 21; spot <= 29; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

  if ((leqmax >= 95) && (leqmax < 100)) 
  {
    for (spot = 21; spot <= 28; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
  
    if ((leqmax >= 90) && (leqmax < 95)) 
    {
    for (spot = 21; spot <= 27; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

    if ((leqmax >= 85) && (leqmax < 90)) 
    {
    for (spot = 21; spot <= 26; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

    if ((leqmax >= 80) && (leqmax < 85)) 
    {
    for (spot = 21; spot <= 25; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

      if ((leqmax >= 75) && (leqmax < 80)) 
      {
    for (spot = 21; spot <= 24; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

  
      if ((leqmax >= 70) && (leqmax < 75)) 
      {
    for (spot = 21; spot <= 23; spot++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

     if ((leqmax >= 65) && (leqmax < 70) ) 
     {
      //BG.clear(); // Clear the canvas
      BG.paint(21,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
  }
}

// Leq10 Bargraph                                                         //valider le else if ?
else if (delta_leq10 >= delta_leq_10_abs) // Si la difference entre valeur precedente et nouvelle valeur du leq10 est assez grande > Reevaluation des leds
{
                                                                    
 if ((leq10 >= 95)) 
 {
    for (spot10 = 11; spot10 <= 20; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
  
  if ((leq10 >= 90) && (leq10<95)) 
  {
    for (spot10 = 11; spot10 <= 19; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
   if ((leq10 >= 85) && (leq10 < 90)) 
   {
    for (spot10 = 11; spot10 <= 18; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
      if ((leq10 >= 80)&&(leq10 < 85)) 
      {
    for (spot10 = 11; spot10 <= 17; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
        if ((leq10 >= 75) && (leq10 < 80)) 
        {
    for (spot10 = 11; spot10 <= 16; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }

      if ((leq10 >= 70) && (leq10 < 75)) 
      {
    for (spot10 = 11; spot10 <= 15; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
    if ((leq10 >= 65) && (leq10 < 70)) 
    {
    for (spot10 = 11; spot10 <= 14; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
    if ((leq10 >= 60) && (leq10 < 65)) 
    {
    for (spot10 = 11; spot10 <= 13; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
    if ((leq10 >= 55) && (leq10 < 60)) 
    {
    for (spot10 = 11; spot10 <= 12; spot10++)
    {
      //BG.clear(); // Clear the canvas
      BG.paint(spot10,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
  }
   if ((leq10 >= 50) && (leq10 < 55)) 
   {
      BG.paint(11,HIGH); // Turn on one LED
      BG.send(); // Send the canvas to the display
    }
}

previous_leq=leq; //Valeur utilisée pour le delta
previous_leq10=leq10; //Valeur utilisée pour le delta
previous_leqmax=leqmax; //Valeur utilisée pour le delta
}


