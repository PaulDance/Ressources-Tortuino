
/**
 * @file TortuinoDessins.h
 * @brief Définition des fonctions implémentées dans TortuinoDessins.cpp
 * @version 1.1
 * @author Paul Mabileau <paulmabileau@hotmail.fr>
 *
 * Ce fichier constitue l'en-tête de TortuinoDessins.cpp. Il permet de préciser ce
 * qui sera rendu accessible à d'autres programmes. Ici, ce sont des fonctions.
 */


# ifndef TORTUINO_DESSINS_h
#	define TORTUINO_DESSINS_h
	
	void triangle(float tailleCote);
	void carre(float tailleCote);
	void polygoneRegulier(int nbCotes, float tailleCote);
	void cercle(float rayon);
	
	void arbre(int nbNiveaux, float tailleTronc);
	void arbreSymetrique(int nbNiveaux, float tailleTronc, float angleSeparation);
	void arbreAsymetrique(int nbNiveaux, float tailleTronc, float angleSeparation, float angleInclinaison);
	void sapin(int nbNiveaux, float tailleTronc);
	
	void courbeVonKoch(int nbNiveaux, float taille);
	void floconVonKoch(int nbNiveaux, float taille);
	
	void triangleSierpinski(int nbNiveaux, float taille);
	
# endif
