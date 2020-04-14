void capteur_ini()
{
  capteur.settings.commInterface = I2C_MODE;
  capteur.settings.I2CAddress = 0x76;
  capteur.settings.runMode = 3;
  capteur.settings.tStandby = 0;
  capteur.settings.filter = 0;
  capteur.settings.tempOverSample = 1 ;
  capteur.settings.pressOverSample = 1;
  capteur.settings.humidOverSample = 1;  //Initialisa le capteur de température
  Serial.println("TT");
  delay(20);
  capteur.begin();
  delay(20);
  Serial.println("Capteur initialisé");
}

void gettemperature()
{
  heat= String(capteur.readTempC(),1);
  float heats=0;
  heats=heat.toFloat();
  if (heats<10.0)
  {
    heat="0"+heat;
  }
  if (heats>0)          //On fait attention à avoir des lignes de même taille
  {
    heat="+"+heat;
  }
  //Serial.println(heat+"C");
  pressure =String(capteur.readFloatPressure(),0);
  //Serial.println(pressure+"mPa");
  humid= String(capteur.readFloatHumidity(),0);
  //Serial.println(humid+"%");
}
