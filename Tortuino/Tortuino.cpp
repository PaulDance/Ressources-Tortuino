
# include <SD.h>
# include <SPI.h>
# include <Tortuino.h>
# include <Stepper.h>
# include <Servo.h>
# include <math.h>


/**
 * @file Tortuino.cpp
 * @brief Ce fichier décrit les instructions de base pour contrôler le robot.
 * @author Alexandre Comte
 * @author Paul Mabileau <paulmabileau@hotmail.fr>
 * @author Florian Bescher
 * @version 1.2
 * 
 * Le fichier Tortuino.cpp rassemble les fonctionnalités essentielles au bon fonctionnement
 * de la communication avec un robot Tortuino. Ces fonctionnalités sont principalement
 * réalisées et mises à disposition au travers de fonctions qui les implémentent. Il y a
 * aussi des paramètres en début de fichiers qui peuvent être modifiés à souhait pour adapter
 * au mieux les programmes au robot qui sera manipulé au final : ils se révèlent particulièrement
 * utiles pour le calibrer. Voir la section **Variables** pour plus de détails.<br/>
 *
 * Pour comprendre comment peut s'utiliser cette bibliothèque de manière plus pratique, le fichier
 * de test <span style="text-decoration: underline;">TestTortuino.ino</span> résume assez bien
 * l'ensemble des choses réalisables grâce à elle. Pour expliquer avec un autre exemple, les
 * instructions suivantes permettent de faire dessiner au robot un carré de côté 10cm :
 * 
 * {@code
 * 	void setup() {						// setup() n'est exécutée qu'une seule fois.
 * 		initialiser();					// Règle l'Arduino sur les bons ports de communication.
 * 		
 * 		for (int i = 0; i < 4; i++) {	// Pour chacun des côtés,
 * 			avancer(10);				// on avance de 10cm,
 * 			tournerGauche(90);			// et on tourne vers la gauche de 90°.
 * 		}
 * 	}
 * 	
 * 	void loop() {						// loop() est exécutée en boucle, après setup().
 * 										// Aucune instruction de plus à ajouter ici.
 * 	}
 * }
 *
 * Notez bien que dans ce code source, les fonctions ainsi déclarées `setup()` et `loop()` sont spécifiques
 * à l'Arduino, le tout se doit d'être utilisé avec l'éditeur Arduino IDE fourni par le constructeur.
 * Consultez la <a href="https://www.arduino.cc/reference/en/">documentation Arduino</a> pour plus de
 * détails à ce sujet et en particulier la référence précise de l'utilisation des fonctions
 * <a href="https://www.arduino.cc/reference/en/language/structure/sketch/setup/">`setup()`</a> et
 * <a href="https://www.arduino.cc/reference/en/language/structure/sketch/loop/">`loop()`</a>.<br/>
 *
 * La présente bibliothèque fourni aussi une fonction stopper() qui une fois appelée bloquera l'exécution
 * de tout programme. Cela permet alors de réaliser le programme précédent de manière équivalente, mais
 * en séparant cette fois-ci l'initialisation de l'exécution :
 * 
 * {@code
 * 	void setup() {						// setup() n'est exécutée qu'une seule fois.
 * 		initialiser();					// Règle l'Arduino sur les bons ports de communication.
 * 	}
 * 	
 * 	void loop() {						// loop() est exécutée en boucle, après setup().
 * 		for (int i = 0; i < 4; i++) {	// Pour chacun des côtés,
 * 			avancer(10);				// on avance de 10cm,
 * 			tournerGauche(90);			// et on tourne vers la gauche de 90°.
 * 		}
 *
 * 		stopper();						// Enfin, on empêche l'Arduino de boucler à l'infini.
 * 	}
 * }
 *
 * Les deux programmes n'ont, au fond, aucune différence : le robot tracera le même carré. Ceci peut
 * être intéressant pour améliorer la compréhension de la syntaxe Arduino, car `setup()` ne gardera ainsi
 * que ce qui est effectivement lié à l'initialisation du robot, tandis que `loop()` se chargera du principal du
 * programme. Cependant, l'instruction stopper() présente ci-dessus à la fin de `loop()` est très importante
 * car sinon, le robot exécutera en boucle les instructions de `loop()` et le dessin qu'elles décrivent sera
 * tracé indéfiniment. Un choix pédagogique est donc à faire ici.<br/>
 *
 * De plus, la bibliothèque fourni une fonctionnalité supplémentaire : un moyen pour le robot de contrôler
 * son servomoteur pour faire monter ou descendre son feutre. On peut donc par exemple reprendre le
 * programme précédant et le modifier un peu pour tracer un carré en pointillés de la sorte :
 *
 * {@code
 * 	void setup() {						// setup() n'est exécutée qu'une seule fois.
 * 		initialiser();					// Règle l'Arduino sur les bons ports de communication.
 * 	}
 * 	
 * 	void loop() {						// loop() est exécutée en boucle, après setup().
 * 		for (int i = 0; i < 4; i++) {	// Pour chacun des côtés,
 * 			descendreFeutre();			// on met le feutre en position basse,
 * 			avancer(3.33);				// on avance du premier tiers du côté en cours : trait tracé,
 * 			monterFeutre();				// on monte le feutre,
 * 			avancer(3.33);				// on avance du deuxième tiers du côté en cours : trait non tracé,
 * 			descendreFeutre();			// on fait descendre le feutre,
 * 			avancer(3.33);				// on avance du dernier tiers : trait tracé,
 * 			tournerGauche(90);			// et on tourne à gauche pour le côté suivant.
 * 		}
 *
 * 		stopper();						// Enfin, on empêche l'Arduino de boucler à l'infini.
 * 	}
 * }
 *
 * Remarquez bien qu'ici les appels à la fonction avancer() sont réalisés avec un argument effectivement
 * de type flottant (`float`), alors que précédemment, seulement fournir un entier (`int`) était suffisant.
 * En réalité, il y avait déjà avant une conversion des entiers fournis en nombre décimaux pour que l'appel
 * se réalise correctement.
 *
 * @see initialiser()
 * @see avancer(float distance)
 * @see tournerGauche(float angle)
 * @see monterFeutre()
 */



