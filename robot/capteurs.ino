// moteur sur pin 4/5/6/7 (d'apres doc)
// donc si capteur sur pin 4, moteur devient vibreur

#define IR1 11
#define IR2 12
#define IR3 13

#define NBCAP 3
#define MAXITE 1000

int IRs[NBCAP] = {IR1, IR2, IR3};
int seuil[NBCAP] = {300, 200, 100};
int valeurs[NBCAP];

int contraste(int iIR) {
  int ir = IRs[iIR];
  pinMode(ir, OUTPUT);
  digitalWrite(ir, HIGH);
  delayMicroseconds(10);
  pinMode(ir, INPUT);
  digitalWrite(ir, LOW);
  long t_in = micros();
  int ite = 0;
  while (digitalRead(ir) == HIGH && ite < MAXITE){
    ite++;
  }
  long t_out = micros();

  if (ite == MAXITE) {
    return 999;
  } return t_out - t_in;
}

void rampeContraste(void){
  for (int iIR = 0; iIR < NBCAP; iIR++) {
    valeurs[iIR] = contraste(iIR);    
  }
}

bool sousSeuil(int iIR){
  return valeurs[iIR] > seuil[iIR];
}

void affichageCapteur(void) {
  for (int i = 0; i < NBCAP; i++) {
    Serial.print("| IR ");
    Serial.print(i);
    Serial.print(" (");
    Serial.print(seuil[i]);
    Serial.print("): ");
    Serial.print(valeurs[i]);  
  } Serial.println("");
}

void testIR(void) {
  delay(1000);
  rampeContraste();
  affichageCapteur();
  for (int i = 0; i < 3; i++) {
    if (sousSeuil(i)) {
      Serial.print(i+1);
      Serial.println(" -> GO VROUM VROUM !!!");
    }
  }
}
