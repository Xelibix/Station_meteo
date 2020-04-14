RtcDateTime temps;
RtcDS3231<TwoWire> rtcObject(Wire);
void stockageheure() {
  RtcDateTime sotcktemps = rtcObject.GetDateTime();
 // Serial.println(sotcktemps);
  sprintf(times, "%d/%d %d:%d",
          sotcktemps.Day(),
          sotcktemps.Month(),
          sotcktemps.Hour(),
          sotcktemps.Minute()
         );
   for (int i = 10 - 1; i > 0; i--) {
    if ( sotcktemps.Day() < 10) {
      times[i] = times[i - 1];  //On décale le tableau de 1 vers la "droite"
    }
    if ( sotcktemps.Month() < 10) {
      times[i + 3] = times[i + 3 - 1];
    }
    if ( sotcktemps.Hour() < 10) {
      times[i + 6] = times[i + 6 - 1];
    }
    if ( sotcktemps.Minute() < 10) {      //On fait attention à ce que chaque ligne ai la même taille
      times[i + 9] = times[i + 9 - 1];
    }
  }
  if ( sotcktemps.Day() < 10) {
       times[0] = 48;
    }
    if ( sotcktemps.Month() < 10) {
      times[3] = 48;
    }
    if ( sotcktemps.Hour() < 10) {
      times[6] = 48;
    }
    if ( sotcktemps.Minute() < 10) {
      times[9] = 48;
    }
  heures = times; //A améliorer
  delay(100);
}
void setupds3231() {                                        //Dans le void setup on va parametre le module rtc
  delay(20);
  pinMode(interruptPinrtcminutes, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinrtcminutes), handleInterrupt, FALLING);  
  rtcObject.Begin();
 // RtcDateTime realtime = RtcDateTime(__DATE__, __TIME__);   //A activer uniquement quand on veut remettre à l'heure le DS3231
  //rtcObject.SetDateTime(realtime);
  temps = rtcObject.GetDateTime(); //on recupere l'heure dans le module
  rtcObject.Enable32kHzPin(false);
  rtcObject.SetSquareWavePin(DS3231SquareWavePin_ModeAlarmTwo);    //Un impultion sera envoyer sur la pin SQW à chaque d'éclenchement de l'alarme 2

  DS3231AlarmTwo alarm2(              //alarme 2
    0,
    0,                                //On parametre l'alarme 2 elle s'active ici toutes les minutes
    0,
    DS3231AlarmTwoControl_OncePerMinute);

  rtcObject.SetAlarmTwo(alarm2);
  rtcObject.LatchAlarmsTriggeredFlags();
  delay(10);
}

void handleAlarm() {

  Serial.println("alarm!!");
  delay(20);
  stockageheure();         //On lit et traite l'heure
  delay(20);
  gettemperature(); //Envoi des données capteurs
  delay(20);
   savesSD();             //On sauvegarde les données sur la carte SD
  rtcObject.LatchAlarmsTriggeredFlags(); //Il faut réactiver la flag sinon l'alarme ne sera jamais redéclenché
  delay(20);
  Restartcarte(); //Reset la carte de manière hardware
}
