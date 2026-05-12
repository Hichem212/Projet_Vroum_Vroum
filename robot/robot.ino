// #define DEBUG

#define VITVIRA 0//80
#define MAXSPD 140//255
#define PAS 10

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
  vM1 = MAXSPD;
  vM2 = MAXSPD;
}

// met a jour etat et affiche les valeurs des capteurs
void actuInfos(void) {
  #ifdef DEBUG
  Serial.print(etatCourant);
  affichageCapteur();
  #endif
  Etat temp = etatCourant;
  etatCourant = nouvEtat();
  if (etatCourant != temp) {
    t = millis();
    etatPrecedent = temp;
  }
}

// code pour robot dans etat TOUT_DROIT
void toutDoit(void) {
  vM1 = min(vM1+PAS, MAXSPD);
  vM2 = min(vM2+PAS, MAXSPD);
}

// code pour robot dans etat virage gauche/droit
void virage(Direction direction) {
  // moteur principale = minimum moyenne entre la vit max et vit debut virage
  int v1 = max(vM1, (MAXSPD+VITVIRA)/2);
  int v2 = max(vM2, (MAXSPD+VITVIRA)/2);
  if (direction == GAUCHE) {
    v1 = VITVIRA;
  } else { // direction == DROITE
    v2 = VITVIRA;
  }
  vM1 = v1;
  vM2 = v2;
}

void loop() {
  actuInfos();
  #ifndef DEBUG
  // bool av = true;
  switch (etatCourant) {
    case TOUT_DROIT: 
      toutDoit();
      break;
    case VIRAGE_GAUCHE:
      virage(GAUCHE);
      break;
    case VIRAGE_DROIT:
      virage(DROITE);
      break;
    default:
      // av = false;
      break;
  }
  avancer(vM1, vM2, true);
  #endif
}
