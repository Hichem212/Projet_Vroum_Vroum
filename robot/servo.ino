#define PINSERV 13

Servo monServo;

#define PAS_SUR_DU_BON_FONCIONNEMENT_DU_SERVO

void initServo(void) {
  monServo.attach(PINSERV);
}

void testServo(void) {
  for (int position = 0; position <=180; position ++){ // on crée une variable position qui prend des valeurs entre 0 à 180 degrés
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(15);  // on attend 15 millisecondes
    }

    for (int position = 180; position >=0; position --){ // cette fois la variable position passe de 180 à 0°
        monServo.write(position);  // le bras du servomoteur prend la position de la variable position
        delay(15);  // le bras du servomoteur prend la position de la variable position
    }
}