Math Game
===================

> **Le projet reste en cours de développement, certaine fonctionnalités peuvent dysfonctionner**


Idée
-------------
Le but de ce jeu était de faire un jeu de plate-forme en utilisant les courbes mathématiques comme élément central du jeu.

<img src="resReadme/in-game1.png" alt="In-game img" width:"75%" />
<img src="resReadme/in-game2.png" alt="In-game img" width:"75%" />
<img src="resReadme/in-game3.png" alt="In-game img" width:"75%" />



Comment jouer
-------------------
## touches
* se deplacer : *Fléches directionnelles*
* passer à la courbes suivantes: *P*
* passer à la courbes précédente: *M*

Modes de jeu
-------------------
Il existe deux mode de jeu:

- le premier est la version du jeu normale
- le second est le mode _hard_ (le nombre de changement de courbes est plus réduit)

Installation
-------------
**L'installation n'a été testé que sur Linux pour le moment.**

* MathGame contient des librairies externes que vous devrez compiler par vous même pour faire fonctionner le jeu*

## SFML
> Les sources sont contenu dans le dossier _extlib_

	cd MathGame/extlibs
	unzip extlibs_sources.zip
	cd SFML-2.1

## Thor
> Les sources sont contenu dans le dossier _extlib_

Prendre les sources et configurer la compilation avec *cmake*
Si il ne trouve pas la SFML, n'oublier de définir la variable `SFML_INCLUDE_DIR=PathToSFML/include`

	cd Thor
	mkdir build && cd build
	cmake ..

lancer ensuite la commande `sudo make install` dans le dossier de sortie de configuration.

Plus de précisions:
[tutorial officiel de l'installation de Thor](http://www.bromeon.ch/libraries/thor/tutorials/v2.0/installation.html)

### SFGUI
Prendre les sources dans le repository (dans le dossier _extlibs_) et configurer la compilation avec *cmake*

	cd MathGame/extlibs/SFGUI
	mkdir build && cd build

> Définir deux variables
> `SFML_ROOT=pathToSourcesSFML"`
> `CMAKE_MODULE_PATH=pathToSourceSFML/cmake/Modules`

lancer ensuite la commande `sudo make install` dans le dossier de sortie de configuration.

[Site officiel de la librairie](http://sfgui.sfml-dev.de/)

## Compiler Math Game
### Via code::blocks
il suffit de lancer le projet :

<img src="resReadme/linker_cb.png" alt="Linker codeblocks option" width:"80%" />


- allez dans le dossier _build options_, et ajoutez les fichiers des librairies externes
- libsfml-audio.so,
- libsfml-graphics.so,
- libsfml-system.so,
- libsfml-window.so,
- libsfml-network.so,
- libsfgui.so,
- libthor.so

- Sous windows les extensions sont des `.a`
- Sur linux pas besoin d'inclure les headers qui lors de l'installation dans le dossier `usr/local/include` et/ou `usr/lib/include`
Sur windows, il faudra ajouter la référence ici


<img src="resReadme/include_cb.png" alt="Include codeblocks option" width:"80%" />

### Via un makefile
> nous fournirons prochainement un makefile :)

Licence
------------
LGPL

