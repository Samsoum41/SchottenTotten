/*
Nom du fichier: main.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description du projet: Ce programme sert à implémenter le jeu de cartes SchottenTotten en C++. Dans cette première version, le programme ne fait intervenir aucune interface graphique.
                       Tout se passe dans la console. De plus, le joueur ne peut pour l'instant que faire du joueur VS joueur.

*/

#include "structures.h"
#include "fonctions.h"
#include <time.h>

// Variables globales du programme:
VectCartes mainJ1, mainJ2;
TabCartes terrain;
Chaine pile;


using namespace std;

int main()
{

    srand(time(NULL));
    init(terrain);
    afficherTerrain(terrain);
    pile=creerPile();

    piocheMain(mainJ1,pile);
    std::cout << "REGARDEZ PAR LA " << std::endl;

    piocheMain(mainJ2,pile);
    std::cout << "La main du joueur 1 : ";
    afficherMain(mainJ1);
    std::cout << std::endl;
    std::cout << "La main du joueur 2 : ";
    afficherMain(mainJ2);
    std::cout << std::endl;

    return 0;
}
