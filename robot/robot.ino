// #define DEBUG

#define VITNORM 140
#define VITVIRA 80

unsigned long t;
int DELTA = 1000;

typedef enum {
  TOUT_DROIT,
  SANS_LIGNE,
  VIRAGE_GAUCHE,
  VIRAGE_DROIT,
  ARRET
} Etat;

typedef enum {
  GAUCHE,
  DROIT
} Direction;


Etat etatPrecedent;
Etat etatCourant;

void setup() {
  Serial.begin(9600);
  initMoteurs();
  etatPrecedent = NULL;
  etatCourant = TOUT_DROIT;
  t = 0;
}

// met a jour etat et affiche les valeurs des capteurs
void actuInfos(void) {
  Serial.print(etatCourant);
  affichageCapteur();
  t = millis();
  Etat temp = etatCourant;
  etatCourant = nouvEtat(&DELTA);
  etatPrecedent = temp;
}

// code pour robot dans etat TOUT_DROIT
void toutDoit(void) {
  rampeContraste();
  int vM1 = VITNORM, vM2 = VITNORM;
  if (!sousSeuil(0)) {
    vM1 = 0;
  }
  if (!sousSeuil(2)) {
    vM2 = 0;
  }
  avancer(vM1, vM2, true);
}

// code pour robot dans etat virage gauche/droit
void virage(Direction direction) {
  int vM1 = VITVIRA, vM2 = VITVIRA;
  // avancer(vM1, vM2, false);

  // vM1 -= (vM1/2)*(1-direction);
  // vM2 -= (vM1/2)*(direction);
  vM1 *= (1-direction);
  vM2 *= direction;
  avancer(vM1, vM2, true);
}

void loop() {
  if (t+DELTA < millis()){
    actuInfos();
  }
  #ifndef DEBUG
  switch (etatCourant) {
    case TOUT_DROIT: 
      toutDoit();
      break;
    case SANS_LIGNE:
      avancer(VITNORM, VITNORM, true);
      break;
    case VIRAGE_GAUCHE:
      virage(GAUCHE);
      break;
    case VIRAGE_DROIT:
      virage(DROIT);
      break;
    default:
      break;
  }
  #endif
}
