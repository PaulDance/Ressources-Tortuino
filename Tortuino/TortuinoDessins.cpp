
# include "Tortuino.h"
# include "TortuinoDessins.h"
# include <math.h>


/**
 * @file TortuinoDessins.cpp
 * @brief Ce fichier met à disposition quelques dessins qui peuvent être intéressants d'essayer.
 * @author Paul Mabileau <paulmabileau@hotmail.fr>
 * @version 1.3
 * 
 * Le fichier TortuinoDessins.cpp implémente un ensemble de fonctions réalisant quelques dessins
 * plus ou moins complexes. Les dessins les plus simples sont par exemple des polygones réguliers
 * tels qu'un triangle, un carré, un hexagone, ... les plus compliqués utilise des motifs récursifs,
 * ce qui est moins simple à programmer, mais tout à fait agréable à contempler, comme par exemple
 * un arbre avec différentes variantes, un flocon de Von Koch ou encore le triangle de Sierpiński.
 * Il présente aussi quelques défis que nous proposons pour l'animation Tortuino et qui ont été
 * réalisés avec succès par les stagiaires d'essai : une maison, une spirale carrée, un tangram et
 * un flocon. Ils se trouvent dans la section défis de ce fichier.
 */



/**
 * Fait tracer au robot un polygone régulier en fonction du nombre de côtés souhaités et de la
 * taille de chacun de ces côtés. Voir l'<a href="https://fr.wikipedia.org/wiki/Polygone_r%C3%A9gulier">
 * article Wikipédia</a> suivant pour plus de détails sur cette figure géométrique.
 * Un nombre de côtés de 3 donne un triangle, 4 un carré, 5 un pentagone régulier, ...
 * 
 * @param nbCotes    Le nombre de côtés du polygone à tracer.
 * @param tailleCote La taille de chacun des côtés.
 */
void polygoneRegulier(int nbCotes, float tailleCote) {
	for (int i = 0; i < nbCotes; i++) {									// Pour chacun des côtés,
		avancer(tailleCote);											// on avance de la taille donnée
		tournerGauche(360 / nbCotes);									// et on tourne de l'angle 360° / nbCôtés.
	}
}

/**
 * Trace un triangle equilatéral d'une certaine taille.
 * En réalité, ce n'est qu'une adaptation de polygoneRegulier(int nbCotes, float tailleCote) au
 * cas particulier du triangle equilatéral.
 * 
 * @param tailleCote La taille des côtés du triangle.
 */
void triangle(float tailleCote) {
	polygoneRegulier(3, tailleCote);									// Un triangle est un cas particulier de polygone régulier.
}

/**
 * Trace un carré d'une certaine taille.
 * En réalité, ce n'est qu'une adaptation de polygoneRegulier(int nbCotes, float tailleCote) au
 * cas particulier du carré.
 * 
 * @param tailleCote La taille des côtés du carré.
 */
void carre(float tailleCote) {
	polygoneRegulier(4, tailleCote);									// Un carré est un cas particulier de polygone régulier.
}

/**
 * Cette fonction est une tentative de réalisation d'un cercle automatiquement avec juste
 * le rayon souhaité en entrée.
 * Seulement, cela ne fonctionne pas trop car il est difficile de décorréler les paramètres
 * du robot pour pouvoir calculer les valeurs nécessaires à une approximation relativement
 * correcte d'un cercle par un polygone régulier au grand nombre de côtés. Cette fonction
 * est en cours développement, une meilleure version peut venir à être rendue disponble.
 * 
 * @param rayon Le rayon du cercle.
 */
