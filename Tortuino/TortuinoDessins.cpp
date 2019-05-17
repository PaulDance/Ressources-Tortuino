
# include "Tortuino.h"
# include "TortuinoDessins.h"
# include <math.h>


/**
 * @file Tortuino.cpp
 * @brief Ce fichier met à disposition quelques dessins qu'il peut être intéressant d'essayer.
 * @author Paul Mabileau <paulmabileau@hotmail.fr>
 * @version 1.2
 * 
 * Le fichier TortuinoDessins.cpp implémente un ensemble de fonctions réalisant quelques dessins
 * plus ou moins complexes. Les dessins les plus simples sont par exemple des polygones réguliers
 * tels qu'un triangle, un carré, un hexagone, ... les plus compliqués utilise des motifs récursifs,
 * ce qui est moins simple à programmer, mais tout à fait agréable à contempler, comme par exemple
 * un arbre avec différentes variantes, un flocon ou encore le triangle de Sierpiński.
 */



/**
 * Fait tracer au robot un polygone régulier en fonction du nombre de côtés souhaités et de la
 * taille de chacun de ces côtés. Voir l'<a href="https://fr.wikipedia.org/wiki/Polygone_r%C3%A9gulier">
 * article Wikipédia</a> suivant pour plus de détails sur cette figure géométrique.
 * 
 * @param nbCotes    Le nombre de côtés du polygone à tracer.
 * @param tailleCote La taille de chacun des côtés.
 */
void polygoneRegulier(int nbCotes, float tailleCote) {
	for (int i = 0; i < nbCotes; i++) {
		avancer(tailleCote);
		tournerGauche(360 / nbCotes);
	}
}

/**
 * Trace un triangle equilatéral d'une certaine taille.
 * En réalité, ce n'est qu'une adaptation de polygoneRegulier(int nbCotes, float tailleCote)
 * au cas particulier du triangle equilatéral.
 * 
 * @param tailleCote La taille des côtés du triangle.
 */
void triangle(float tailleCote) {
	polygoneRegulier(3, tailleCote);
}

/**
 * Trace un carré d'une certaine taille.
 * En réalité, ce n'est qu'une adaptation de polygoneRegulier(int nbCotes, float tailleCote)
 * au cas particulier du carré.
 * 
 * @param tailleCote La taille des côtés du carré.
 */
void carre(float tailleCote) {
	polygoneRegulier(4, tailleCote);
}

/**
 * Cette fonction est une tentative de réalisation d'un cercle automatiquement avec juste
 * le rayon souhaité en entrée.
 * Seulement, cela ne fonctionne pas trop car il est difficile de décoréler les paramètres
 * du robot pour pouvoir calculer les valeurs nécessaires à une approximation relativement
 * correcte d'un cercle par un polygone régulier à un grand nombre de côtés.
 * 
 * @param rayon Le rayon du cercle.
 */
void cercle(float rayon) {				// W.I.P.
	float nbCotes = 20.0 * rayon;
	polygoneRegulier(floor(nbCotes), 2.0 * M_PI * rayon / nbCotes);
}

/**
 * Trace un arbre récursivement dont l'angle entre les branches est de 90 degrés et qui est
 * symétrique par rapport à l'axe formé par son tronc. C'est donc un cas particulier de
 * arbreSymetrique(int nbNiveaux, float tailleTronc, float angleSeparation).
 * 
 * @param nbNiveaux		Le nombre de niveaux que l'arbre comprendra, c'est-à-dire le nombre
 * 						de fois moins un que l'arbre va se séparer ou autrement dit la distance
 * 						en nombre de branches entre la racine et chaque feuille.
 * @param tailleTronc	La taille du tronc de départ. Les branches qui en partiront auront
 * 						leurs tailles d'un tier plus petites.
 */
void arbre(int nbNiveaux, float tailleTronc) {
	arbreSymetrique(nbNiveaux, tailleTronc, 90);
}

/**
 * Trace un arbre récursivement dont l'angle entre les branches peut être précisé et qui
 * est symétrique par rapport à l'axe formé par son tronc. C'est donc un cas particulier
 * de arbreAsymetrique(int nbNiveaux, float tailleTronc, float angleSeparation, float angleInclinaison).
 * 
 * @param nbNiveaux			Le nombre de niveaux que l'arbre comprendra, c'est-à-dire le nombre
 * 							de fois moins un que l'arbre va se séparer ou autrement dit la distance
 * 							en nombre de branches entre la racine et chaque feuille.
 * @param tailleTronc		La taille du tronc de départ. Les branches qui en partiront auront
 * 							leurs tailles d'un tier plus petites.
 * @param angleSeparation	L'angle séparant les branches provenant d'une même branche mère.
 * @see arbre(int nbNiveaux, float tailleTronc)
 */
