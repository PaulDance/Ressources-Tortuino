
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
	void flocon(int nbNiveaux, float taille);
	
	void triangleSierpinski(int nbNiveaux, float taille);
	
# endif