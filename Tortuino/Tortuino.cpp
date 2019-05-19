
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
 * aussi des paramètres en début de fichiers qui peuvent être modifiés à souhait pour
 * adapter au mieux les programmes au robot qui sera manipulé au final : le calibrer.
 */



const int stepsPerRevolution	=	64 * 64 / 2;	/**< Le nombre de pas par tour que réalise un moteur pas à pas ; c'est une donnée constructeur. */
	  float	PERIMETER	=	M_PI * 9.2,				/**< Le périmètre des roues du robot tel que mesuré avec le pneu. */
			BRAQUAGE	=	11.3 / 2;				/**< Le rayon de braquage du robot. C'est une valeur qui peut être amenée à être calibrée. */

const int	FEUTRE_HAUT	=	50,						/**< L'angle de la position haute du servomoteur. Il a été ajusté empiriquement. */
			FEUTRE_BAS	=	10;						/**< L'angle de la position basse du servomoteur. Il a été ajusté empiriquement. */

const int	portBouton	=	7,						/**< Le numéro de la broche qui sert de port pour le bouton permettant le démarrage différé : 7. */
			portServo	=	9;						/**< Le numéro de la broche pour le port du servomoteur : 9. */

const int	delaiBouton	=	10;						/**< Le délai en ms entre chaque test du bouton. */

const int 	delaiMonterDescendre	=	200;		/**< Le délai en ms d'attente après l'envoi d'une commande au feutre. Paramétré empiriquement. */

Stepper stepperLeft;								/**< L'objet qui sert à contrôler le moteur pas à pas de gauche et qui est relié aux ports 10 à 13. */
Stepper stepperRight;								/**< L'objet qui sert à contrôler le moteur pas à pas de droite et qui est relié aux ports 2 à 5. */

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
 * qui bloquera tant que le bouton de démarrage différé n'est pas appuyé.
 */
void initialiser() {
	stepperLeft = Stepper(stepsPerRevolution, 10, 12, 11, 13);			// Affectation des ports pour le moteur pas à pas gauche
	stepperRight = Stepper(stepsPerRevolution, 2, 4, 3, 5);				// et droit.
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
 * de braquage est affectée par cette fonction, retrouvant ainsi le calibrage effectué. <br/>
 * Le reste de l'initialisation est bien entendu aussi réalisé.
 * 
 * @param couleur La première lettre de la couleur identifiant le robot utilisé.
 * @see initialiser()
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
 * affecte directement au rayon de braquage la moitié de la valeur fournie en entrée.
 * Le reste de l'initialisation est bien entendu aussi réalisé.
 * 
 * @param braquage La valeur du diamètre de braquage à utiliser.
 */
void initialiser(float braquage) {
	BRAQUAGE = braquage / 2;											// On transforme le diamètre fourni en le rayon à utiliser.
	initialiser();														// On continue avec la partie principale de l'initialisation.
}

/**
 * Réalise l'attente nécessaire à la fonctionnalité du démarrage différé. L'exécution de cette
 * fonction bloquera tant que le bouton en question n'a pas été appuyé.
 */
void attendreBouton() {
	int oldState, newState = digitalRead(portBouton);					// On initialise newState à l'état actuel de la broche du bouton.

	while (true) {
		oldState = newState;											// On sauvegarde l'état précedant dans oldState,
		newState = digitalRead(portBouton);								// et on met à jour l'actuel dans newState.

		if (oldState == LOW && newState == HIGH) {						// Si les deux correspondent à un front descendant,
			return;														// on met fin à l'attente;
		}

		delay(delaiBouton);												// sinon, on attend un petit peut et on teste à nouveau.
	}
}

/**
 * Permet de mettre à l'arrêt l'exécution en cours que réalise l'Arduino. Cette fonction peut se
 * révéler utile si le croquis Arduino utilise la fonction loop() mais souhaite à un moment donné
 * stopper le robot.
 */
void stopper(){
	while (true){														// Tout le temps
		delay(delaiBouton);												// on attend un petit peu.
	}
}

/**
 * Règle la vitesse de rotation des moteurs pas à pas.
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
 * s'effectue autour de l'axe de décrit le feutre positionné dans l'emplacement prévu à cet
 * effet, de sorte que s'il reste baisser lors de l'opération, cela ne laisse pas de cercle
 * de tracé derrière le robot.
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
 * de tracé derrière le robot.
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
 * ajusté.
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
