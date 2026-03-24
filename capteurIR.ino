#include <QTRSensors.h>

#define IR1 2
#define IR2 3
#define IR3 4

QTRSensors qtr;
const uint8_t capteur[] = {IR1, IR2, IR3};
uint16_t resultat[3];

void setup() {
  Serial.begin(9600);
  
  qtr.setTypeRC();
  qtr.setSensorPins(capteur, 3);
  for (int i = 0; i < 400; i++){
    qtr.calibrate();
  }
}
// 3 2 1 vcc gnd
void loop() {
  qtr.readCalibrated(resultat);
  for (int i = 0; i < 3; i++){
    Serial.print(resultat[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
