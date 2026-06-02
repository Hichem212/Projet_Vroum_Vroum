// #define DEBUG

#define MINSPD_PID 100
#define DROISPD_PID 140
#define MAXSPD_PID 180//250

#define MINSPD_CHENILLE 120
#define MAXSPD_CHENILLE 160

#define PERDU 500 // temps en millisecondes avant d'etre considere comme perdu
// #define ROTA 200

typedef enum {
  TOUT_DROIT,
  SANS_LIGNE,
  VIRAGE_GAUCHE,
  VIRAGE_DROIT,
  RETROUVE_LIGNE,
  ARRET
} Etat;

unsigned long t_perdu = 0;
unsigned long t_retrouve = 1; 
bool surLigne = true;

int vM1, vM2;

typedef enum {
  GAUCHE,
  DROITE
} Direction;

void setup() {
  Serial.begin(9600);
  initMoteurs();
  initEtat();
}

// met a jour etat, surLigne, la rampe de contraste
void actuInfos(void) {
  rampeContraste();
  actuEtat();
  surLigne = !(t_perdu+PERDU < millis() && !t_retrouve);
}

// programme de deplacement du robot lent mais robuste,
// inpire du deplacement des chenilles des vehicules lent (ex: tank)
void chenille(void) {
  if (etatCourant() == TOUT_DROIT) {
    avancer(MAXSPD_CHENILLE, MAXSPD_CHENILLE, surLigne);
  } else if (etatCourant() == VIRAGE_GAUCHE || (etatCourant() == SANS_LIGNE && etatPrecedent() == VIRAGE_GAUCHE)) {
    rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, GAUCHE);  
  } else if (etatCourant() == VIRAGE_DROIT || (etatCourant() == SANS_LIGNE && etatPrecedent() == VIRAGE_DROIT)) {
    rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, DROITE);
  } else {
    avancer(MAXSPD_CHENILLE, MAXSPD_CHENILLE, surLigne);
  }
}

// programme de deplacement du robot rapide mais ne sait pas tourner,
// utilise l'algorithme du PID
void algoDepPID(void) {
  calculPID();
  avancer(vM1, vM2, surLigne);
  restetVit();
}

// combine tout pour aller vite et etre resistant
void systemCombine(void) {
  if (etatCourant() == TOUT_DROIT) {
    algoDepPID();
  } else if (etatCourant() == VIRAGE_GAUCHE || (etatCourant() == SANS_LIGNE && etatPrecedent() == VIRAGE_GAUCHE)) {
    rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, GAUCHE);  
  } else if (etatCourant() == VIRAGE_DROIT || (etatCourant() == SANS_LIGNE && etatPrecedent() == VIRAGE_DROIT)) {
    rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, DROITE);
  } else if (etatCourant() == SANS_LIGNE && etatPrecedent() == TOUT_DROIT) {
      avancer(MAXSPD_CHENILLE, MAXSPD_CHENILLE, surLigne);
  } else {
    retrouveLigne();
  }
}

void loop() {
  actuInfos();
  #ifdef DEBUG
  Serial.println("");
  // Serial.println(surLigne);
  // rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, GAUCHE);
  // Serial.println(t_perdu);
  // Serial.println(t_retrouve);
  // calculPID();
  // affichageCapteur();
  afficherEtat();
  // afficherVitesse();
  // restetVit();
  delay(250);
  #else
    // algoDepPID();
    // chenille();
    systemCombine();
  #endif
}
