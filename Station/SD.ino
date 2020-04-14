void savesSD() {  //Ce code est inspiré des exemples de la librairie SD il inscrit les valeurs mesurés sur la carte SD
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH); //On sature le transistor pour activer le module carte SD
  delay(50);
  SD.begin(4);
  myFile = SD.open("cpateurs.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(heures+" "+heat+"C"+" "+pressure+"Mpa"+" "+humid+"%");
    myFile.close();
  } else {
  }
  digitalWrite(A0, HIGH);
}
