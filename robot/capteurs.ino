#define IR1 11
#define IR2 12
#define IR3 13

#define NBCAP 3
#define MAXITE 1000

int IRs[NBCAP] = {IR1, IR2, IR3};
int seuil[NBCAP] = {200, 220, 200};
int valeurs[NBCAP];

// renvoie le contraste trouve par le capteur iIR
int contraste(int iIR) {
  int ir = IRs[iIR];
  pinMode(ir, OUTPUT);
  digitalWrite(ir, HIGH);
  delayMicroseconds(10);
  pinMode(ir, INPUT);
  digitalWrite(ir, LOW);
  long t_in = micros();
  int ite = 0;
  while (digitalRead(ir) == HIGH && ite < MAXITE){
    ite++;
  }
  long t_out = micros();

  return t_out - t_in;
}

// trouve le contraste pour tout les capteurs
void rampeContraste(void){
  for (int iIR = 0; iIR < NBCAP; iIR++) {
    valeurs[iIR] = contraste(iIR);    
  }
}

// indique si le contraste du capteur iIr est sous le seuil, cad si le capteur n'est pas sur la ligne
bool sousSeuil(int iIR){
  return valeurs[iIR] < seuil[iIR];
}

// Renvoie le nouvel etat du robot (lit automatiquement les contrastes)
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

// calcul l'ecart du robot par rapport a la ligne dans l'interval [-100; 100],
// (lit automatiquement les contrastes),
// < 0 -> trop a gauche
// > 0 -> trop a droite
int ecartLigne(void) {
  return 100L*(valeurs[2]-valeurs[0])/(valeurs[2]+valeurs[0]);
}

// =======================================
//        DEBUG
// =======================================

void afficherEtat(void) {
  Serial.print("Etat precedent : ");
  Serial.print(etatPrecedent);
  Serial.print(" | Etat courant : ");
  Serial.print(etatCourant);

  Serial.println("");
}

// affiche les valeurs des capteurs
void affichageCapteur(void) {
  for (int i = 0; i < NBCAP; i++) {
    Serial.print("| IR ");
    Serial.print(i);
    Serial.print(" (");
    Serial.print(seuil[i]);
    Serial.print("): ");
    Serial.print(valeurs[i]);  
  } 
  Serial.println("");
}

// fonction de tests pour les capteurs
void testIR(void) {
  delay(1000);
  rampeContraste();
  affichageCapteur();
  for (int i = 0; i < 3; i++) {
    if (sousSeuil(i)) {
      Serial.print(i+1);
      Serial.println(" -> sous seuil");
    }
  }
}
