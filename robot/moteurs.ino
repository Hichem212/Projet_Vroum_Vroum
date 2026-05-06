#define E1 6
#define M1 7
#define E2 5
#define M2 4  

#define MAXSPD 255
#define OFFSETM1 0.75
#define OFFSETM2 1.0

int cplMoteur[2][2] = {{E1, M1}, {E2, M2}};

// initialise les pins des moteurs
void initMoteurs() {
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
}

// actionne un moteur en envoyant sa vitesse et son sens aux pins du moteur
void actMoteur(int moteur[2], int vitesse, int sens) {
  if (vitesse > MAXSPD) return;
  digitalWrite(moteur[1],sens);
  analogWrite(moteur[0], vitesse);
}

// fait avancer le robot en envoyant la vitesse vM1 et vM2 au moteur m1 et m2
void avancer(int vM1, int vM2) {
  actMoteur(cplMoteur[0], vM1 * OFFSETM1, HIGH);
  actMoteur(cplMoteur[1], vM2 * OFFSETM2, LOW);
  delay(50);
}

void testMoteur(void) {
  Serial.println("moteurs stop");
  for (int i = 0; i < 100; i++) {
    avancer(0, 0);
  }
  Serial.println("moteurs progressif");
  for (int i = 0; i < MAXSPD; i++) {
    avancer(i, i);
  }
  for (int i = 0; i < MAXSPD; i++) {
    avancer(MAXSPD-i, MAXSPD-i);
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