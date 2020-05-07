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
#include <time.h>
#include "fonctions.h"

using namespace std;

void permut(Liste &liste,int nb1,int nb2)
{
    int inter;
    inter=liste[nb1];
    liste[nb1]=liste[nb2];
    liste[nb2]=inter;
}

/*
Cette fonction est appelée dans la fonction creerPile. Elle servira à associé à un nombre compris entre 0 et 3 une couleur.
*/
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
            return "Tr";
            break;
        default:
            std::cout << "Il y a une erreur la, dans l'attribution des noms des couleurs." << std::endl;
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

/*
Cette fonction aura pour objectif de créer une pile qui représentera le paquet de 52 cartes. Cette pile doit donc comprendre toutes les cartes en un seul modèle et les organiser de manière aléatoire.
Pour cela, on va considérer la suite de nombre 0 -> 51 qu'on va stocker dans un tableau. Chaque numéro représente l'une des cartes du paquet. On réalise ensuite un nombre aléatoire de permutations
aléatoires dans ce tableau. Ainsi le tableau contient un 52-arrangement de [0,51] ordonné de manière aléatoire. Enfin on associe une carte à chaque nombre en fonction de son quotient et son reste 
modulo 4=nombre de couleurs différentes.
*/
Chaine creerPile()
{
    int nbPermutations,rand1,rand2;
    Chaine pile;
    // On fixe un nombre aléatoire de permutations à effectuer, en prenant garde que ce nombre ne soit pas trop élevé (<50)
    srand(time(NULL));
    nbPermutations=100;
    // nbPermutations=std::rand()%100;
    Liste liste;

    for (int i=0;i<nbTotalCartes;i++)
    {
        liste[i]=i;
    }
    for (int i=0;i<nbPermutations;i++)
    {
        rand1=std::floor(std::rand()%52);
        rand2=std::floor(std::rand()%52);
        permut(liste,rand1,rand2);
    }
    //On traite le premier maillon de la chaîne séparément.
    pile.carte.valeur = liste[0] / 4 + 10;
    pile.carte.couleur = couleur(liste[0] % 4);
    for (int i=1;i<52;i++)
    {
        Carte carte;
        carte.valeur=liste[i]/4 +1;
        carte.couleur=couleur(liste[i]%4);
        push(carte,pile);
    }
    std::cout << "La pile est creee !";
    sautDeLignes(2);
    return pile;
}

/*
Cette fonction est appelée en début de partie pour initialiser les mains de chaque joueur.
*/
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


/*
Cette fonction teste si un joueur peut déposer une carte sur une borne, i.e s'il en a pas déjà posé 3.
*/
bool testBorneRemplie(int numBorne, int numJoueur)
{
    if (numJoueur ==1)
    {
        for (int i=1;i<4;i++)
        {
            if (game::terrain[numBorne][i].valeur==0)
                return false;
        }
    }
    else if (numJoueur == 2)
    {
        for (int i=5;i<8;i++)
        {
            if (game::terrain[numBorne][i].valeur==0)
                return false;
        }
    }
    else
        cout << "il y a une erreur #testBorneRemplie";
    return true;
}

/*
Cette fonction calcule une distance 'modulo13' au sens où ce serait la taille du plus petit chemin reliant deux points dans un cercle de valeurs, par ex : 12 est à une distance 2 de 1 ( 12->13->1)
*/
int distanceMod13(int a, int b)
{
    int valeurs[3]{abs(b-a), abs(b-a-13), abs(b-a+13)};
    return (game::min(valeurs,3));
}

bool estSansPaire(Carte* cartes)
{
    return (cartes[0].valeur!=cartes[1].valeur && cartes[1].valeur!=cartes[2].valeur && cartes[0].valeur!=cartes[2].valeur);
}

