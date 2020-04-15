unsigned long pos = 0;
char valtemperature [6];
String valtemperaturestring;
String petitechaine = "";
int cpt = 0;

void sdread() {
   pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);

  SD.begin(4);
  delay(20);
 // Serial.println("card initialized.");

     myFile = SD.open("cpateurs.txt");
       delay(20);
  pos = myFile.size();
  delay(20);
    myFile.close();
  Serial.print("pos= ");
 Serial.println(pos);
 if (pos>=10000)  //Cette partie est à completer
 {
   numberofstrings=(pos/1000)*2*10;
 }
 else
 {
  numberofstrings=(pos/100)*2*10;
 }
  pos = pos - 21;

  delay(20);
}

String demandedata() {                   //Lit les morceaux de chaines dans la carte sd et les renvoi.
 Serial.print("pos :");
  Serial.println(pos);
  myFile = SD.open("cpateurs.txt");
  petitechaine = "";
  while (true)
  {
    myFile.seek(pos);
    for  (int i = 0; i <= 4; i++)
    {
      valtemperature [i] = myFile.read();
    }
    valtemperaturestring = valtemperature;
    petitechaine = petitechaine + valtemperaturestring;
    pos = pos - 33;
    cpt++;
    if (cpt == 3) //Detecte la fin d'un morceau de chaine
    {
      Serial.println(petitechaine);
      cpt = 0;
      myFile.close();
      delay(20);
      return petitechaine;
      break;
    }
  }
}
