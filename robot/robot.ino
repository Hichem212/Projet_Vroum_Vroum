
void setup() {
  Serial.begin(9600);
  // initMoteurs();
}

void loop() {
  delay(1000);
  rampeContraste();
  affichageCapteur();
  if (sousSeuil(0) || sousSeuil(1) || sousSeuil(2)) {
    Serial.println("GO VROUM VROUM !!!!!!");
    // goVroumVroum();
  }
}
