#include <Tortuino.h>
#include <TortuinoDessins.h>

/**
 * Test des fonctions de base de la bibliothèque Tortuino.
 */


void setup() {
  initialiser();
  vitesse(10);
  
  avancer(5);
  reculer(5);
  tournerGauche(30);
  tournerDroite(30);

  delay(1000);
  arbre(3, 5);
}

void loop() {
  delay(1000);
}
