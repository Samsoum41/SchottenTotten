/*
Nom du fichier: cartes.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à implémenter l'ensemble des fonctions qui interviennent dans la construction et l'utilisation des cartes et de la pile de carte.

*/

#include "structures.h"
#include <cstdlib>
#include <cmath>

void permut(Liste &liste,int nb1,int nb2)
{
    int inter;
    inter=liste[nb1];
    liste[nb1]=liste[nb2];
    liste[nb2]=inter;
}

std::string couleur(int numeroCouleur)
{
    switch (numeroCouleur)
    {
        case 0:
            return "<>";
            break;
        case 1:
            return "<3";
            break;
        case 2:
            return ">>";
            break;
        case 3:
            return "Trrr";
            break;
        default:
            std::cout << "Il y a une erreur là, dans l'attribution des noms des couleurs." << std::endl;
            return 0;
    }
}


void push(Carte carte, Chaine &pile)
{
    Chaine* nvMaillon= new Chaine;
    *nvMaillon=pile;
    pile.carte=carte;
    pile.suivant=nvMaillon;
}

Carte pop(Chaine &pile)
{
    Carte nvCarte{pile.carte};
    Chaine* ptr{pile.suivant};
    pile = *pile.suivant;
    delete ptr;
    return nvCarte;
}

Chaine creerPile()
{
    /*
    L'objectif de cette fonction sera de créer une pile qui représentera le paquet de 52 cartes. Cette pile doit donc comprendre toutes les cartes en un seul modèle et les organiser de manière aléatoire.
    Pour cela, on va considérer la suite de nombre 0 -> 52 qu'on va stocker dans un tableau. Chaque numéro représente l'une des cartes du paquet. On réalise ensuite un nombre aléatoire de permutations
    aléatoires dans ce tableau. Ainsi le tableau contient un 52-arrangement de [0,51] ordonné de manière aléatoire.
    */
    int nbPermutations,rand1,rand2;
    Chaine pile;
    // On fixe un nombre aléatoire de permutations à effectuer, en prenant garde que ce nombre ne soit pas trop élevé (<50)
    nbPermutations=100;

    Liste liste;
    for (int i=0;i<52;i++)
    {
        liste[i]=i;
    }
    for (int i=0;i<nbPermutations;i++)
    {
        rand1=std::floor(std::rand()%52)+1;
        rand2=std::floor(std::rand()%52)+1;
        permut(liste,rand1,rand2);
    }
    for (int i=0;i<52;i++)
    {
        Carte carte;
        carte.valeur=liste[i]/4 +1;
        carte.couleur=couleur(liste[i]%4);
        push(carte,pile);
    }
    return pile;
}

void piocheMain(VectCartes &main, Chaine &pile)
{
    for (int i=0;i<tailleMain;i++)
    {
        std::cout << pile.carte.couleur << std::endl;
        main[i]= pop(pile);
    }
}
