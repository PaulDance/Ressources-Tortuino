
/**
 * @file Tortuino.h
 * @brief Définition des fonctions implémentées dans Tortuino.cpp
 * @version 1.1
 * @author Paul Mabileau <paulmabileau@hotmail.fr>
 *
 * Ce fichier constitue l'en-tête de Tortuino.cpp. Il permet de préciser ce
 * qui sera rendu accessible à d'autres programmes. Ici, ce sont des fonctions.
 */


# ifndef TORTUINO_h
#	define TORTUINO_h
	
	void initialiser();
	void initialiser(float braquage);
	void initialiser(char couleur);
	void attendreBouton();
	void stopper();
	void vitesse(int v);
	void avancer(float distance);
	void reculer(float distance);
	void tournerGauche(float angle);
	void tournerDroite(float angle);
	void monterFeutre();
	void descendreFeutre();
	
# endif
