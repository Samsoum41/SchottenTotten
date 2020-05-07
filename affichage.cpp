/*
Nom du fichier: affichage.cpp
Nom du projet: SchottenTotten
Auteur: Samy Hocine
Date de création: 19/03/2020

Description: Ce fichier sert à implémenter l'ensemble des fonctions qui interviennent dans l'affichage du terrain ou de cartes à l'écran.

*/

#include "structures.h"
#include "g_variables.h"
#include "fonctions.h"

using namespace std;

/*
Cette fonction est appelée en début de partie, elle va initialisé la variable globale 'terrain'.
*/
void init(TabCartes &terrain)
{
    for (int i=0 ; i<tailleColonne;i++)
    {
        for (int j=1;j<4;j++)
            // Les cartes de valeur 0 représenteront des emplacements vides sur le terrain
            terrain[i][j].valeur=0;
        // Les cartes de valeur -1 représentent les bornes.
        terrain[i][4].valeur=-1;
        for (int j=5;j<tailleColonne;j++)
            // Les cartes de valeur 0 représenteront des emplacements vides sur le terrain
            terrain[i][j].valeur=0;
    }
    // On distribue les cartes dans les mains de chaque joue
    // On place un message pour marquer le début du jeu !
    std::cout << "SCHOTTEN TOTTEN" << std::endl;
    std::cout << "Dans ce jeu, nous representerons les couleurs avec ce code :" << std::endl;
    std::cout << "- la couleur 'pique' sera représentee par : >>" << std::endl;
    std::cout << "- la couleur 'coeur' sera représentee par : <3" << std::endl;
    std::cout << "- la couleur 'trefle' sera représentee par : Tr" << std::endl;
    std::cout << "- la couleur 'carreau' sera représentee par : <>" << std::endl;
    cout << endl;
    std::cout << "Tu vas jouer qu'en solo contre toi-meme pour l'instant. Pourquoi ? " << std::endl;
    std::cout << "Parce que le seul qui puisse te battre, c'est toi." << std::endl;
    cout << endl;
    std::cout << "La partie commence !" << std::endl;
}


/*
Cette fonction est appelée pour afficher des cartes à l'écran. Elle s'occupe de remplacer la valeur d'une carte comme le valet ( valeur=11 ) en le symbole correct associé (J).
*/
void afficherCarte(Carte carte)
{
    switch(carte.valeur)
    {
        case -1:
            std::cout << "   B   ";
            break;
        case 0:
            std::cout << "       ";
            break;
        case 11:
            std::cout << " J  " << carte.couleur << " ";
            break;
        case 12:
            std::cout << " Q  " << carte.couleur << " ";
            break;
        case 13:
            std::cout << " K  " << carte.couleur << " ";
            break;

        default:
            std::cout << " " << carte.valeur << "  " << carte.couleur << " ";
    }
}

/*
Cette fonction gère l'affichage de chaque élément du terrain.
*/
void afficherTerrain(TabCartes terrain)
{
    std::cout << "___________________________________________________________________" << std::endl;
    std::cout << "        0      1      2      3      4      5      6      7      8  " << std::endl;
    for (int ligne=0;ligne<tailleColonne;ligne++)
    {
        cout << " " << ligne << " | ";
        for (int colonne=0;colonne<tailleColonne;colonne++)
        {
            afficherCarte(terrain[colonne][ligne]);
        }
    std::cout << std::endl;
    }
    std::cout << "___________________________________________________________________" << std::endl;
}

/*
Cette fonction sera appelée à chaque tour pour montrer à chaque joueur le contenu de sa main.
*/
void afficherMain(VectCartes main)
{
    sautDeLignes(2);
    std::cout << "Indice de la carte :";
    for (int i = 0; i < tailleMain; i++)
        std::cout << "   " << i << "   |";
    sautDeLignes(1);
    std::cout << "_______________________________________________________________________";
    sautDeLignes(2);
    std::cout << "Carte              :";
    for (int i=0;i<tailleMain;i++)
    {
        afficherCarte(main[i]);
        std::cout << "|" ;
    }
    sautDeLignes(2);
}

void sautDeLignes(int nbLignes)
{
    for (int i=0;i<nbLignes;i++)
    {
        cout << endl;
    }
}

void afficherGagnant(int numJGagnant)
{
    cout << "La partie est terminée ! Le joueur numero " << numJGagnant << " a gagne la partie de SchottenTotten !" << endl;
}

