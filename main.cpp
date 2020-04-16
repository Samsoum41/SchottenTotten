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
#include "g_variables.h"
#include <time.h>

// Les variables globales du programme sont définies dans structures.h.

using namespace std;

int main()
{
    string temp;
    int numBorne;
    srand(time(NULL));
    init(game::terrain);
    afficherTerrain(game::terrain);
    piocheMain(game::mainJ1,game::pile);
    piocheMain(game::mainJ2,game::pile);

    cout << "Quel est le nom du joueur 1 ?" << endl;
    cin >> game::nomJ1;
    cout << "La main de " << game::nomJ1 << "est  : ";
    afficherMain(game::mainJ1);
    cin >> temp;
    sautDeLignes(10);

    cout << "Et quel est le nom du joueur 2 ?" << endl;
    cin >> game::nomJ2;
    cout << "La main de " << game::nomJ2 << "est  : ";
    afficherMain(game::mainJ2);
    cin >> temp;
    sautDeLignes(10);

    while (game::fini==0)
    {
        // Tour J1
        cout << "C'est votre tour, " << game::nomJ1 << " !" << endl;
        cout << game::nomJ1 << ", voulez-vous revendiquer revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 0." << endl;
        cin >> numBorne;
        if (numBorne > 0)
        {
            revendiquer(numBorne,1);
        }
        else
        {
            cout << "Vous n'avez pas revendiqué de bornes." << endl;
        }
        placerCarteClan(1);
        pioche(game::mainJ1, game::pile);

        if (game::fini==0)
        {
            sautDeLignes(10);
            cout << "Ce sera au tour de " << game::nomJ2 << " de jouer son tour, pressez entrée lorsque " << game::nomJ2 << " sera prêt(e)." << endl;
            cin >> temp;



            // Tour J2
            cout << "C'est votre tor, " << game::nomJ2 << " !" << endl;
            cout << game::nomJ2 << ", voulez-vous revendiquer revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 0." << endl;
            cin >> numBorne;
            if (numBorne > 0)
            {
                revendiquer(numBorne,2);
            }
            else
            {
                cout << "Vous n'avez pas revendiqué de bornes." << endl;
            }
            placerCarteClan(2);
            pioche(game::mainJ2, game::pile);
            sautDeLignes(10);
            cout << "Ce sera au tour de " << game::nomJ1 << " de jouer son tour, pressez entrée lorsque " << game::nomJ1 << " sera prêt(e)." << endl;
            cin >> temp;
        }
    }
    afficherGagnant(game::fini);
    return 0;
}
