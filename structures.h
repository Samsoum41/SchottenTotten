/*
Nom du fichier: structures.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à construire l'ensemble des structures de données qui interviennent dans le jeu.
*/

#include <string>
#include <iostream>
#include <cstddef>


const int tailleMain(6);
const int tailleColonne(9);
const int nbTotalCartes(52);

struct Carte
{
    int valeur;
    std::string couleur;
};

struct Chaine
{
    Carte carte;
    Chaine* suivant=NULL;
};



typedef int Liste[nbTotalCartes];
typedef Carte VectCartes[tailleMain];
typedef Carte TabCartes[tailleColonne][tailleColonne];

// Variables globales du programme:

VectCartes mainJ1, mainJ2;
TabCartes terrain;
Chaine pile;
std::string nomJ1, nomJ2;
int fini{0};
int bornesJ1[5]; // 5 est le nombre maximal de bornes qu'un joueur peut avoir,
int bornesJ2[5]; // au bout de 5 bornes on gagne, quoiqu'il arrive.
int joueurDerniereCarte[9]; // On considère un tableau de taille 9 contenant le numéro du dernier joueur à avoir posé une carte dans la borne i
