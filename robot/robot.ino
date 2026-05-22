// #define DEBUG
// #define PID

#ifdef PID
#define MINSPD 80
#define VIRASPD 125
#define DROISPD 180
#define MAXSPD 250
#else
#define MINSPD 120//100
#define MAXSPD 160//140
#define DROISPD (MAXSPD+MINSPD)/2
#endif
#define DELTA 10 // 100 Hz


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

// met a jour etat
void actuInfos(void) {
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
  actuInfos();
  // if (etatCourant == VIRAGE_DROIT || etatCourant == VIRAGE_GAUCHE || etatCourant == SANS_LIGNE) {
   
  // } 
  bool ajust = t + DELTA > millis();
  if (ajust) {
    calculPID();
    t = millis();
  }
  avancer(vM1, vM2, true);
  if (ajust) {
    restetVit();
  }
}

void loop() {
  #ifdef DEBUG
  Serial.println("");
  calculPID();
  affichageCapteur();
  afficherEtat();
  afficherVitesse();
  restetVit();
  delay(1000);
  #else
    #ifdef PID
    algoDepPID();
    #else
    chenille();
    #endif
  #endif
}