/*
Cette fonction va vérifier qu'un 3-uplet ne contient pas de paires et que les valeurs des cartes ne soient pas trop éloignées pour affirmer qu'un 3-uplet de cartes est une suite ou non.
*/
bool estUneSuite(Carte* cartes)
{
    return (estSansPaire(cartes) && distanceMod13(cartes[0].valeur,cartes[1].valeur)<3 && distanceMod13(cartes[1].valeur,cartes[2].valeur)<3 && distanceMod13(cartes[0].valeur,cartes[2].valeur)<3);
}

/*
Cette fonction va généraliser le critère précédent pour l'appliquer à un objet 'vector' de taille variable. Elle est appelée pour vérifier que les bornes d'un joueur forment une suite.
Elle renvoie true seulement lorsque tout le paquet est une suite dans un certain ordre. Le paquet doit contenir au moins 3 cartes.
*/
bool estUneSuiteVect(vector<int> bornesJoueur)
{
    int taille{ static_cast<int> (bornesJoueur.size()) };
    if (taille < 3)// On ne relève que les suites de 3 éléments ou plus.
        return false;
    else
        for (int i = 0; i < taille; i++)
        {
            for (int j = i; j < taille; j++)
            {
                if (distanceMod13(bornesJoueur[i], bornesJoueur[j]) >= taille)
                    return false;
            }
        }
    return true;
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

/*
Cette fonction calcule le score d'une combinaison de cartes dans le cadre d'une borne qui est revendiquée. Elle appelle notamment toutes les fonctions tests précédentes.
*/
int calculScore(Carte* cartes)
{
    if (estUneSuiteCouleur(cartes))
        return 4;
    else if (estUnBrelan(cartes))
        return 3;
    else if (estUneCouleur(cartes))
        return 2;
    else if (estUneSuite(cartes))
        return 1;
    else
        return 0;
}

/*
Cette fonction renvoie la plus grande valeur trouvée dans un paquet de cartes.
*/
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

/*
Cette fonction passe un tableau par adresse pour y stocker le tas de cartes qu'un joueur a sur une borne. Ces tableaux sont utilisés pour faire les tests de combinaisons(suite, couleur ..).
*/
void tasBorne(int numBorne, int numJoueur, Carte* tasSurBorne)
{
    if (numJoueur==1)
    {
        for (int i=0;i<3;i++)
        {
            tasSurBorne[i]=game::terrain[numBorne][3-i]; // /!\ Ici on s'appuie sur le fait que numJoueur prennent les valeurs 1 ou 2 seulement.
        }
    }
    else if (numJoueur==2)
    {
        for (int i=0;i<3;i++)
        {
            tasSurBorne[i]=game::terrain[numBorne][5+i]; // /!\ Ici on s'appuie sur le fait que numJoueur prennent les valeurs 1 ou 2 seulement.
        }
    }
    else
        cout << "Erreur: Mauvais definition de numJoueur #tasBorne" << endl;
}

/*
Cette fonction renvoie vraie si le numéro de joueur entrée est le gagnant, faux sinon. Elle prend en entrée les informations d'une borne qui doit être remplie !
Il faut donc que les tas contiennent 3 cartes initialisées chacun.
Ainsi, lorsqu'une revendication est faîte et fait intervenir ce test il y a toujours un gagnant pour la borne, pas de match nul.
*/
bool testCombinaisons1(int borne, int numJoueur, Carte* tasSurBorneJ1, Carte* tasSurBorneJ2)
{
    int scoreJ1{0}, scoreJ2{0};
    scoreJ1=calculScore(tasSurBorneJ1);
    scoreJ2=calculScore(tasSurBorneJ2);

    //cout << "Le tas sur la borne du cote J1 est " << tasSurBorneJ1[0].valeur << " " << tasSurBorneJ1[0].couleur << " | " << tasSurBorneJ1[1].valeur << " " << tasSurBorneJ1[1].couleur << " | " <<tasSurBorneJ1[2].valeur << " " << tasSurBorneJ1[2].couleur << endl;
    //cout << "Le tas sur la borne du cote J2 est " << tasSurBorneJ2[0].valeur << " " << tasSurBorneJ2[0].couleur << " | " << tasSurBorneJ2[1].valeur << " " << tasSurBorneJ2[1].couleur << " | " <<tasSurBorneJ2[2].valeur << " " << tasSurBorneJ2[2].couleur << endl;
    cout << "Le score de J1 est " << scoreJ1 << " alors que le score de J2 est " << scoreJ2 << endl;

    if (numJoueur==1 && scoreJ1>scoreJ2)
        return true;
    else if (numJoueur==2 && scoreJ1<scoreJ2)
        return true;
    else if (scoreJ1==scoreJ2)
    {
        int max1{0}, max2{0};
        max1=maxCartes(game::mainJ1);
        max2=maxCartes(game::mainJ2);
        cout << " le maximum de J1 est " << max1 << " et le max de J2 est " << max2 << endl;
        if ((numJoueur==1 && max1>max2) || (numJoueur==2 && max2>max1))
        {
            cout << "Les deux joueurs ont, certes, des combinaisons de meme valeurs, mais le joueur " << numJoueur << " a la carte de plus haute valeur !" << endl;
            return true;
        }
        else if (max1==max2)
        {
            /*
            S'il y a une égalité totale, le gagnant est celui qui a posé la dernière carte le plus tôt sur la borne.
            Etant donnée ce qui est attendu de la fonction, on doit vérifier si le vainqueur est celui qui revendique la borne ou pas.
            */
            int premier{ game::joueurDerniereCarte[borne] % 2 + 1 };
            cout << "Les deux joueurs ont, certes, des combinaisons de meme valeurs et des mains aussi fortes, mais le joueur " << premier << " a pose sa carte le premier !" << endl;
            //cout << "la variable jouerDernierCarte renvoie " << game::joueurDerniereCarte[borne] << " et sa version modifiee " << game::joueurDerniereCarte[borne]%2 +1 << endl;
            return (numJoueur==premier);
        }
        else
        {
            cout << "on est dans l'exception 1 #testCombinaisons1" << endl;
            return false;
        }
    }
    else
    {
        cout << "on est dans l'exception 2 #testCombinaisons1" << endl;
        return false;
    }
}

/*
Vérifie les conditions à remplir pour que la partie s'arrête, seul fonction modifiant la variable globale game::fini qui arrête la boucle du jeu.
*/
void testFinie(int numJoueur)
{
    if (numJoueur==1 && (game::bornesJ1.size()>=5 || estUneSuiteVect(game::bornesJ1)))
        game::fini=1;
    else if (numJoueur==2 && (game::bornesJ2.size()>=5 || estUneSuiteVect(game::bornesJ2)))
        game::fini=2;
}

void ajouterCarte(Carte* tasSurBorne, Carte carte)
{
    if (tasSurBorne[0].valeur==0)
        tasSurBorne[0]=carte;
    else if (tasSurBorne[1].valeur==0)
        tasSurBorne[1]=carte;
    else if (tasSurBorne[2].valeur==0)
        tasSurBorne[2]=carte;
    else
        cout << "Erreur: Dans 'ajouterCarte', on a entre un tableau qui est deja complet !!!" << endl;
}

void copierTableau(Carte* tableauACopiee, Carte* copie, int taille)
{
    for (int i=0;i<taille;i++)
        copie[i]=tableauACopiee[i];
}

bool estUneNouvelleCarte(Carte* tasCartes, Carte carte) // On suppose que la taille d'un tas est 3
{
    for (int i = 0; i < 3; i++)
    {
        if (carte.valeur == tasCartes[i].valeur && carte.couleur == tasCartes[i].couleur)
            return false;
    }
    return true;
}


/*
La fonction testCombinaison2 intervient lorsqu'un joueur revendique une borne incomplète. Son rôle est de considérer tous les cas possibles en considérant les cartes
restantes dans la pile et les mains du joueur.
Elle renvoie vraie s'il existe une combinaison potentielle permettant au joueur attaqué de gagner et faux 'il est fichu.
*/
bool testCombinaisons2(int numBorne, int numJoueur, Carte* tasSurBorneJ1, Carte* tasSurBorneJ2)
{
    // Si le défenseur (c'est toujours le cas pour l'attaquant) a 3 cartes sur la borne, on revient à un testCombinaisons1() mais
    //cout << "Le tas sur la borne du cote J1 est " << tasSurBorneJ1[0].valeur << " " << tasSurBorneJ1[0].couleur << " | " << tasSurBorneJ1[1].valeur << " " << tasSurBorneJ1[1].couleur << " | " <<tasSurBorneJ1[2].valeur << " " << tasSurBorneJ1[2].couleur << endl;
    //cout << "Le tas sur la borne du cote J2 est " << tasSurBorneJ2[0].valeur << " " << tasSurBorneJ2[0].couleur << " | " << tasSurBorneJ2[1].valeur << " " << tasSurBorneJ2[1].couleur << " | " <<tasSurBorneJ2[2].valeur << " " << tasSurBorneJ2[2].couleur << endl;
    if ((numJoueur==1 && tasSurBorneJ2[2].valeur!=0) || (numJoueur==2 && tasSurBorneJ1[2].valeur!=0))
    {
        int scoreJ1{0}, scoreJ2{0};
        scoreJ1=calculScore(tasSurBorneJ1);
        scoreJ2=calculScore(tasSurBorneJ2);
        if ((numJoueur==1 && scoreJ1<scoreJ2) || (numJoueur==2 && scoreJ1>scoreJ2))
        {
            cout << "on renvoie Truuue" << endl;
            return true;
        }
        else
            return false;
    }
    // Sinon on doit rajouter des cartes au tas du défenseur puis tester dans tous les cas possibles.
    else
    {
        for (int i=0;i<tailleMain;i++) //D'abord on teste les cartes des mains de J1 et J2
        {
            bool ajouter{ false };
            Carte *tasCourantJ1{new Carte[3]},*tasCourant_2_J1{new Carte[3]};
            Carte *tasCourantJ2{new Carte[3]}, *tasCourant_2_J2{new Carte[3]};
            copierTableau(tasSurBorneJ1, tasCourantJ1, 3);
            copierTableau(tasSurBorneJ1, tasCourant_2_J1, 3);
            copierTableau(tasSurBorneJ2, tasCourantJ2, 3);
            copierTableau(tasSurBorneJ2, tasCourant_2_J2, 3);
            /*
            cout << &tasCourantJ1 << " " << &tasSurBorneJ1 << endl;
            cout << *&tasCourantJ1 << " " << *&tasSurBorneJ1 << endl;
            cout << tasCourantJ1 << " " << tasSurBorneJ1 << endl;
            */
            if (numJoueur == 1 && estUneNouvelleCarte(tasCourantJ2, game::mainJ1[i])) // Si le joueur qui défend est 2, c'est à lui qu'il manque des cartes, donc à lui qu'il faut ajouter.
            {
                ajouterCarte(tasCourantJ2, game::mainJ1[i]);
                ajouter = true;
                if (testCombinaisons2(numBorne, numJoueur, tasCourantJ1, tasCourantJ2))
                    // S'il y a une combinaison induite qui est vraie, on renvoie vrai encore
                    // Avec la variable ajotuer, on ne réalise les tests qu'une fois que l'on a ajouter un nouvelle carte, pour éviter des boucles infinis.
                    return true;
            }
            else if (numJoueur == 1 && estUneNouvelleCarte(tasCourant_2_J2, game::mainJ2[i]))
            {
                ajouterCarte(tasCourant_2_J2, game::mainJ2[i]); // On teste chaque main, il faut une variable propre à chaque tentative, d'où tasCourant_2_J2.
                ajouter = true;
                if (testCombinaisons2(numBorne, numJoueur, tasCourantJ1, tasCourant_2_J2))
                    return true;
            }
            else if (numJoueur == 2 && estUneNouvelleCarte(tasCourantJ1, game::mainJ1[i]))
            {
                ajouterCarte(tasCourantJ1, game::mainJ1[i]);
                ajouter = true;
                if (testCombinaisons2(numBorne, numJoueur, tasCourantJ1, tasCourantJ2))
                    return true;
            }
            else if (numJoueur == 2 && estUneNouvelleCarte(tasCourant_2_J1, game::mainJ1[i]))
            {
                ajouterCarte(tasCourant_2_J1, game::mainJ1[i]);
                ajouter = true;
                if (testCombinaisons2(numBorne, numJoueur, tasCourant_2_J1, tasCourantJ2))
                    return true;
            }
            else if (!estUneNouvelleCarte(tasCourant_2_J1, game::mainJ1[i]) && !estUneNouvelleCarte(tasCourantJ1, game::mainJ1[i]) && !estUneNouvelleCarte(tasCourant_2_J2, game::mainJ2[i]) && !estUneNouvelleCarte(tasCourantJ2, game::mainJ1[i]))
                cout << "Pas de nouvelles cartes dans à prendre dans une main ce tour-ci ! #testCombinaisons2" << endl;
        }
        // Enfin on parcourt la pile de cartes non distribuées à l'aide d'un nouveau pointeur
        Chaine *current{&game::pile};
        while (current)
        {
            bool ajouter{ false };
            Carte *tasCourantJ1{new Carte[3]};
            Carte *tasCourantJ2{new Carte[3]};
            copierTableau(tasSurBorneJ1, tasCourantJ1, 3);
            copierTableau(tasSurBorneJ2, tasCourantJ2, 3);
            if (numJoueur == 1 && estUneNouvelleCarte(tasCourantJ2, current->carte))
            {
                ajouterCarte(tasCourantJ2, current->carte);
                ajouter = true;
            }
            else if (numJoueur == 2 && estUneNouvelleCarte(tasCourantJ1, current->carte))
            {
                ajouterCarte(tasCourantJ1, current->carte);
                ajouter = true;

            }
            else if (!ajouter)
            {
                cout << "Pas de nouvelles cartes issus de la pioche ce tour-la ! #testCombi2" << endl;
            }
            else
                cout << "Il y a un probleme dans testCombinaisons2 !!!" << endl;
            if (ajouter && testCombinaisons2(numBorne, numJoueur, tasCourantJ1, tasCourantJ2))
                return true;
            current=current -> suivant;
        }
        return false;
    }
}

/*
Cette fonction actualise la variable globale contenant les bornes d'un joueur et change la place de la borne prise sur le terrain.
*/
void prendreBorne(int numBorne, int numJoueur)
{
    if (numJoueur==1)
    {
        game::bornesJ1.push_back(numBorne);
        game::terrain[numBorne][0]=game::terrain[numBorne][4];
        game::terrain[numBorne][4].valeur=0;
        //cout << "On se trouve dans prendreBorne, bornes1 mesure " << game::bornesJ1.size() << " et bornes2 mesure " << game::bornesJ2.size() << endl;
    }
    else if (numJoueur==2)
    {
        game::bornesJ2.push_back(numBorne);
        game::terrain[numBorne][8]=game::terrain[numBorne][4];
        game::terrain[numBorne][4].valeur=0;
    }
    else
        cout << "Il y une erreur, un numero de joueur est mal defini !!! #prendreBorne" << endl;

}

/*
Cette fonction est appelée lorsqu'on demande à prendre une borne. Elle appelle les fonctions testCombinaisons1 et 2 selon si le joueur revendiquant la borne a 3 carte, la fonction prendreBorne
et la fonction testFinie.
*/
void revendiquer (int numBorne, int numJoueur)
{
    Carte tasSurBorneJ1[3];
    Carte tasSurBorneJ2[3];
    tasBorne(numBorne, 1, tasSurBorneJ1);
    tasBorne(numBorne, 2, tasSurBorneJ2);
    //cout << numJoueur << " " << testBorneRemplie(numBorne, numJoueur) << endl;
    if (!testBorneRemplie(numBorne, numJoueur))
        cout << "Vous n'avez pas 3 cartes sur la borne " << numBorne << ", vous ne pouvez pas la revendiquer." << endl;
    else if (testBorneRemplie(numBorne, numJoueur%2 +1))
    {
        int numJGagnant{-2};
        if (testCombinaisons1(numBorne, numJoueur, tasSurBorneJ1, tasSurBorneJ2))
            numJGagnant=numJoueur;
        else
            numJGagnant=numJoueur%2 +1;
        //cout << "On se trouve dans la premiere boucle else if, et numJGagnant vaut " << numJGagnant << " le testCombinaison1 a renvoye "<< testCombinaisons1(numBorne, numJoueur, tasSurBorneJ1, tasSurBorneJ2) << endl;
        if (numJGagnant==1)
        {
            cout << game::nomJ1 << " a gagne la borne " << numBorne << " !" << endl;
            prendreBorne(numBorne, numJGagnant);
        }
        else if (numJGagnant==2)
        {
            cout << game::nomJ2 << " a gagne la borne " << numBorne << " !" << endl;
            prendreBorne(numBorne, numJGagnant);
        }
        else
            cout << "Y a une erreur dans la revendiquation de la borne, le numero du joueur gagnant la revendication est mal defini, numJGagnant = "<< numJGagnant << " !!! #revendiquer" << endl;
        //A la fin, on vérifie que le joueur qui a acquis la borne n'a pas gagné la partie
        testFinie(numJGagnant);
    }
    else
    {
        if (!testCombinaisons2(numBorne, numJoueur, tasSurBorneJ1, tasSurBorneJ2)) // Si aucune combinaison ne peut sauver le joueur attaqué, il perd la borne.
        {
            cout << "Le joueur " << numJoueur << " a pris la borne " << numBorne << " !" << endl;
            prendreBorne(numBorne, numJoueur);
            testFinie(numJoueur);
        }
        else
        {
            cout << "Aucun joueur n'a pris la borne " << numBorne << "." << endl;
        }
    }
}


/*
Cette fonction retire une carte à un joueur, elle est appelée lorsqu'un joueur pose une certaine carte sur le terrain.
*/
void retirerCarteMain(int numCarte, int numJoueur)
{
    if (numJoueur==1)
    {
        if (numCarte==tailleMain-1) // tailleMain-1 est le dernier indice de la liste game::mainJ1, pas tailleMain !
            game::mainJ1[tailleMain-1].valeur=0;
        else
        {
            for (int i=numCarte;i<tailleMain-1;i++)
            {
                game::mainJ1[i]=game::mainJ1[i+1];
            }
            game::mainJ1[tailleMain-1].valeur=0;
        }
    }
    else if (numJoueur==2)
    {
        if (numCarte==tailleMain-1) // tailleMain-1 est le dernier indice de la liste game::mainJ1, pas tailleMain !
            game::mainJ2[tailleMain-1].valeur=0;
        else
        {
            for (int i=numCarte;i<tailleMain-1;i++)
            {
                game::mainJ2[i]=game::mainJ2[i+1];
            }
            game::mainJ2[tailleMain-1].valeur=0;
        }
    }
}

/*
Cette fonction parcourt la pile et renvoie faux si elle repère un doublon.
*/
bool testPile()
{
    Chaine *ptr1{&game::pile},*ptr2{&game::pile};
    int k{0};
    while (ptr1)
    {
        while (ptr2)
        {
            if (ptr1==ptr2)
            {
                k++;
                if (k>1)
                {
                    return false;
                }
            }
            ptr2= ptr2 -> suivant;
        }
        ptr1= ptr1 -> suivant;
    }
    return true;
}
