String data = "";
short j = 2;

void Sendtemp()
{
  //Serial.println("IN");   //Important
  if (onetime == true)
  {
    BTserial.println("");
    onetime = false;
    Serial.println("ezzae");
    Serial.println(onetime);
    sdread();
  }


  String n = String(j, DEC); //j correspond au nombres de string plusieurs string
  if (res == "Wait")
  {

    //  Serial.println("IN2");

    BTserial.println(numberofstrings); //Envoi  un premier morceaux de chaine à l'application

    // Serial.println("Carte");  //detecte quand on appuie sur le bouton demande
    reset();
  }
  if (res == "SEE")
  {
    BTserial.println(demandedata());

    // Serial.println("Carte");  //detecte quand on appuie sur le bouton demande
    reset();
  }
  else if (res == String("Data" + n)) //Envoi les morceaux des chaines suivant à l'application
  {

    BTserial.println(demandedata());
    //Serial.println("part2");  //detecte quand on appuie sur le bouton demande
    res = "0";
    j++;
    clearbuf = 0;          //Améliorable
    res = "0";
    temp = "";

    if (j == numberofstrings)
    {
      j = 2;
      Comeagaintemprature = false;  //Detecte la fin de la transmission
      // onetime = true;
    }
  }

  else if (res == "111")
  {
    Serial.println("capteurs");
    //    Serial.println(String(capteur.readTempC(),1)+String(capteur.readFloatPressure(),0)+String(capteur.readFloatHumidity(),0)); //Envoi des données capteurs
    BTserial.println(String(capteur.readTempC(), 1) + String(capteur.readFloatPressure(), 0) + String(capteur.readFloatHumidity(), 0)); //Envoi des données capteurs en temps réel
    //onetime=true;
    clearbuf = 0;
    res = "0";
  }
  else {
    reset();
  }
}

void reset() //permet de clear les buffers et de reset j
{
  clearbuf = 0;
  res = "0";
  temp = "";
  j = 2;

}