/*
Cette fonction s'occupe de demander au joueur où il veut placer sa carte clan, de la placer sur le terrain, et appelle retireCarteMain pour retirer la carte de la main du joueur.
*/
void placerCarteClan(int joueur)
{
    bool placer{false};
    int numBorne, numCarte;
    //Boucle qui empêche les joueurs de sélectionner une borne déjà remplie
    while (!placer)
    {
        if (joueur==1)
            cout << game::nomJ1 << ", veuillez choisir une borne ou poser une carte clan : ";
        else if (joueur ==2)
            cout <<  game::nomJ2 << ", veuillez choisir une borne ou poser une carte clan : ";
        
        numBorne = getIntLim(nbBornes);  

        if ((game::terrain[numBorne][1].valeur!=0 && joueur==1) || (game::terrain[numBorne][7].valeur!=0 && joueur==2) )
            cout << "Vous avez choisi une borne deja remplie, vous ne pouvez pas pose de carte clan dessus." << endl;
        else
            placer=true;

    }
    cout << "\n Veuillez choisir le numero de la carte que vous voulez y placer : ";
    numCarte = getIntLim(tailleMain);
    if (joueur ==1)
    {
        if (game::terrain[numBorne][3].valeur==0)
        {
            game::terrain[numBorne][3]=game::mainJ1[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else if (game::terrain[numBorne][2].valeur==0)
        {
            game::terrain[numBorne][2]=game::mainJ1[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else if (game::terrain[numBorne][1].valeur==0)
        {
            game::terrain[numBorne][1]=game::mainJ1[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else
            cout << "Erreur: Dans 'placerCarteClan', les tas de la borne " << numBorne << " sont deja remplis mais celle-ci est encore sollicitee !!!" << endl;
    }
    else if (joueur==2)
    {
        if (game::terrain[numBorne][5].valeur==0)
        {
            game::terrain[numBorne][5]=game::mainJ2[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else if (game::terrain[numBorne][6].valeur==0)
        {
            game::terrain[numBorne][6]=game::mainJ2[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else if (game::terrain[numBorne][7].valeur==0)
        {
            game::terrain[numBorne][7]=game::mainJ2[numCarte];
            retirerCarteMain(numCarte, joueur);
        }
        else
            cout << "Erreur: Dans 'placerCarteClan', les tas de la borne " << numBorne << " sont deja remplis mais celle-ci est toujours au milieu de la colonne !!!" << endl;
    }
    else
        cout << "Erreur: Dans 'placerCartePlan', la variable joueur est mal definie !!! " << endl;
    game::joueurDerniereCarte[numBorne]=joueur;
}

/*
Cette fonction est appelé lorsque l'on veut demander aux joueurs d'échanger leurs places.
*/
void changeJoueur()
{
    char temp;
    cout << "Vous devez echanger votre place avec l'autre joueur. Une fois l'echange fait, entrez un caractere ou un nombre :" ;
    std::cin >> temp;
    std::cin.ignore(32767, '\n');
    cout << endl;
}

/*
Cette fonction intervient à chaque fois que l'on souhaite marquer un temps d'arrêt
*/
void bloquer()
{
    char temp;
    cout << "Pour continuer, entrez un caractere ou un nombre :" ;
    std::cin >> temp;
    std::cin.ignore(32767, '\n');
    cout << endl;
}

/*
Cette fonction parcourt la liste chainée et affiche chacune des cartes qu'elle y trouve.
*/
void afficherPile()
{
    Chaine *ptr{&game::pile};
    while (ptr)
    {
        cout << (ptr -> carte).valeur << (ptr -> carte).couleur << endl;
        ptr=ptr -> suivant;
    }
}


/*
Cette fonction s'occupe de réaliser les vérifications nécessaires à l'entrée d'un entier par l'utilisateur.
*/
int getInt()
{
    while (true)
    {
        int i{ 0 };
        std::cin >> i;
        //On vérifie que l'utilisateur n'est pas mis en échec l'opérateur cin en entrant un caractère non convertible en entier, auquel cas on le repasse en mode normal.
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Vous n'avez pas entrez un entier, veuillez recommencer : ";
        }
        else
        {
            //Si l'utilisateur a entré du contenu en plus d'un entier, on vide le buffer pour les prochaines fois:
            std::cin.ignore(32767, '\n');
            return i;
        }
    }
}

/*
Cette fonction là ajoute des vérifications supplémentaires dans le cas où l'entier que l'on veut demander correspond à un numéro de carte ou une borne par exemple.
 */
int getIntLim(int max)
{
    while (true)
    {
        int i{ getInt() };
        if (i < max && i >= 0)
            return i;
        else
            std::cout << "Vous n'avez pas entré un entier entre 0 et " << max-1 << ", veuillez recommencer :";
    }
}
