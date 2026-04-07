#include <Servo.h>


void setup() {
  Serial.begin(9600);
  initMoteurs();
}

void loop() {
  // testIR();
  // testMoteur();

  rampeContraste();
  affichageCapteur();
  char vM1 = 255, vM2 = 255;
  if (sousSeuil(0)) {
    vM2 = 0;
  }
  if (sousSeuil(2)) {
    vM1 = 0;
  }
  avancer(vM1, vM2);
}
