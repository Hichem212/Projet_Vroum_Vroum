#define IR1 2
#define IR2 3
#define IR3 4

#define NBCAP 3

int IRs[NBCAP] = {IR1, IR2, IR3};
int seuil[NBCAP] = {300, 200, 80};
int valeurs[NBCAP];

int contraste(int iIR) {
  int ir = IRs[iIR];
  pinMode(ir, OUTPUT);
  digitalWrite(ir, HIGH);
  delayMicroseconds(10);
  pinMode(ir, INPUT);
  digitalWrite(ir, LOW);
  long t_in = micros();
  while (digitalRead(ir) == HIGH){
    ;
  }
  long t_out = micros();

  return t_out - t_in;
}

void rampeContraste(){
  for (int iIR = 0; iIR < NBCAP; iIR++) {
    valeurs[iIR] = contraste(iIR);    
  }
}

bool sousSeuil(int iIR){
  // bool activation[NBCAP];
  // for (int iIR = 0; iIR < NBCAP; iIR++) {
  //   activation[iIR] = valeurs[iIR] <= seuil[iIR];    
  // }
  return valeurs[iIR] <= seuil[iIR];
}

void affichageCapteur() {
  Serial.print("IR 1 : ");
  Serial.print(valeurs[0]);  
  Serial.print(" | IR 2 : ");
  Serial.print(valeurs[1]);
  Serial.print(" | IR 3 : ");
  Serial.println(valeurs[2]);
}
