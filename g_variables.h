/*
Nom du fichier: g_variables.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 16/04/2020

Description: Ce fichier sert à 'annoncer' les variables globales du jeu dans un namespace.
*/

#pragma once

#include "structures.h"
#include "fonctions.h"

// Variables globales du programme:
namespace game
{
    extern int fini;
    extern VectCartes mainJ1, mainJ2;
    extern TabCartes terrain;
    extern Chaine pile;
    extern std::string nomJ1, nomJ2;
    extern std::vector<int> bornesJ1; // 5 est le nombre maximal de bornes qu'un joueur peut avoir,
    extern std::vector<int> bornesJ2; // au bout de 5 bornes on gagne, quoiqu'il arrive.
    extern int joueurDerniereCarte[9]; // On considère un tableau de taille 9 contenant le numéro du dernier joueur à avoir posé une carte dans la borne i
    int min(int* listeNombres, int taille);

}

