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
#include "g_variables.h"

using namespace std;

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
    Carte nvCarte;
    nvCarte=pile.carte;
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
        main[i]= pop(pile);
    }
}

void pioche(VectCartes &main, Chaine &pile)
{
    main[5]=pop(pile);
}

bool testBorneRemplie(int numBorne, int numJoueur)
{
    if (numJoueur ==1)
    {
        for (int i=1;i<4;i++)
        {
            if (game::terrain[numBorne][i].valeur==0)
            {
                return false;
            }
        }
    }
    else if (numJoueur == 2)
    {
        for (int i=5;i<8;i++)
        {
            if (game::terrain[numBorne][i].valeur==0)
            {
                return false;
            }
        }
    }
    else
    {
        cout << "il y a une erreur";
    }
    return true;
}

int distanceMod13(int a, int b)
{
    return (abs((a-b)%13));
}

bool estUneSuiteVect(vector<int> bornesJoueur)
{
    int taille{bornesJoueur.size()};
    bool res{false};
    for (int i=0;i<taille;i++)
    {
        for (int j=i;j<taille;j++)
        {
            if (distanceMod13(bornesJoueur[i],bornesJoueur[j])>=taille)
                return false;
        }
    }
    return true;
}

bool estUneSuite(Carte* cartes)
{
    return (distanceMod13(cartes[0].valeur,cartes[1].valeur)<3 && distanceMod13(cartes[1].valeur,cartes[2].valeur)<3 && distanceMod13(cartes[0].valeur,cartes[2].valeur)<3);
}

bool estUneCouleur(Carte* cartes)
{
    return (cartes[0].couleur==cartes[1].couleur && cartes[1].couleur==cartes[2].couleur);
}

bool estUneSuiteCouleur(Carte* cartes)
{
    return (estUneSuite(cartes) && estUneCouleur(cartes));
}

bool estUnBrelan(Carte* cartes)
{
    return (cartes[0].valeur==cartes[1].valeur && cartes[1].valeur==cartes[2].valeur);
}

int calculScore(Carte* cartes)
{
    if (estUneSuiteCouleur(cartes))
    {
        return 4;
    }
    else if (estUnBrelan(cartes))
    {
        return 3;
    }
    else if (estUneSuite(cartes))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int maxCartes(VectCartes cartes)
{
    int maxi{0};
    for (int i=0;i<tailleMain;i++)
    {
        if (maxi<cartes[i].valeur)
            maxi = cartes[i].valeur;
    }
    return maxi;
}


int testCombinaisons1(int borne, int numJoueur)
{
    int scoreJ1{0}, scoreJ2{0};
    Carte cartesBorneJ1[3];
    Carte cartesBorneJ2 [3];
    for (int i=0;i<3;i++)
    {
        cartesBorneJ1[i]=game::terrain[borne][1+i];
        cartesBorneJ2[i]=game::terrain[borne][5+i];
    }
    scoreJ1=calculScore(cartesBorneJ1);
    scoreJ2=calculScore(cartesBorneJ2);
    if (scoreJ1>scoreJ2)
    {
        return 1;
    }
    else if (scoreJ1<scoreJ2)
    {
        return 2;
    }
    else
    {
        int max1{0}, max2{0};
        max1=maxCartes(game::mainJ1);
        max2=maxCartes(game::mainJ2);
        if (max1<max2)
        {
            return 2;
        }
        else if (max1>max2)
        {
            return 1;
        }
        else
        {
            return ((game::joueurDerniereCarte[borne]+1)%2);
        }
    }
}

bool testFinie(int numJoueur)
{
    if (numJoueur==1 && (game::bornesJ1.size()>=5 || estUneSuiteVect(game::bornesJ1)))
        return true;
    else if (numJoueur==2 && (game::bornesJ2.size()>=5 || estUneSuiteVect(game::bornesJ2)))
        return true;
    else
        return false;
}

bool testCombinaisons2(int numBorne)
{

}

void revendiquer (int numBorne, int numJoueur)
{
    if (testBorneRemplie(numBorne, (numJoueur+1)%2))
    {
        int numJGagnant{-2};
        numJGagnant=testCombinaisons1(numBorne, numJoueur);
        if (numJGagnant==1)
            cout << game::nomJ1 << " a gagné la borne " << numBorne << " !" << endl;
        else if (numJGagnant==2)
            cout << game::nomJ2 << " a gagné la borne " << numBorne << " !" << endl;
        else
            cout << "Y a une erreur dans la revendiquation de la borne." << endl;
        //A la fin, on vérifie que le joueur qui a acquis la borne n'a pas gagné la partie
        testFinie(numJGagnant);
    }
    else
    {
        if (testCombinaisons2(numBorne))
        {
            cout << "Le joueur " << numJoueur << " a pris la borne " << numBorne << " !" << endl;
            testFinie(numJoueur);
        }
        else
        {
            cout << "Aucun joueur n'a pris la borne " << numBorne << "." << endl;
        }
    }
}

void placerCarteClan(int joueur)
{

}
