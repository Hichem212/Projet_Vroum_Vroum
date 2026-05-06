#define VITNORM 140
#define DELTA 1000

unsigned long t;

typedef enum etat {
  TOUT_DROIT,
  SANS_LIGNE,
  VIRAGE_GAUCHE,
  VIRAGE_DROIT,
  ARRET
} Etat;

Etat etatCourant;

void setup() {
  Serial.begin(9600);
  initMoteurs();
  etatCourant = TOUT_DROIT;
  t = 0;
}

// met a jour etat et affiche les valeurs des capteurs
void actuInfos(void) {
  affichageCapteur();
  t = millis();
  etatCourant = nouvEtat();
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
  avancer(vM1, vM2);
}

void loop() {
  // actualise son etat tout les 1000 millis
  if (t+DELTA < millis()){
    actuInfos();
  }
  switch (etatCourant) {
    case TOUT_DROIT: 
      toutDoit();
      break;
    case SANS_LIGNE:
      toutDoit();
      break;
    default:
      break;
  }
}
