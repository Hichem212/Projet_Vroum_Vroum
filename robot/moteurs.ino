#define E1 6
#define M1 7
#define E2 5
#define M2 4  

#define OFFSETM1 0.8
#define OFFSETM2 1.0

#define Kp 1
#define Ki 0
#define Kd 0
int ep = 0;
int sum = 0;

#define MAXERRPID 100
int lstErr[MAXERRPID] = {0};
int indiceErr = 0;

int cplMoteur[2][2] = {{E1, M1}, {E2, M2}};

// initialise les pins et variables des moteurs
void initMoteurs() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  vM1 = (MINSPD+MAXSPD)/2;
  vM2 = vM2;
}

// reinitialise les vitesses des moteurs a la vitesse minimale
void restetVit(void) {
  vM1 = MINSPD;
  vM2 = MINSPD;
}

// incremente de v1 et v2 les vitesses des moteurs vM1 et vM2 (dans l'intervalle [MINSPD; MAXSPD])
void incrVit(int v1, int v2) {
  vM1 = max(MINSPD, min(vM1+v1, MAXSPD));
  vM2 = max(MINSPD, min(vM2+v2, MAXSPD));
}

// actionne un moteur en envoyant sa vitesse et son sens aux pins du moteur
void actMoteur(int moteur[2], int vitesse, int sens) {
  if (vitesse > MAXSPD) 
    vitesse = MAXSPD;
  digitalWrite(moteur[1],sens);
  analogWrite(moteur[0], vitesse);
}

// fait avancer le robot en envoyant la vitesse vM1 et vM2 au moteur m1 et m2
void avancer(int vM1, int vM2, bool avancer) {
  actMoteur(cplMoteur[0], vM1 * OFFSETM1, avancer);
  actMoteur(cplMoteur[1], vM2 * OFFSETM2, !avancer);
  delay(30);
}

// fait tourner les roues du robot dans le sens oppose pour le faire tourner sur place
void rotation(int vM1, int vM2, Direction direction) {
  actMoteur(cplMoteur[0], vM1 * OFFSETM1, direction);
  actMoteur(cplMoteur[1], vM2 * OFFSETM2, direction);
  delay(30);
}

// calcul du PID des roues
int calculPID(void) {
  sum -= lstErr[indiceErr];
  lstErr[indiceErr] = ecartLigne();
  sum += lstErr[indiceErr];
  int u = Kp * lstErr[indiceErr] + Ki * sum + Kd * (lstErr[indiceErr] - ep);
  ep = lstErr[indiceErr];
  indiceErr = (indiceErr+1)%MAXERRPID;
  incrVit(-u, u);
}

// =======================================
//        DEBUG
// =======================================

// fonction de test pour les moteurs du robot
void testMoteur(void) {
  Serial.println("moteurs stop");
  for (int i = 0; i < 100; i++) {
    avancer(0, 0, true);
  }
  Serial.println("moteurs progressif");
  for (int i = 0; i < MAXSPD; i++) {
    avancer(i, i, true);
  }
  for (int i = 0; i < MAXSPD; i++) {
    avancer(MAXSPD-i, MAXSPD-i, true);
  }
  Serial.println("moteur 0 et 1 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(MAXSPD, MAXSPD, true);
  }
  Serial.println("moteur 0 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(MAXSPD, 0, true);
  }
  Serial.println("moteur 1 a vMax");
  for (int i = 0; i < 100; i++) {
    avancer(0, MAXSPD, true);
  }
  
}