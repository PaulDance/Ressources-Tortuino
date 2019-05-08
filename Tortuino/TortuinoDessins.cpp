
# include "Tortuino.h"
# include "TortuinoDessins.h"
# include <math.h>


void polygoneRegulier(int nbCotes, float tailleCote) {
	for (int i = 0; i < nbCotes; i++) {
		avancer(tailleCote);
		tournerGauche(360 / nbCotes);
	}
}

void triangle(float tailleCote) {
	polygoneRegulier(3, tailleCote);
}

void carre(float tailleCote) {
	polygoneRegulier(4, tailleCote);
}

void cercle(float rayon) {				// W.I.P.
	float nbCotes = 20.0 * rayon;
	polygoneRegulier(floor(nbCotes), 2.0 * M_PI * rayon / nbCotes);
}

void arbre(int nbNiveaux, float tailleTronc) {
	arbreSymetrique(nbNiveaux, tailleTronc, 90);
}

void arbreSymetrique(int nbNiveaux, float tailleTronc, float angleSeparation) {
	arbreAsymetrique(nbNiveaux, tailleTronc, angleSeparation, 0);
}

void arbreAsymetrique(int nbNiveaux, float tailleTronc, float angleSeparation, float angleInclinaison) {
	if (nbNiveaux == 1) {
		avancer(tailleTronc);
		monterFeutre();
		reculer(tailleTronc);
	}
	else {
		avancer(tailleTronc);
		tournerGauche(angleInclinaison + angleSeparation / 2);
		arbreAsymetrique(nbNiveaux - 1, 2 * tailleTronc / 3, angleSeparation, angleInclinaison);
		tournerDroite(angleSeparation);
		descendreFeutre();
		arbreAsymetrique(nbNiveaux - 1, 2 * tailleTronc / 3, angleSeparation, angleInclinaison);
		tournerGauche(angleSeparation / 2 - angleInclinaison);
		reculer(tailleTronc);
	}
}

void sapin(int nbNiveaux, float tailleTronc) {
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, 45);
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, -45);
}

void courbeVonKoch(int nbNiveaux, float taille) {
	if (nbNiveaux == 1) {
		avancer(taille);
	}
	else {
		courbeVonKoch(nbNiveaux - 1, taille / 3);
		tournerGauche(60);
		courbeVonKoch(nbNiveaux - 1, taille / 3);
		tournerDroite(120);
		courbeVonKoch(nbNiveaux - 1, taille / 3);
		tournerGauche(60);
		courbeVonKoch(nbNiveaux - 1, taille / 3);
	}
}

void flocon(int nbNiveaux, float taille) {
	for (int i = 0; i < 3; i ++) {
		courbeVonKoch(nbNiveaux, taille);
		tournerGauche(60);
	}
}

void triangleSierpinski(int nbNiveaux, float taille) {
	if (nbNiveaux == 1) {
		triangle(taille);
	}
	else {
		triangleSierpinski(nbNiveaux - 1, taille / 2);
		monterFeutre();
		avancer(taille / 2);
		descendreFeutre();
		triangleSierpinski(nbNiveaux - 1, taille / 2);
		monterFeutre();
		tournerGauche(120);
		avancer(taille / 2);
		tournerDroite(120);
		descendreFeutre();
		triangleSierpinski(nbNiveaux - 1, taille / 2);
		monterFeutre();
		tournerDroite(120);
		avancer(taille / 2);
		tournerGauche(120);
		descendreFeutre();
	}
}