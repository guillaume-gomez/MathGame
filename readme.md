Math Game
===================

> **Le projet reste en cours de développement, certaine fonctionnalités peuvent dysfonctionner**


Idée
-------------
Le but de ce jeu était de faire un jeu de plate-forme en utilisant les courbes mathématiques comme élément central du jeu.

![In-game img]( resReadme/in-game1.png?raw=true )
![In-game img]( resReadme/in-game2.png?raw=true )
![In-game img]( resReadme/in-game3.png?raw=true )

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
> la version necessaire est _SFML2.1_ disponible[ ici](http://www.sfml-dev.org/download/sfml/2.1/index-fr.php) 

Même si vous choisissez la librarie deja compilée pour votre OS, téléchargez les sources pour la suite de l'installation :coffee

## Thor
> Les sources sont contenu dans le dossier _extlib_

Prendre les sources et configurer la compilation avec *cmake*
** Si il ne trouve pas la SFML, n'oublier de définir la variable `SFML_INCLUDE_DIR=PathToSFML/include`

lancer ensuite la commande `sudo make install` dans le dossier de sortie de configuration.

Plus de précisions: 
[tutorial officiel de l'installation de Thor](http://www.bromeon.ch/libraries/thor/tutorials/v2.0/installation.html)

### SFGUI
Prendre les sources dans le repository (dans le dossier _extlibs_) et configurer la compilation avec *cmake*

> Définir deux variables
> `SFML_ROOT=pathToSourcesSFML"`
> `CMAKE_MODULE_PATH=pathToSourceSFML/cmake/Modules`

lancer ensuite la commande `sudo make install` dans le dossier de sortie de configuration.
 
[Site officiel de la librairie](http://sfgui.sfml-dev.de/)

## Compiler Math Game
### Via code::blocks
il suffit de lancer le projet :

![Linker codeblocks option]( resReadme/linker_cb.png?raw=true)

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


![Include codeblocks option]( resReadme/include_cb.png?raw=true)


### Via un makefile
> nous fournirons prochainement un makefile :)

Licence
------------
LGPL