const int stepsPerRevolution	=	64 * 64 / 2;	/**< Le nombre de pas par tour que réalise un moteur pas à pas ; c'est une donnée constructeur. */
	  float	PERIMETER	=	M_PI * 9.2,				/**< Le périmètre des roues du robot tel que mesuré avec le pneu. */
			BRAQUAGE	=	11.3 / 2;				/**< Le rayon de braquage du robot. C'est une valeur qui peut être amenée à être calibrée. */

const int	FEUTRE_HAUT	=	50,						/**< L'angle de la position haute du servomoteur. Il a été ajusté empiriquement. */
			FEUTRE_BAS	=	10;						/**< L'angle de la position basse du servomoteur. Il a été ajusté empiriquement. */

const int	portBouton	=	7,						/**< Le numéro de la broche qui sert de port pour le bouton permettant le démarrage différé : 7. */
			portServo	=	9;						/**< Le numéro de la broche pour le port du servomoteur : 9. */

const int	delaiEntreBouton	=	10;				/**< Le délai en ms entre chaque test du bouton. Sa petite valeur importe peu, mais le délai reste utile. */
const int	delaiApresBouton	=	500;			/**< Le délai en ms effectué après que le bouton ait été pressé. Il permet d'éviter que l'utilisateur
														se coince le doigt dans le câblage du robot au démarrage de l'exécution du programme de celui-ci. */

const int 	delaiMonterDescendre	=	200;		/**< Le délai en ms d'attente après l'envoi d'une commande au feutre. Paramétré empiriquement. */

Stepper stepperLeft = Stepper(stepsPerRevolution, 10, 12, 11, 13);	/**< L'objet qui sert à contrôler le moteur pas à pas de gauche et qui est relié aux ports 10 à 13. */
Stepper stepperRight = Stepper(stepsPerRevolution, 2, 4, 3, 5);		/**< L'objet qui sert à contrôler le moteur pas à pas de droite et qui est relié aux ports 2 à 5. */

Servo servo;										/**< L'objet qui sert à contrôler le servomoteur soulevant et abaissant le feutre du robot. */


/**
 * Réalise la conversion d'une distance que le robot peut parcourir en un certain nombre de pas que
 * chacun des deux moteurs pas à pas doit effectuer pour que le robot puisse avancer de la distance
 * donnée. Cette conversion prend en compte les paramètres décrivant la géométrie du robot.
 * 
 * @param  distance La distance linéaire en centimètres correspondant à un déplacement.
 * @return          Le nombre de pas permettant de réaliser le déplacement de la distance donnée.
 */
