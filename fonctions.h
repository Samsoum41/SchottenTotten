/*
Nom du fichier: fonctions.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à stocker les prototypes des différentes fonctions du jeu.
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
void placerCarteClan(int joueur);
void afficherGagnant(int numJGagnant);
void changeJoueur();
void bloquer();
void afficherPile();

// Ensuite celles de 'cartes.cpp'
Chaine creerPile();
void piocheMain(VectCartes &main,Chaine &pile);
void pioche(VectCartes &main, Chaine &pile);
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
void retirerCarteMain(int numCarte, int numJoueur);
void prendreBorne(int numBorne, int numJoueur);
bool testCombinaisons2(int numBorne, int numJoueur, Carte* tasSurBorneJ1, Carte* tasSurBorneJ2);
void ajouterCarte(Carte* tasSurBorne, Carte carte);
void testFinie(int numJoueur);
bool testCombinaisons1(int borne, int numJoueur, Carte* tasSurBorneJ1, Carte* tasSurBorneJ2);
void tasBorne(int numBorne, int numJoueur, Carte* tasSurBorne);
bool testPile();
void parcourirPile();
