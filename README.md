# Ecosystem simulation

![release](https://img.shields.io/badge/release-v1.0-blueviolet)
![language](https://img.shields.io/badge/language-C%2B%2B-0052cf)
![library](https://img.shields.io/badge/library-SDL2-00cf2c)
![size](https://img.shields.io/badge/size-76%20Mo-f12222)
![license](https://img.shields.io/badge/license-CC--0-0bb9ec)

<br/>

Ce dépôt contient le code source d'un programme simulant différents types d'êtres vivants, des plantes, des proies et des prédateurs afin de créer un écosystème.

<br/>

<p align="center">
	<img src="https://i.imgur.com/DgQEcKJ.png" width="700">
</p>

<br/>

# Utilisation

Vous trouverez dans le fichier [**main.cpp**](https://github.com/angeluriot/Ecosystem_simulation/blob/master/sources/main.cpp) le morceau
de code permettant de modifier les différents paramètres de la simulation :

```cpp

// ------------------------- Paramètres de la simulation -------------------------

int world_width = 320;              // Largeur du monde (en cases)
int world_height = 180;             // Hateur du monde (en cases)
int zoom = 6;                       // Taille des cases (en pixels)

int nb_plants = 160;                // Nombre de plantes au début
int growth_rate = 15;               // Vitesse de l'évolution des plantes (en pourcents)

int nb_preys = 160;                 // Nombre de proies au début
int prey_time_no_eat_max = 30;      // Temps que tient une proie sans manger
int prey_nb_eat_kid = 15;           // Nombre de plantes qu'une proie doit manger pour faire un enfant

int nb_predators = 20;              // Nombre de prédators au début
int predator_time_no_eat_max = 60;  // Temps que tient un prédateur sans manger
int predator_nb_eat_kid = 25;       // Nombre de proies qu'un prédateur doit manger pour faire un enfant

int frame_rate_max = 144;        // FPS maximum (en images par seconde)

// -------------------------------------------------------------------------------

```

<br/>

# Installation

Si vous possédez déjà le compilateur [**MinGW**](http://www.mingw.org/) et de quoi utiliser un Makefile
sur Windows, il vous suffit de télécharger l'intégralité du dépôt et de faire la commande **`make`** à la racine du projet.

<br/>

# Releases

Vous pouvez tester directement le programme sans installation en consultant les [**Releases**](https://github.com/angeluriot/Ecosystem_simulation/releases)

<br/>

# Crédits

* [**Angel Uriot**](https://github.com/angeluriot) : Créateur du projet.

* [**Maxime Bourand**](https://github.com/mbourand) : Aide à l'optimisation.
