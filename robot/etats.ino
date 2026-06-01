#define MAXETAT 4

Etat lstEtat[MAXETAT];
int iEtat = 0;

// init les etats du robot
void initEtat(void) {
  lstEtat[0] = TOUT_DROIT;
  for (int i = 1; i < MAXETAT; i++) {
    lstEtat[i] = 0;
  }
}

// Renvoie l'etat courant du robot
Etat etatCourant(void) {
  return lstEtat[iEtat];
}

// Renvoie l'etat precedent du robot
Etat etatPrecedent(void) {
  return lstEtat[(iEtat-1)%MAXETAT]; 
}

// Renvoie le nouvel etat du robot
Etat nouvEtat(void){
  Etat e = ARRET;
  if (!sousSeuil(1)) { 
    e = TOUT_DROIT;
  } else if (sousSeuil(0) && sousSeuil(1) && sousSeuil(2)) {
    e = SANS_LIGNE;
  } else if (!sousSeuil(0)) { // si le capteur droit detecte la ligne
    e = VIRAGE_DROIT;
  } else if (!sousSeuil(2)) { // si le capteur gauche detecte la ligne
    e = VIRAGE_GAUCHE;
  }
  return e;
}

// actualise l'etat du robot
void actuEtat(void) {
  Etat temp = nouvEtat();

  if (etatCourant() != temp) {
    iEtat = (iEtat+1)%MAXETAT;
    lstEtat[iEtat] = temp;
    if (etatCourant() == SANS_LIGNE) {
      t_perdu = millis();
      t_retrouve = 0;
    } else {
      t_retrouve = millis();
      t_perdu = 0;
    }
  }
}

Direction dernierVirage(void) {
  int i = 0;
  while (i < MAXETAT && lstEtat[(iEtat-i)%MAXETAT] != VIRAGE_DROIT && lstEtat[(iEtat-i)%MAXETAT] != VIRAGE_GAUCHE) {
    i++;
  }
  if (lstEtat[(iEtat-i)%MAXETAT] == VIRAGE_DROIT) {
    return DROITE;
  } 
  return GAUCHE;
}

// =======================================
//        DEBUG
// =======================================

void afficherEtat(void) {
  Serial.print(iEtat);
  Serial.print(" | ");
  Serial.print(etatCourant());
  Serial.print(" | ");
  Serial.print(etatPrecedent());
  Serial.print(" |          ");
  for (int i = 0; i < MAXETAT; i++) {
    Serial.print(" | ");
    Serial.print(lstEtat[i]);
  } 
  Serial.println("");
}
