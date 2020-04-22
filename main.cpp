/*
Nom du fichier: main.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de cr�ation: 19/03/2020

Description du projet: Ce programme sert � impl�menter le jeu de cartes SchottenTotten en C++. Dans cette premi�re version, le programme ne fait intervenir aucune interface graphique.
                       Tout se passe dans la console. De plus, le joueur ne peut faire que du joueur VS joueur.
*/

#include "structures.h"
#include "fonctions.h"
#include "g_variables.h"
#include <time.h>

// Les variables globales du programme sont d�finies dans structures.h.

using namespace std;

int main()
{
    // Initialisation des variables globales
    int numBorne;
    init(game::terrain);
    afficherTerrain(game::terrain);
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
        cout << game::nomJ1 << ", voulez-vous revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 9 : ";
        cin >> numBorne;
        sautDeLignes(1);
        if (numBorne <9) // 9 repr�sente le nombre de bornes - 1.
        {
            revendiquer(numBorne,1);
        }
        else
        {
            cout << "Vous n'avez pas revendique de bornes." << endl;
        }
        placerCarteClan(1);
        pioche(game::mainJ1, game::pile);
        cout << "Voici votre main apres pioche :" << endl;
        afficherMain(game::mainJ1);
        bloquer();

        if (game::fini==0) // Sinon la partie est d�j� finie.
        {
            sautDeLignes(tailleSautLigne);
            changeJoueur();
            //Tour J2
            cout << "C'est votre tour, " << game::nomJ2 << " !" << endl;
            cout << "Voici le terrain :" << endl;
            afficherTerrain(game::terrain);
            cout << "Voici votre main :" << endl;
            afficherMain(game::mainJ2);
            cout << game::nomJ2 << ", voulez-vous revendiquer une borne ? Si oui, laquelle ? Sinon, entrez 9." << endl;
            cin >> numBorne;
            if (numBorne <9)
            {
                revendiquer(numBorne,2);
            }
            else
            {
                cout << "Vous n'avez pas revendique de bornes." << endl;
            }
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
