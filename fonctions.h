/*
Nom du fichier: fonctions.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à stocker les prototypes du fichier fonctions.cpp.
*/

#pragma once
#include "structures.h"

// On commence par les fonctions de 'affichage.cpp'
void init(TabCartes &terrain);
void afficherCarte(Carte carte);
void afficherTerrain(TabCartes terrain);
void afficherMain(VectCartes main);
void sautDeLignes(int nbLignes);
void afficherGagnant(int numJGagnant);


// Ensuite celles de 'cartes.cpp'
Chaine creerPile();
void piocheMain(VectCartes &main,Chaine &pile);
void pioche(VectCartes &main, Chaine &pile);
bool testFinie(int numJoueur);
int testCombinaisons1(int borne, int numJoueur);
int maxCartes(VectCartes cartes);
int calculScore(Carte* cartes);
bool estUnBrelan(Carte* cartes);
bool estUneSuiteCouleur(Carte* cartes);
bool estUneCouleur(Carte* cartes);
bool estUneSuite(Carte* cartes);
bool estUneSuiteVect(std::vector<int> bornesJoueur);
int distanceMod13(int a, int b);
bool testBorneRemplie(int numBorne, int numJoueur);
void revendiquer (int numBorne, int numJoueur);
void placerCarteClan(int joueur);

