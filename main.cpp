/*
Nom du fichier: main.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description du projet: Ce programme sert à implémenter le jeu de cartes SchottenTotten en C++. Dans cette première version, le programme ne fait intervenir aucune interface graphique.
                       Tout se passe dans la console. De plus, le joueur ne peut faire que du joueur VS joueur.
*/

#include "structures.h"
#include "fonctions.h"
#include "g_variables.h"
#include <time.h>

// Les variables globales du programme sont définies dans structures.h.

using namespace std;

int main()
{
    // Initialisation des variables globales
    int numBorne;
    init(game::terrain);
    afficherTerrain(game::terrain);
    afficherPile();
    piocheMain(game::mainJ1,game::pile);
    piocheMain(game::mainJ2,game::pile); 
    cout << "Quel est le nom du joueur 1 ?" << endl;
    cin >> game::nomJ1;
    cout << "La main de " << game::nomJ1 << " est  : ";
    afficherMain(game::mainJ1);
    changeJoueur();
    sautDeLignes(tailleSautLigne);
    cout << "Et quel est le nom du joueur 2 ?" << endl;
    cin >> game::nomJ2;
    cout << "La main de " << game::nomJ2 << " est  : ";
    afficherMain(game::mainJ2);
    changeJoueur();
    sautDeLignes(tailleSautLigne);
    while (game::fini==0)
    {
        // Tour J1
        cout << "C'est votre tour, " << game::nomJ1 << " !" << endl;
        cout << "Voici le terrain :" << endl;
        afficherTerrain(game::terrain);
        cout << "Voici votre main : "<< endl;
        afficherMain(game::mainJ1);
        cout << game::nomJ1 << ", voulez-vous revendiquer une borne ? Entrez 1 si vous le souhaitez. Sinon, entrez un autre nombre : ";
        if (getInt() == 1)
        {
            std::cout << "Quelle borne voulez vous revendiquer ? Entrez son numero : ";
            numBorne = getIntLim(nbBornes);
            sautDeLignes(1);
            revendiquer(numBorne, 1);

        }

        else
            std::cout << "Vous n'avez pas revendique de bornes." << std::endl;

        sautDeLignes(1);
        placerCarteClan(1);
        pioche(game::mainJ1, game::pile);
        cout << "Voici votre main apres pioche :" << endl;
        afficherMain(game::mainJ1);
        bloquer();

        if (game::fini==0) // Sinon la partie est déjà finie.
        {
            sautDeLignes(tailleSautLigne);
            changeJoueur();
            //Tour J2
            cout << "C'est votre tour, " << game::nomJ2 << " !" << endl;
            cout << "Voici le terrain :" << endl;
            afficherTerrain(game::terrain);
            cout << "Voici votre main :" << endl;
            afficherMain(game::mainJ2);
            cout << game::nomJ2 << ", voulez-vous revendiquer une borne ? Entrez 1 si vous le souhaitez. Sinon, entrez un autre nombre : ";
            if (getInt() == 1)
            {
                std::cout << "Quelle borne voulez vous revendiquer ? Entrez son numero : ";
                numBorne = getIntLim(nbBornes);
                sautDeLignes(1);
                revendiquer(numBorne, 2);

            }

            else
                std::cout << "Vous n'avez pas revendique de bornes." << std::endl;
            sautDeLignes(1);
            placerCarteClan(2);
            pioche(game::mainJ2, game::pile);
            cout << "Voici votre main apres pioche :" << endl;
            afficherMain(game::mainJ2);
            bloquer();
            sautDeLignes(tailleSautLigne);
            changeJoueur();
        }
    }
    afficherGagnant(game::fini);
    return 0;
}


