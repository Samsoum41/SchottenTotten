/*
Nom du fichier: g_variables.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de cr�ation: 16/04/2020

Description: Ce fichier sert � d�clarer et initialiser les variables globales du jeu de mani�re � ce qu'elles soient accessible dans l'ensemble des fichiers et d�finies qu'une seule et unique fois.

*/

#include "structures.h"
#include "fonctions.h"

// Variables globales du programme:
namespace game
{
    const double pi{3.14};
    int fini{0};
    VectCartes mainJ1, mainJ2;
    TabCartes terrain;
    Chaine pile{creerPile()};
    std::string nomJ1, nomJ2;
    std::vector<int> bornesJ1; // Variable qui stocke les num�ros des bornes d'un joueur.
    std::vector<int> bornesJ2; 
    int joueurDerniereCarte[9]; // On consid�re un tableau de taille 9 contenant le num�ro du dernier joueur � avoir pos� une carte dans la borne i.
    int min(int* listeNombres, int taille)  // On d�finit notre propre fonction min pour un tableau.
    {
        int v_min{listeNombres[0]};
        for (int i=0;i<taille;i++)
        {
            if (v_min>listeNombres[i])
                v_min=listeNombres[i];
        }
        return v_min;
    }
}



