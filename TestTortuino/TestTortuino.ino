#include <Tortuino.h>
#include <TortuinoDessins.h>

/**
 * Test des fonctions de base de la bibliothèque Tortuino.
 */


void setup() {
  int attente = 500;
  
  initialiser(11.3f);
  delay(500);
  arbre(3,10);
  tournerGauche(180);
}

void loop() {
  delay(1000);
}
