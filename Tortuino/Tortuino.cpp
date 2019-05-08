
# include <SD.h>
# include <SPI.h>
# include <Tortuino.h>
# include <Stepper.h>
# include <Servo.h>
# include <math.h>


const int stepsPerRevolution	=	64 * 64 / 2;
	  float	PERIMETER	=	M_PI * 9.2,	// Périmètre des roues du robot.
			BRAQUAGE	=	11.3 / 2;	// Rayon de braquage du robot.

const int	FEUTRE_HAUT	=	50,			// Angle de la postion haute du servomoteur ;
			FEUTRE_BAS	=	10;			// position basse.

const int	portBouton	=	7,			// Port du bouton de démarrage.
			portServo	=	9;			// Port du servomoteur.

const int	delaiBouton	=	10;			// Delai en ms entre chaque test du bouton.

const int 	delaiMonterDescendre	=	200;	// Delai en ms d'attente après l'envoi d'une commande au feutre.

Stepper stepperLeft(stepsPerRevolution, 10, 12, 11, 13);
Stepper stepperRight(stepsPerRevolution, 2, 4, 3, 5);

Servo servo;



int distanceToStep(float distance) {
	return (int)(distance / PERIMETER * stepsPerRevolution);
}

void initialiser() {
	servo.attach(portServo);
	pinMode(portBouton, INPUT_PULLUP);
	vitesse(10);
	descendreFeutre();
	attendreBouton();
}

void initialiser(char color) {
	if(color == "w") {
		BRAQUAGE = 11.3 / 2;	// Rayon pour le robot blanc OK
	}
	else if(color == "j") {
		BRAQUAGE = 11.3 / 2;
	}
	else if(color == "b") {
		BRAQUAGE = 11 / 2;		// Rayon pour le robot bleu OK
	}
	else if(color == "v") {
		BRAQUAGE = 10.5 / 2;
	}
	else if(color == "r") {
		BRAQUAGE = 11.3 / 2;
	}
	else if(color == "n") {
		BRAQUAGE = 11.3 / 2;
	}
	initialiser();
}

void initialiser(float braquage) {
	BRAQUAGE = braquage / 2;
	initialiser();
}

void attendreBouton() {
	int oldState, newState = digitalRead(portBouton);

	while (true) {
		oldState = newState;
		newState = digitalRead(portBouton);

		if (oldState == LOW && newState == HIGH) {
			return;
		}

		delay(delaiBouton);
	}
}

void stopper(){
	while (true){
		delay(delaiBouton);
	}
}

void vitesse(int v) {
	stepperRight.setSpeed(v);
	stepperLeft.setSpeed(v);
}

void avancer(float distance) {
	int steps = distanceToStep(fabs(distance));
	int sens = 1;
	if (distance < 0) {
		sens = -1;
	}

	for (int i = 0; i < steps; i++) {
		stepperRight.step(sens);
		stepperLeft.step(-sens);
	}
}

void reculer(float distance) {
	avancer(-distance);
}

void tournerGauche(float angle) {
	int steps = distanceToStep(M_PI / 180 * fabs(angle) * BRAQUAGE);
	int sens = 1;
	if (angle < 0) {
		sens = -1;
	}

	for (int i = 0; i < steps; i++) {
		stepperRight.step(sens);
		stepperLeft.step(sens);
	}
}

void tournerDroite(float angle) {
	tournerGauche(-angle);
}

void monterFeutre() {
	servo.write(FEUTRE_HAUT);
	delay(delaiMonterDescendre);
}

void descendreFeutre() {
	servo.write(FEUTRE_BAS);
	delay(delaiMonterDescendre);
}