int distanceToStep(float distance) {
	return (int)(distance / PERIMETER * stepsPerRevolution);
}

/**
 * Initialise la configuration du robot pour qu'il puisse correctement communiquer avec ses différents
 * composants qui le constituent : le servomoteur, les moteurs pas à pas et le bouton de démarrage différé.
 * Au cours de cette configuration, elle met le robot dans un état standard qui sera ainsi toujours le
 * même au début de l'exécution de chaque essai : la vitesse de rotation des moteurs pas à pas est par
 * défaut de 10 et le feutre est en position basse. Cette fonction à sa fin fait appel à attendreBouton()
 * qui bloquera tant que le bouton de démarrage différé n'est pas appuyé.<br/>
 * L'initialisation est une étape absolument nécessaire au bon fonctionnement du robot ; sans cela, la
 * carte Arduino que contrôle ces fonctions n'est pas en mesure de connaître les différents composants
 * du robot, ni sur quels ports ils se trouvent et ni comment les utiliser. Les fonctions initialiser(char couleur)
 * et initialiser(float braquage) ajoute à la présente fonction quelques détails en plus, mais finissent
 * toujours par l'appeler. Il n'y a donc pas besoin d'appeler par exemple initialiser(float braquage) si
 * cela se révèle utile pour vous et juste ensuite initialiser(), car cela sera redondant et même plutôt
 * contre-productif. Un seul appel est suffisant.
 */
void initialiser() {
	servo.attach(portServo);											// Affectation du port pour le servomoteur.
	pinMode(portBouton, INPUT_PULLUP);									// Mode de la broche pour le bouton : entrée.
	vitesse(10);														// Vitesse de rotation des moteurs pas à pas : 10.
	descendreFeutre();													// Feutre en position basse.
	attendreBouton();													// Attente du bouton de démarrage différé.
}

/**
 * Cette version de l'opération d'initialisation met en place une méthode pour calibrer chaque robot
 * à souhait pour que les erreurs systématiques au moment de la rotation puissent être compensées.
 * Le choix qui a été fait ici est de donner à chaque robot une couleur (par exemple de la plaquette
 * d'expérimentation électrique) représentée par la première lettre de son écriture et qui l'identifie
 * de manière unique. Ensuite, grâce à une correspondance établie au préalable, la valeur du rayon
 * de braquage est affectée par cette fonction, retrouvant ainsi le calibrage effectué. Voir le code
 * source pour bien comprendre comment ces associations sont réalisées.<br/>
 * Le reste de l'initialisation est bien entendu aussi réalisé.
 * 
 * @param couleur La première lettre de la couleur identifiant le robot utilisé.
 * @see initialiser()
 * @see initialiser(float braquage)
 */
void initialiser(char couleur) {
	if (couleur == 'w') {												// On teste simplement quelle valeur a la couleur
		BRAQUAGE = 11.3 / 2;
	}
	else if (couleur == 'j') {											// parmi un ensemble donné qui permet surtout de récupérer
		BRAQUAGE = 11.3 / 2;											// son association à un rayon de braquage donné.
	}
	else if (couleur == 'b') {
		BRAQUAGE = 11 / 2;
	}
	else if (couleur == 'v') {
		BRAQUAGE = 10.5 / 2;
	}
	else if (couleur == 'r') {
		BRAQUAGE = 11.3 / 2;
	}
	else if (couleur == 'n') {
		BRAQUAGE = 11.3 / 2;
	}
	initialiser();														// Quel que soit l'entrée, on fait toujours la partie principale de l'initialisation.
}

