// #include <QTRSensors.h>

#define IR1 2
#define IR2 3
#define IR3 4

int rampeCapteur(int IR) {
  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH);
  delayMicroseconds(10);
  pinMode(IR, INPUT);
  digitalWrite(IR, LOW);
  long t_in = micros();
  while (digitalRead(IR) == HIGH){
    ;
  }
  long t_out = micros();
  return t_out - t_in;
}

void affichageCapteur() {
  Serial.print("IR 1 : ");
  Serial.print(rampeCapteur(IR1));
  Serial.print("| IR 2 : ");
  Serial.print(rampeCapteur(IR2));
  Serial.print("| IR 3 : ");
  Serial.println(rampeCapteur(IR3));
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world !");
}

void loop() {
  delay(1000);
  affichageCapteur();
}



// QTRSensors qtr;
// const uint8_t capteur[] = {IR1, IR2, IR3};
// uint16_t resultat[3];

// void setup() {
//   Serial.begin(9600);
  
//   qtr.setTypeRC();
//   qtr.setSensorPins(capteur, 3);
//   for (int i = 0; i < 400; i++){
//     qtr.calibrate();
//   }
// }
// // 3 2 1 vcc gnd
// void loop() {
//   qtr.readCalibrated(resultat);
//   for (int i = 0; i < 3; i++){
//     Serial.print(resultat[i]);
//     Serial.print(" ");
//   }
//   Serial.println("");
// }
