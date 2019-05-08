#include <Tortuino.h>
#include <TortuinoDessins.h>

/**
 * Test des fonctions de base de la bibliothèque Tortuino.
 */


void setup() {
  int attente = 500;
  
  initialiser("v");
  vitesse(10);

  monterFeutre();// Test du feutre tout seul.
  descendreFeutre();
  delay(attente);
  
  avancer(5);         // Test des roues : avant-arrière.
  reculer(5);
  delay(attente);
  
  tournerGauche(60);  // Test des roues : gauche-droite.
  tournerDroite(60);
  delay(attente);//même avec montée et descente du feutre
  
  descendreFeutre();  // Test pointillés.
  avancer(2);
  monterFeutre();
  avancer(2);
  descendreFeutre();
  avancer(2);
  delay(attente);

  monterFeutre();     // Vérification de la continuité d'un trait,
  avancer(1);         // même avec montée et descente du feutre.
  descendreFeutre();
  avancer(2);
  monterFeutre();
  descendreFeutre();
  avancer(2);
  delay(attente);
  
  carre(10);        // Test complet : un arbre à 3 niveaux.
  
}

void loop() {
  delay(1000);
}