/**
 * Cette version de l'opération d'initialisation est utile à la calibration d'un robot car
 * affecte directement au rayon de braquage la moitié de la valeur fournie en entrée. Le
 * reste de l'initialisation est bien entendu aussi réalisé.<br/>
 * Notez bien qu'un paramètre de type `float` est attendu en entrée. Or, d'autres fonctions
 * existent mais ont des signatures différentes. En particulier, initialiser(char couleur)
 * attend un caractère, ce qui revient à un nombre entier. Ainsi, si vous fournissez un
 * nombre entier à la présente fonction, par exemple avec `initialiser(10);`, le compilateur
 * C++ terminera sur une erreur car il y a précisément une ambiguïté entre initialiser(char
 * couleur) et initialiser(float braquage). En effet, ce n'est pas au compilateur d'effectuer
 * le choix implicite entre ces deux fonctions. Pour tout de même parvenir à ce que l'on
 * souhaite dans cet exemple, il est possible de forcer le nombre entier `10` à être converti
 * en `float` grâce à un `f` à la fin. Cela donne donc : `avancer(10f);`, et dans ce cas là,
 * cela fonctionnera comme souhaité car cela appelera effectivement initialiser(float braquage).
 * Si maintenant vous souhaitez appeler `initialiser(11.3);`, pour la même raison, il faut en
 * fait faire `initialiser(11.3f);`.
 * 
 * @param braquage La valeur du diamètre de braquage à utiliser.
 * @see initialiser()
 * @see initialiser(char couleur)
 */
void initialiser(float braquage) {
	BRAQUAGE = braquage / 2;											// On transforme le diamètre fourni en le rayon à utiliser.
	initialiser();														// On continue avec la partie principale de l'initialisation.
}

/**
 * Réalise l'attente nécessaire à la fonctionnalité du démarrage différé. L'exécution de cette
 * fonction bloquera tant que le bouton en question n'a pas été appuyé. Cette fonction est
 * toujours appelée par initialiser(), car cela permet d'éviter que l'utilisateur du robot
 * ne soit surpris par son démarrage alors que le câble de programmation est encore branché
 * et que le robot n'est pas en place. Une petite attente après l'appui du bouton est aussi
 * effectué pour ne pas que l'utilisateur ne trouve son doigt coincé dans les câblages après
 * le départ du robot.
 */
void attendreBouton() {
	int oldState, newState = digitalRead(portBouton);					// On initialise newState à l'état actuel de la broche du bouton.

	while (true) {
		oldState = newState;											// On sauvegarde l'état précedant dans oldState,
		newState = digitalRead(portBouton);								// et on met à jour l'actuel dans newState.

		if (oldState == LOW && newState == HIGH) {						// Si les deux correspondent à un front descendant,
			delay(delaiApresBouton);									// on attend un peu plus, pour ne pas surprendre
			return;														// et on met fin à l'attente;
		}

		delay(delaiEntreBouton);										// sinon, on attend un petit peu et on teste à nouveau;
	}
}

/**
 * Permet de mettre à l'arrêt l'exécution en cours que réalise l'Arduino. Cette fonction peut se
 * révéler utile si le croquis Arduino utilise la fonction loop() mais souhaite à un moment donné
 * stopper le robot. Cette instruction ne rend pas la main à toute exécution qui la suit, elle est
 * donc plutôt à utiliser en dernière, à la toute fin de loop() si c'est bien ce qui est souhaité.
 * Si par contre une simple pause est voulue, plusieurs options sont possibles, comme par exemple
 * utiliser <a href="https://www.arduino.cc/reference/en/language/functions/time/delay/">delay()</a>
 * pour attendre d'une durée donnée, puis continuer le flot d'exécution ; ou aussi attendreBouton()
 * qui attend indéfiniment l'appui du bouton du robot et après rend la main.
 */
void stopper(){
	while (true){														// Tout le temps
		delay(delaiEntreBouton);										// on attend un petit peu.
	}
}

/**
 * Règle la vitesse de rotation des moteurs pas à pas. Une valeur de 10 est largement suffisante.
 * Cette fonction n'est actuellement pas considérée comme intéressante à utilser en dehors du
 * fonctionnement interne de cette bibliothèque. Elle est pour l'instant seulement appelée par
 * initialiser() qui s'occupe de régler le robot pour avoir une vitesse par défaut qui fonctionne
 * tout à fait correctement pour le robot ainsi paramétré.
 * 
 * @param v La valeur entière de la vitesse à affecter aux moteurs pas à pas.
 */
void vitesse(int v) {
	stepperRight.setSpeed(v);											// Les moteurs pas à pas gauche
	stepperLeft.setSpeed(v);											// et droite prennent la même valeur de vitesse donnée.
}

/**
 * Fait avancer le robot Tortuino d'une distance donnée.
 * @param distance La distance en centimètres à parcourir.
 * @see reculer(float distance)
 */
