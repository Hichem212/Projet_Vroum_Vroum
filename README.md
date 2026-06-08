# Projet Vroum Vroum

Code source d'un robot suiveur de ligne, avec une 3 capteurs IR Pololu et 2 moteurs a courant continue

Site du projet : https://secil.univ-tlse3.fr/ontheroadagain/

# Fonctionnement :
3 modes de deplacements,
* **Mode chenille** : s'inspire du systeme de rotation des vehicules lent comme les tanks pour tourner. Le robot est donc lent mais robuste dans les differents circuits.
* **Systeme PID** : en cours de developpement, systeme auto equilibrant, rapide mais complexe.
* **Systeme conmbiné** : combine le système PID et chenille avec systeme pour retrouver la ligne "intelligent". C'est le mode utilise pour le robot durant la course finale

# Systeme de sauvetage :
Un algorithme pour retrouver la ligne est implementer mais pas utilise, la valeur utilisee normalement est de 400ms
* des qu'il n'est pas dans un cas pour tourner et qu'il n'arrive pas a detecter la ligne, alors il avance un moment avant de se considerer comme perdu
* des qu'il est perdu, il recul jusqu'a trouver la ligne, puis soit il recuprere le dernier virage lu, sinon il tourne la ou le contraste est le plus haut

# A faire :
* optimiser l'algo du PID
* modifier la roue libre pour avoir un servo moteur ou une ball caster
* ajouter des capteurs pour agrandir le champ de vision
