# Ressources-Tortuino
L'ensemble des ressources informatiques nécessaires à l'utilisation du robot 
Tortuino et au bon déroulement de l'animation qui l'utilise


## Le projet

Le projet Tortuino s'est réalisé dans le cadre du [GATE](https://gate.wp.telecom-sudparis.eu/ "GATE TSP")
et a donc été réalisé par des élèves de première année de Télécom SudParis, une
école d'ingénieurs en informatique. Les projets GATE sont réalisé dans une perspective
client / équipe projet ; dans notre cas, notre client était Planète Science, une
association qui anime régulièrement différentes sorte de stage vulgarisant de
nombreux sujets scientifiques, comme la robotique, l'astronomie, la physique, ...

Planète Science nous avait ainsi formulé un livrable pour notre projet : créer
une animation de deux jours pour initier un public jeune à la programmation grâce
à la [carte de contrôle Arduino](https://www.arduino.cc/ "Arduino"). Nous avons
alors méné à bien ce projet pour en effet avoir au final cette animation. Elle
se base sur un robot qui a la capacité d'avancer, de tourner et de monter ou
descendre un feutre pour laisser derrière soi un dessin programmé à l'avance.
Puisque c'est le principe des tortues graphiques, cela a donc donné le nom Tortuino.


## But de ce Git

Ce Git a pour objectif de rassembler en un seul endroit tout ce qui est 
nécessaire pour fabriquer, utiliser, tester et simuler un robot Tortuino. Vous 
trouverez dans ce répertoire plusieurs dossiers :

* **Modèles** : tous les fichiers de conception assistée par ordinateur décrivant 
les modèles informatiques des composants d'un robot à fabriquer soi-même et 
permettant la découpe, l'impression et le montage d'un robot Tortuino.
* **Tortuino** : la bibliothèque informatique s'occupant de fournir quelques
fonctions de base pour facilement contrôler le robot.
* **TestTortuino** : un "croquis" Arduino permettant de tester de nombreuses 
fonctionnalités d'un robot Tortuino et de sa bibliothèque en une seule fois.
* **Documentation** : une documentation complète, exhaustive et précise de la 
bibliothèque informatique Tortuino en deux formats : site Web et PDF.
* **Images** : l'ensemble des images inclues dans la documentation et utiles
au reste des ressources.
* **SimulationTortuino** : un site Web permettant de visualiser de manière presque
instantanée le résultat de quelques instructions Tortuino. Cela se révèle très
utile pour des dessins complexes.

Vous trouverez enfin quelques fichiers qui s'occupent de gérer la création
automatique de la documentation grâce à l'outil dédié [Doxygen](http://doxygen.nl/ "Doxygen") :
* _DoxyConfig_ : le fichier de configuration Doxygen décrivant tous les paramètres
nécessaires à la construction automatique de la documentation.
* _Makefile_ : un fichier utilisable avec `make` qui simplifie l'appel de `doxygen`
et de `pdflatex` pour fabriquer la documentation à proprement parler.
* _make.timestamp_ : contient la dernière date d'exécution de `make` et permet donc
à ce dernier de ne pas recréer la documentation si cela n'est pas nécessaire par
rapport à la date de dernière modification de ses dépendances.
* _make.log_ : le journal regroupant les messages renvoyés lors des compilations
créant la documentation.


## Installation

Plusieurs choses sont à faire pour qu'un poste soit prêt à être utilisé pour
un stage :

* Avoir une installation de l'[éditeur Arduino](https://www.arduino.cc/en/Main/Software "Arduino IDE").
* Copier le dossier **Tortuino** dans le répertoire _libraries_ des documents Arduino.
Vous trouverez ce dernier dans :
	* _Mes Documents_ > _Arduino_ > _libraries_ si vous êtes sous Windows.
	* _~/Arduino/libraries_ si vous êtes sous Linux ou macOS.

Puis vous pouvez aussi faciliter l'utilisation du robot en réalisant :

* Mettre un raccourci vers l'éditeur Arduino sur le bureau.
* Placer le dossier **SimulationTortuino** dans un endroit simple d'accès et mettre
aussi un raccourci sur le bureau pointant vers le fichier _index.html_ du site Web.

Le reste des fichiers sert au développement du projet mais surtout à la préparation
de l'animation.


## Modification de la documentation

Si vous souhaitez modifier de votre côté les fichiers de la bibliothèque Tortuino
et les documenter, référez-vous d'abord à la [documentation Doxygen](http://doxygen.nl/manual/index.html "Doxygen manual").
Le _Makefile_ vous aidera à faciliter la création de la documentation. Une fois
un fichier modifié, il vous suffit d'exécuter la commande `make` en étant dans le
dossier principal. Ceci va automatiser Doxygen pour tout faire d'un coup. Une fois 
ceci terminé, vous trouverez le résultat des compilations dans le dossier 
**Documentation**.

Si vous souhaitez mettre à jour votre répertoire Git, il est conseillé d'exécuter
`make pull` qui va d'abord faire `git pull` puis `touch make.timestamp`. Ceci
permet de d'assurer que make ne rappellera pas Doxygen par erreur lorsque ça n'est
en fait pas nécessaire.

Ce système n'est pas affecté par une modification d'un quelconque autre fichier.