void avancer(float distance) {
	int steps = distanceToStep(fabs(distance));							// On convertit la distance en nombre de pas à faire;
	int sens = 1;														// et on met le sens par défaut vers l'avant.
	if (distance < 0) {													// Si la distance est négative,
		sens = -1;														// on met le sens vers l'arrière.
	}

	for (int i = 0; i < steps; i++) {									// On fait tous les pas à réaliser un par un :
		stepperRight.step(sens);										// la roue gauche d'abord,
		stepperLeft.step(-sens);										// la droite ensuite.
	}
}

/**
 * Fait reculer le robot Tortuino d'une distance donnée.
 * @param distance La distance en centimètres à parcourir.
 * @see avancer(float distance)
 */
void reculer(float distance) {
	avancer(-distance);													// On réutilise la généralisation faite dans avancer().
}

/**
 * Fait tourner sur place le robot Tortuino d'un angle fourni vers sa gauche. La rotation
 * s'effectue autour de l'axe que décrit le feutre positionné dans l'emplacement prévu à cet
 * effet, de sorte que s'il reste baissé lors de l'opération, cela ne laisse pas de cercle
 * de tracé derrière le robot. Il peut cependant avoir un petit décalage qui soit tout de
 * même présent après rotation car en réalité le feutre n'est pas parfaitement stable : un
 * petit jeu existe entre le feutre et son guide. L'effet de ce jeu n'est pas pour autant
 * terrible et cela ne se verra pas trop.
 * 
 * @param angle L'angle en degrés de rotation vers la gauche à effectuer.
 * @see tournerDroite(float angle)
 */
void tournerGauche(float angle) {
	int steps = distanceToStep(M_PI / 180 * fabs(angle) * BRAQUAGE);	// On récupère le nombre de pas correspondant à la longueur de l'arc décrit par l'angle donné
	int sens = 1;														// et on met le sens par défaut vers la gauche.
	if (angle < 0) {													// Si l'angle est négatif,
		sens = -1;														// on met le sens vers la droite.
	}

	for (int i = 0; i < steps; i++) {									// On fait tous les pas à réaliser un par un :
		stepperRight.step(sens);										// la roue droite d'abord,
		stepperLeft.step(sens);											// la gauche ensuite.
	}
}

/**
 * Fait tourner sur place le robot Tortuino d'un angle fourni vers sa droite. La rotation
 * s'effectue autour de l'axe de décrit le feutre positionné dans l'emplacement prévu à cet
 * effet, de sorte que s'il reste baisser lors de l'opération, cela ne laisse pas de cercle
 * de tracé derrière le robot. Il peut cependant avoir un petit décalage qui soit tout de
 * même présent après rotation car en réalité le feutre n'est pas parfaitement stable : un
 * petit jeu existe entre le feutre et son guide. L'effet de ce jeu n'est pas pour autant
 * terrible et cela ne se verra pas trop.
 * 
 * @param angle L'angle en degrés de rotation vers la gauche à effectuer.
 * @see tournerGauche(float angle)
 */
void tournerDroite(float angle) {
	tournerGauche(-angle);												// On réutilise la généralisation faite dans tournerGauche().
}

/**
 * Place le feutre en position haute de telle manière qu'il ne touche pas la feuille en-dessous
 * du robot, en supposant que le collier le tenant et permettant ce déplacement soit correctement
 * ajusté. Cela permet de choisir quand est-ce que l'on souhaite dessiner ou non, car à certains
 * moments, par exemple si l'on veut se replacer pour continuer une autre partie d'un dessin, cela
 * se révèle assez utile.
 *
 * @see descendreFeutre()
 */
void monterFeutre() {
	servo.write(FEUTRE_HAUT);											// Mise à la position haute du feutre.
	delay(delaiMonterDescendre);										// Petit délai pour attendre que le mouvement du servomoteur se termine à coup sûr.
}

/**
 * Place le feutre en position basse de telle manière qu'il touche la feuille en-dessous du
 * robot, en supposant que le collier le tenant et permettant ce déplacement soit correctement
 * ajusté.
 *
 * @see monterFeutre()
 */
void descendreFeutre() {
	servo.write(FEUTRE_BAS);											// Mise à la position basse du feutre.
	delay(delaiMonterDescendre);										// Petit délai pour attendre que le mouvement du servomoteur se termine à coup sûr.
}
