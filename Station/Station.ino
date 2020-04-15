
#include <AltSoftSerial.h>
#include <Wire.h>
#include "LowPower.h"
#include "SparkFunBME280.h"
#include <SPI.h>
#include <SD.h>
#include <RtcDS3231.h>


File myFile;
AltSoftSerial BTserial;
BME280 capteur;

void Sendtemp();
const int wakeUpPinBLE = 3;
const byte interruptPinrtcminutes = 2;
String heures;
String heat = "",  pressure = "",humid = "";
short clearbuf = 0;
short sleep = 1;
short seed;
String temp = "";
String res = "0";
unsigned long numberofstrings = 0;
volatile bool alarm = 0;
boolean Comeagaintemprature = false;
boolean onesetup = true;            //permet de faire le setup apres le réveil une fois
boolean BLEdisco = false;
boolean onetime = true;

void Restartcarte() //Cette fonction pemet d'affecter un état haut sur la pin RST de arduino ce qui le reset (pas idéal mais fontionne bien)
{

  Serial.println("reset");
  delay(20);
  int rst = A2;
  // active la broche en sortie (OUTPUT)
  pinMode(rst, OUTPUT);
  // Déactive le reset forçant la sortie au niveau bas
  digitalWrite(rst, LOW);
}

void handleInterrupt() //Interruption venant du DS3231
{ 
  alarm = true;          //Cette fonction détecte l'interruption de la pin SQWs
  digitalWrite(13, !digitalRead(13));
}

void wakeUpBLE()  //Interruption venant du HM-10
{
  detachInterrupt(digitalPinToInterrupt(interruptPinrtcminutes));
  sleep = 0;
}

void discoBLE()
{
  onesetup = true;
  sleep = 1; //Pas utille vu que reset apres mais on va garder
  BLEdisco = true;
  detachInterrupt(digitalPinToInterrupt(wakeUpPinBLE));
  // attachInterrupt(digitalPinToInterrupt(interruptPinrtcminutes), handleInterrupt, FALLING); A reactiver
}

void setup()
{
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);   //Eteint de module carte SD
  Serial.begin(9600);
  setupds3231();
  delay(20);
  capteur_ini();
  pinMode(wakeUpPinBLE, INPUT_PULLUP);
}

void loop()
{
  if (sleep == 1)
  {

    BLEdisco = false;
    // Serial.println("dodo");
    delay(20);
    attachInterrupt(digitalPinToInterrupt(wakeUpPinBLE), wakeUpBLE, HIGH);//On active l'interruption pour se réveiller  //A REACITVER
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
  if (alarm == true) {
    handleAlarm();
  }
  while (true) //Boucle infine quand le BLE nous réveille
  {
    if (alarm == true)
    {
      //Serial.println("alarmebreak");
      alarm = false;
      break;
    }
    if (onesetup == true)
    {
      BTserial.begin(9600);
      detachInterrupt(digitalPinToInterrupt(wakeUpPinBLE));//On enleve toute interruption au cas ou
      attachInterrupt(digitalPinToInterrupt(wakeUpPinBLE), discoBLE, LOW);
      randomSeed(seed++);
      onesetup = false;
    }
    // On lit les entrées bluetooth et on décompose les caratères pour ensuite les assembler en chaine
    while (true)
    {
      if (BTserial.available())
      {
        if (clearbuf == 0) {
          temp = "";
        }
        char c = BTserial.read();   //Décode les messages BLE
        if (c == '`') {
          break;  //Déclenche
        }
        clearbuf++;
        String a = String(c);
        res = temp + a;
        temp = res;
      }
      if (BLEdisco == true)
      {
        break;
      }
    }

    if (res == "Temperature" || res == "111" || Comeagaintemprature == true)
    {
      Comeagaintemprature = true;
      Sendtemp();                    //On va dans le fichier Datatransfer
    }
    if (BLEdisco == true)
    {
      //  Serial.println("brek2");
      Restartcarte() ;
      break;
    }
  }
}
