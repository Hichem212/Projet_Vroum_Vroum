// #define DEBUG

#define MINSPD 100
#define MAXSPD 140
#define PAS 10
#define DELTA 50 

unsigned long t;
int vM1, vM2;

typedef enum {
  TOUT_DROIT,
  SANS_LIGNE,
  VIRAGE_GAUCHE,
  VIRAGE_DROIT,
  ARRET
} Etat;

typedef enum {
  GAUCHE,
  DROITE
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

// met a jour etat et affiche les infos du robot si en mode debug
void actuInfos(void) {
  #ifdef DEBUG
  Serial.print(etatPrecedent);
  Serial.print(" | ");
  Serial.print(etatCourant);
  affichageCapteur();
  #endif
  Etat temp = etatCourant;
  etatCourant = nouvEtat();
  if (etatCourant != temp) {
    etatPrecedent = temp;
  }
}

// programme de deplacement du robot lent mais robuste,
// inpire du deplacement des chenilles des vehicules lent (ex: tank)
void chenille(void) {
  actuInfos();
  if (etatCourant == TOUT_DROIT) {
    avancer(MAXSPD, MAXSPD, true);
  } else if (etatCourant == VIRAGE_GAUCHE || (etatCourant == SANS_LIGNE && etatPrecedent == VIRAGE_GAUCHE)) {
    rotation(MINSPD, MINSPD, GAUCHE);  
  } else if (etatCourant == VIRAGE_DROIT || (etatCourant == SANS_LIGNE && etatPrecedent == VIRAGE_DROIT)) {
    rotation(MINSPD, MINSPD, DROITE);
  } else {
    avancer(MAXSPD, MAXSPD, true);
  }
}

void algoDepPID(void) {
  rampeContraste();
  calculPID();
  avancer(vM1, vM2, true);
}

void loop() {
  #ifdef DEBUG
  // calculPID();
  // avancer(vM1, vM2, true);
  // avancer(MAXSPD, MAXSPD, true);
  // rotation(MINSPD, MINSPD, DROITE);
  #else
  chenille();
  #endif
}
