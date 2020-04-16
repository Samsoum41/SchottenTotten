/*
Nom du fichier: structures.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à construire l'ensemble des structures de données qui interviennent dans le jeu.
*/
#pragma once
#include <string>
#include <iostream>
#include <cstddef>
#include <vector>

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
    Chaine* suivant{nullptr};
};



typedef int Liste[nbTotalCartes];
typedef Carte VectCartes[tailleMain];
typedef Carte TabCartes[tailleColonne][tailleColonne];



