/*
Nom du fichier: g_variables.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 16/04/2020

Description: Ce fichier sert à déclarer et initialiser les variables globales du jeu de manière à ce qu'elles soient accessible dans l'ensemble des fichiers et définies qu'une seule et unique fois.

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
    std::vector<int> bornesJ1; // Variable qui stocke les numéros des bornes d'un joueur.
    std::vector<int> bornesJ2; 
    int joueurDerniereCarte[9]; // On considère un tableau de taille 9 contenant le numéro du dernier joueur à avoir posé une carte dans la borne i.
    int min(int* listeNombres, int taille)  // On définit notre propre fonction min pour un tableau.
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



