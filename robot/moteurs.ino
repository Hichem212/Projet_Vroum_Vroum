#define E1 6
#define M1 7
#define E2 5
#define M2 4  

#define MAXSPD 255

int cplMoteur[2][2] = {{E1, M1}, {E2, M2}};

void initMoteurs() {
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
}

void actMoteur(int moteur[2], int vitesse, int sens) {
  if (vitesse > MAXSPD) return;
  digitalWrite(moteur[1],sens);
  analogWrite(moteur[0], vitesse);
}

void avancer(char vM1, char vM2) {
  actMoteur(cplMoteur[0], vM1, LOW);
  actMoteur(cplMoteur[1], vM2, HIGH);
  delay(30);
}

void testMoteur(void) {
  Serial.println("moteurs stop");
  for (int i = 0; i < 100; i++) {
    avancer(0, 0);
  }
  Serial.println("moteur 0 et 1 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(MAXSPD, MAXSPD);
  }
  Serial.println("moteur 0 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(MAXSPD, 0);
  }
  Serial.println("moteur 1 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(0, MAXSPD);
  }
  
}