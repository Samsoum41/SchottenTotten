/*
Nom du fichier: affichage.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à implémenter l'ensemble des fonctions qui interviennent dans l'affichage du terrain.

*/

#include "structures.h"

using namespace std;

void init(TabCartes &terrain)
{
    for (int i=0 ; i<tailleColonne;i++)
    {
        for (int j=1;j<4;j++)
        {
            // Les cartes de valeur 0 représenteront des emplacements vides sur le terrain
            terrain[i][j].valeur=0;
        }
        // Les cartes de valeur -1 représentent les bornes.
        terrain[i][4].valeur=-1;
        for (int j=5;j<tailleColonne;j++)
        {
            // Les cartes de valeur 0 représenteront des emplacements vides sur le terrain
            terrain[i][j].valeur=0;
        }
    }
    // On distribue les cartes dans les mains de chaque joue
    // On place un message pour marquer le début du jeu !
    std::cout << "SCHOTTEN TOTTEN" << std::endl;
    std::cout << "Dans ce jeu, nous representerons les couleurs avec ce code :" << std::endl;
    std::cout << "- la couleur 'pique' sera représentee par : >>" << std::endl;
    std::cout << "- la couleur 'coeur' sera représentee par : <3" << std::endl;
    std::cout << "- la couleur 'trefle' sera représentee par : Tr" << std::endl;
    std::cout << "- la couleur 'carreau' sera représentee par : <>" << std::endl;
    std::cout << "La partie commence !" << std::endl;
}

void afficherCarte(Carte carte)
{
    switch(carte.valeur)
    {
        case -1:
            std::cout << "   B   ";
            break;
        case 0:
            std::cout << "       ";
            break;
        case 10:
            std::cout << " 10 >> ";
            break;
        case 11:
            std::cout << " J  " << carte.couleur << " ";
            break;
        case 12:
            std::cout << " Q  " << carte.couleur << " ";
            break;
        case 13:
            std::cout << " K  " << carte.couleur << " ";
            break;

        default:
            std::cout << " " << carte.valeur << "  " << carte.couleur << " ";
    }
}

void afficherTerrain(TabCartes terrain)
{
    std::cout << "________________________________________________________________" << std::endl;
    for (int ligne=0;ligne<tailleColonne;ligne++)
    {
        for (int colonne=0;colonne<tailleColonne;colonne++)
        {
            afficherCarte(terrain[colonne][ligne]);
        }
    std::cout << std::endl;
    }
    std::cout << "________________________________________________________________" << std::endl;
}

void afficherMain(VectCartes main)
{
    for (int i=0;i<tailleMain;i++)
    {
        afficherCarte(main[i]);
        std::cout << "|" ;
    }
    std::cout << std::endl;
}

void sautDeLignes(int nbLignes)
{
    for (int i=0;i<nbLignes;i++)
    {
        cout << endl;
    }
}

void afficherGagnant(int numJGagnant)
{

}

