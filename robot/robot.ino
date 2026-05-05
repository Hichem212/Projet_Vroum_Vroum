#include <Servo.h>

#define VITNORM 140

void setup() {
  Serial.begin(9600);
  initMoteurs();
}

void loop() {
  // testIR();
  // testMoteur();

  rampeContraste();
  affichageCapteur();
  char vM1 = VITNORM, vM2 = VITNORM;
  if (sousSeuil(0)) {
    vM1 = 0;
  }
  if (sousSeuil(2)) {
    vM2 = 0;
  }
  avancer(vM1, vM2);
}
