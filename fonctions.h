/*
Nom du fichier: fonctions.h
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à stocker les prototypes du fichier fonctions.cpp.
*/


// On commence par les fonctions de 'affichage.cpp'
void init(TabCartes terrain);
void afficherCarte(Carte carte);
void afficherTerrain(TabCartes terrain);
void afficherMain(VectCartes main);


// Ensuite celles de 'cartes.cpp'
Chaine creerPile();
void piocheMain(VectCartes &main,Chaine &pile);