void cercle(float rayon) {												// W.I.P.
	float nbCotes = 20.0 * rayon;										// On décide d'essayer avec 20 côtés "seulement" et on peut en déduire
	polygoneRegulier(floor(nbCotes), 2.0 * M_PI * rayon / nbCotes);		// la taille du polygone régulier approchant suffisamment le cercle souhaité
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
	arbreSymetrique(nbNiveaux, tailleTronc, 90);						// Utilisation de la généralisation de l'arbre symétrique.
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
	arbreAsymetrique(nbNiveaux, tailleTronc, angleSeparation, 0);		// Utilisation de la généralisation de l'arbre asymétrique.
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
	if (nbNiveaux == 1) {												// Si le nombre de niveaux est de 1,
		avancer(tailleTronc);											// on trace juste un trait
		monterFeutre();													// et sans laisser de trace derrière soi,
		reculer(tailleTronc);											// on revient en arrière.
	}
	else {																// Sinon,
		avancer(tailleTronc);											// on trace le tronc de l'arbre
		tournerGauche(angleInclinaison + angleSeparation / 2);			// on tourne à gauche de l'angle paramétré
		arbreAsymetrique(nbNiveaux - 1, 2 * tailleTronc / 3, angleSeparation, angleInclinaison);	// et on refait un arbre, plus petit cette fois-ci;
		tournerDroite(angleSeparation);									// Après cet arbre, on tourne pour aller vers l'autre branche,
		descendreFeutre();												// on se met en position de dessin,
		arbreAsymetrique(nbNiveaux - 1, 2 * tailleTronc / 3, angleSeparation, angleInclinaison);	// et on refait un arbre plus petit;
		tournerGauche(angleSeparation / 2 - angleInclinaison);			// enfin, on se remet dans l'axe du tronc
		reculer(tailleTronc);											// et on revient à la position de départ.
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
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, 45);					// On fait un arbre asymétrique complètement penché vers la gauche
	arbreAsymetrique(nbNiveaux, tailleTronc, 90, -45);					// et un autre vers la droite.
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
	if (nbNiveaux == 1) {												// Si le nombre de niveaux est de 1,
		avancer(taille);												// on ne fait qu'un trait sans revenir en arrière.
	}
	else {																// Sinon,
		courbeVonKoch(nbNiveaux - 1, taille / 3);						// on commence par faire une courbe de Von Koch plus petite pour le premier tiers du segment;
		tournerGauche(60);												// puis on se place pour faire la première moitié du deuxième tiers,
		courbeVonKoch(nbNiveaux - 1, taille / 3);						// et on la trace;
		tournerDroite(120);												// ensuite on se place pour faire la seconde moitié du deuxième tiers,
		courbeVonKoch(nbNiveaux - 1, taille / 3);						// et on la trace;
		tournerGauche(60);												// enfin on se place pour faire le troisième et dernier tiers,
		courbeVonKoch(nbNiveaux - 1, taille / 3);						// et on la trace.
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
 * 					niveaux ou de côtés n'augmente pas la taille globale du flocon ; autrement dit, le
 * 					segment de départ sert d'étalon pour en déduire à l'avance la taille des côtés engendrés.
 */
void floconVonKoch(int nbNiveaux, float taille) {
	for (int i = 0; i < 3; i++) {										// Un flocon de Von Koch est la répétition de trois
		courbeVonKoch(nbNiveaux, taille);								// de ses courbes
		tournerGauche(60);												// séparées par un angle externe de 60°, soit un angle interne de 120°.
	}
}

/**
 * Trace un <a href="https://fr.wikipedia.org/wiki/Triangle_de_Sierpi%C5%84ski">triangle de Sierpiński</a>
 * paramétré par son niveau et la taille globale du triangle.
 * 
 * @param nbNiveaux Le nombre de niveaux du triangle de Sierpiński.
 * @param taille    La taille du segment de départ qui sera conservée au fur et à mesure des itérations
 * 					de l'algorithme de Sierpiński ; idem à ce que fait floconVonKoch(int nbNiveaux, float taille)
 */
void triangleSierpinski(int nbNiveaux, float taille) {
	if (nbNiveaux == 1) {												// Si le nombre de niveaux est de 1,
		triangle(taille);												// on fait juste un triangle de la taille donnée.
	}
	else {																// Sinon,
		triangleSierpinski(nbNiveaux - 1, taille / 2);					// on commence par faire le triangle d'en bas à gauche,
		monterFeutre();
		avancer(taille / 2);											// puis on se place pour faire celui d'en bas à droite,
		descendreFeutre();
		triangleSierpinski(nbNiveaux - 1, taille / 2);					// et on le trace;
		monterFeutre();
		tournerGauche(120);												// ensuite on se déplace pour faire le troisième et dernier,
		avancer(taille / 2);
		tournerDroite(120);
		descendreFeutre();
		triangleSierpinski(nbNiveaux - 1, taille / 2);					// et on le trace;
		monterFeutre();
		tournerDroite(120);
		avancer(taille / 2);
		tournerGauche(120);												// enfin, on revient à la position de départ.
		descendreFeutre();
	}
}


//			-----		Section Défis		-----


/**
 * Réalise le premier défi que nous proposons pour l'animation Tortuino : une maison avec son
 * toit et sa porte d'entrée. Elle n'accepte pas de paramètres en entrée, car sa forme est fixée
 * et que mettre à disposition des moyens de personnaliser chaque partie de la maison est long
 * et en soi pas particulièrement intéressant. Le dessin est ainsi toujours le même.
 */
void maison() {
	avancer(10);														// Le toit.
	tournerDroite(120);
	avancer(10);
	tournerDroite(120);
	avancer(10);
	tournerDroite(30);
	
	avancer(10);														// La première partie du corps.
	tournerDroite(90);
	avancer(6);
	tournerDroite(90);
	
	avancer(4);															// La première partie du bas
	tournerDroite(90);													// et la porte.
	avancer(2);
	tournerDroite(90);
	avancer(4);
	tournerDroite(90);
	
	avancer(6);															// Les deuxièmes parties du bas
	tournerDroite(90);
	avancer(10);														// et du corps.
	tournerDroite(90);
}

/**
 * Trace une spirale carrée en fonction du nombre de côtés souhaités, de la longueur du côté
 * de départ et de l'écart en longueur entre deux côtés adjacents. C'est l'implémentation du
 * deuxième défi Tortuino. Une spirale carrée est une spirale composés d'un certain nombre de
 * segments reliés l'un à la suite de l'autre et séparés d'un angle de droit.
 * 
 * @param nbCotes			Le nombre de côtés de la spirale à tracer. 1 fait un seul segment.
 * @param longueurDepart	La longueur en centimètres du premier côté de la spirale.
 * @param ecart				L'écart en centimètres entre deux côtés adjacents de la spirale,
 * 							c'est-à-dire entre les côtés qui se trouvent dans la même direction
 * 							à partir du point de départ - au nord, au sud, à l'est ou à l'ouest.
 * 							Ce n'est pas directement l'écart entre la longueur du côté en cours
 * 							et son suivant, mais plutôt son quadruple.
 */
void spiraleCarree(int nbCotes, float longueurDepart, float ecart) {
	float longueurCote = longueurDepart;								// On enregistre la longueur du segment en cours
	const float diffLongueur = ecart / 4;								// et la longueur qu'il lui faut ajouter pour le suivant.
	
	for (int i = 0; i < nbCotes; i++) {									// Pour chacun des côtés,
		avancer(longueurCote);											// on le trace,
		tournerGauche(90);												// on se place pour le suivant,
		longueurCote += diffLongueur;									// et on augmente la taille du côté pour avoir l'écart souhaité.
	}
}

/**
 * Dessine le troisième défi de l'animation : un carré divisé en pièces à tangram, nom raccourci
 * en juste tangram. Le carré en question est composé de cinq triangles, un plus petit carré et
 * un parallélogramme. De même que la maison(), la geométrie est fixée et n'accepte donc pas de
 * paramètres permettant d'ajuster sa forme.
 */
void tangram() {
	for (int i = 0; i < 4; i++) {										// Le contour.
		avancer(10);
		tournerGauche(90);
	}
	
	tournerGauche(45);													// Le triangle du haut.
	avancer(7.07);
	tournerGauche(90);
	avancer(7.07);
	tournerGauche(180);
	monterFeutre();
	
	avancer(3.535);														// Les petits bouts et le petit carré.
	tournerGauche(90);
	descendreFeutre();
	avancer(3.535);
	tournerDroite(90);
	avancer(3.535);
	tournerDroite(90);
	avancer(3.535);
	tournerGauche(90);
	avancer(3.535);
	tournerGauche(135);
	
	avancer(5);															// Le parallélogramme.
	tournerDroite(135);
	avancer(3.535);
	monterFeutre();
	tournerDroite(45);
	avancer(5);
	tournerDroite(135);
	descendreFeutre();
	avancer(3.535);
}

/**
 * Réalise le quatrième défi proposé : un flocon à huit branches. Chacune des branches comporte
 * trois "feuilles" de sorte qu'elles aient leurs terminaisons alignées. Il a aussi sa forme fixée.
 */
void flocon() {
	for (int i = 0; i < 8; i++) {										// Pour chacune des huit branches,
		avancer(6.59);													// on fait le "tronc" principal,
		tournerGauche(45);
		
		avancer(2);														// la "feuille" de gauche,
		monterFeutre();
		reculer(2);
		tournerDroite(45);
		descendreFeutre();
		
		avancer(1.41);													// celle du milieu
		monterFeutre();
		reculer(1.41);
		tournerDroite(45);
		descendreFeutre();
		
		avancer(2);														// et celle de droite ;
		monterFeutre();
		reculer(2);
		tournerGauche(45);
		
		reculer(6.59);													// on se replace ensuite au centre
		tournerDroite(45);												// en tournant pour se préparer
		descendreFeutre();												// pour la suivante.
	}
}