void arbreSymetrique(int nbNiveaux, float tailleTronc, float angleSeparation) {
	arbreAsymetrique(nbNiveaux, tailleTronc, angleSeparation, 0);
}

/**
 * Trace un arbre récursivement dont l'angle entre les branches et l'angle entre la branche de gauche
 * et la branche mère moins 45 degrés peuvent être précisés : il est asymétrique par rapport à l'axe
 * formé par son tronc. Il généralise donc un arbre.
 * 
 * @param nbNiveaux			Le nombre de niveaux que l'arbre comprendra, c'est-à-dire le nombre
 * 							de fois moins un que l'arbre va se séparer ou autrement dit la distance
 * 							en nombre de branches entre la racine et chaque feuille.
 * @param tailleTronc		La taille du tronc de départ. Les branches qui en partiront auront
 * 							leurs tailles d'un tier plus petites.
 * @param angleSeparation	L'angle séparant les branches provenant d'une même branche mère.
 * @param angleInclinaison	L'angle entre la branche de gauche et la branche mère moins 45 degrés.
 * @see arbre(int nbNiveaux, float tailleTronc)
 * @see arbreSymetrique(int nbNiveaux, float tailleTronc, float angleSeparation)
 */
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

/**
 * Utilise deux arbres asymétriques pour tracer un sapin, c'est-à-dire un arbre où chaque branche se
 * sépare en trois autres : une continuant vers le haut (le tronc donc) et deux horizontales sur le
 * côté (les branches donc).
 * 
 * @param nbNiveaux		Le nombre de niveaux que l'arbre comprendra, c'est-à-dire le nombre
 * 						de fois moins un que l'arbre va se séparer ou autrement dit la distance
 * 						en nombre de branches entre la racine et chaque feuille.
 * @param tailleTronc	La taille du tronc de départ. Les branches qui en partiront auront
 * 						leurs tailles d'un tier plus petites.
 * @see arbre(int nbNiveaux, float tailleTronc)
 */
void sapin(int nbNiveaux, float tailleTronc) {
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, 45);
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, -45);
}

/**
 * Trace une <a href="https://fr.wikipedia.org/wiki/Flocon_de_Koch#Courbe_de_Koch">courbe de Von Koch</a>
 * paramétrée par son niveau et la taille du segment de départ.
 * 
 * @param nbNiveaux Le nombre de niveaux de la courbe de Von Koch, par convention 1 donne un trait seulement.
 * @param taille    La taille du segment à partir de laquelle l'opération récursive est itérée, c'est-à-dire
 * 					que contrairement à un arbre ou un polygone tels qu'implémentés ici, ajouter plus de
 * 					niveaux ou de côtés n'augmente pas la taille globale de la courbe ; autrement dit, le
 * 					segment de départ sert d'étalon pour en déduire à l'avance la taille des côtés engendrés.
 */
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

/**
 * Trace un <a href="https://fr.wikipedia.org/wiki/Flocon_de_Koch#Flocon_de_Koch">flocon de Von Koch</a>
 * paramétré par son niveau et la taille du segment de départ. C'est en fait une répétition de la
 * courbeVonKoch(int nbNiveaux, float taille) : trois fois séparées par un angle intérieur de 120 degrés.
 * 
 * @param nbNiveaux Le nombre de niveaux du flocon de Von Koch, par convention 1 donne un triangle seulement.
 * @param taille    La taille du segment à partir de laquelle l'opération récursive est itérée, c'est-à-dire
 * 					que contrairement à un arbre ou un polygone tels qu'implémentés ici, ajouter plus de
 * 					niveaux ou de côtés n'augmente pas la taille globale du floncon ; autrement dit, le
 * 					segment de départ sert d'étalon pour en déduire à l'avance la taille des côtés engendrés.
 */
void flocon(int nbNiveaux, float taille) {
	for (int i = 0; i < 3; i ++) {
		courbeVonKoch(nbNiveaux, taille);
		tournerGauche(60);
	}
}

/**
 * Trace un <a href="https://fr.wikipedia.org/wiki/Triangle_de_Sierpi%C5%84ski">triangle de Sierpiński</a>
 * paramétré par son niveau et la taille globale du triangle.
 * 
 * @param nbNiveaux Le nombre de niveaux du triangle de Sierpiński.
 * @param taille    La taille du segment de départ qui sera conservée au fur et à mesure des itérations
 * 					de l'algorithme de Sierpiński ; idem à ce que fait flocon(int nbNiveaux, float taille)
 */
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
