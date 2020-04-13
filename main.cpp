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

// Les variables globales du programme sont définies dans structures.h.

using namespace std;

int main()
{
    string temp;
    int numBorne;
    srand(time(NULL));
    init(terrain);

    afficherTerrain(terrain);
    pile=creerPile();
    piocheMain(mainJ1,pile);
    piocheMain(mainJ2,pile);

    cout << "Quel est le nom du joueur 1 ?" << endl;
    cin >> nomJ1;
    cout << "La main de " << nomJ1 << "est  : ";
    afficherMain(mainJ1);
    cin >> temp;
    sautDeLignes(10);

    cout << "Et quel est le nom du joueur 2 ?" << endl;
    cin >> nomJ2;
    cout << "La main de " << nomJ2 << "est  : ";
    afficherMain(mainJ2);
    cin >> temp;
    sautDeLignes(10);

    while (fini==0)
    {
        // Tour J1
        cout << "C'est votre tour, " << nomJ1 << " !" << endl;
        cout << nomJ1 << ", voulez-vous revendiquer revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 0." << endl;
        cin >> numBorne;
        if (numBorne > 0)
        {
            revendiquer(numBorne,J1);
        }
        else
        {
            cout << "Vous n'avez pas revendiqué de bornes." << endl;
        }
        placerCarteClan(1);
        pioche(mainJ1, pile);

        if (fini==0)
        {
            sautDeLignes(10);
            cout << "Ce sera au tour de " << nomJ2 << " de jouer son tour, pressez entrée lorsque " << nomJ2 << " sera prêt(e)." << endl;
            cin >> temp;



            // Tour J2
            cout << "C'est votre tour, " << nomJ2 << " !" << endl;
            cout << nomJ2 << ", voulez-vous revendiquer revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 0." << endl;
            cin >> numBorne;
            if (numBorne > 0)
            {
                revendiquer(numBorne,J2);
            }
            else
            {
                cout << "Vous n'avez pas revendiqué de bornes." << endl;
            }
            placerCarteClan(2);
            pioche(mainJ2, pile)
            sautDeLignes(10);
            cout << "Ce sera au tour de " << nomJ1 << " de jouer son tour, pressez entrée lorsque " << nomJ1 << " sera prêt(e)." << endl;
            cin << temp;
        }
    }
    afficherGagnant(fini)
    return 0;
}
