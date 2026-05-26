// #define DEBUG

#define MINSPD_PID 100
#define DROISPD_PID 140
#define MAXSPD_PID 180//250

#define MINSPD_CHENILLE 100
#define MAXSPD_CHENILLE 140

#define PERDU 500 // temps en millisecondes avant d'etre considere comme perdu
#define RETROUVE 75 // temps en millisecondes avant d'etre considere comme retrouve
unsigned long t_perdu = 0;
unsigned long t_retrouve = 1; 
bool surLigne = true;

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
}

// met a jour etat, surLigne, la rampe de contraste
void actuInfos(void) {
  rampeContraste();
  Etat temp = etatCourant;
  etatCourant = nouvEtat();
  if (etatCourant != temp) {
    etatPrecedent = temp;
    
    if (etatCourant == SANS_LIGNE) {
      t_perdu = millis();
      t_retrouve = 0;
    } else {
      t_retrouve = millis();
      t_perdu = 0;
    }
  }

  if (t_perdu+PERDU < millis() && !t_retrouve) {
    surLigne = false;
  } 
  if (!t_perdu && t_retrouve+RETROUVE < millis()) {
    surLigne = true;
  }
  
}

// programme de deplacement du robot lent mais robuste,
// inpire du deplacement des chenilles des vehicules lent (ex: tank)
void chenille(void) {
  if (etatCourant == TOUT_DROIT) {
    avancer(MAXSPD_CHENILLE, MAXSPD_CHENILLE, surLigne);
  } else if (etatCourant == VIRAGE_GAUCHE || (etatCourant == SANS_LIGNE && etatPrecedent == VIRAGE_GAUCHE)) {
    rotation(MINSPD_CHENILLE, MINSPD_CHENILLE, GAUCHE);  
  } else if (etatCourant == VIRAGE_DROIT || (etatCourant == SANS_LIGNE && etatPrecedent == VIRAGE_DROIT)) {
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

void goFast(void) {
  if (etatCourant == SANS_LIGNE) {
    chenille();
  } else {
    algoDepPID();
  }
}

void loop() {
  actuInfos();
  #ifdef DEBUG
  Serial.println("");
  Serial.println(surLigne);
  // Serial.println(t_perdu);
  // Serial.println(t_retrouve);
  // calculPID();
  // affichageCapteur();
  // afficherEtat();
  // afficherVitesse();
  // restetVit();
  // delay(500);
  #else
    // algoDepPID();
    // chenille();
    goFast();
  #endif
}
