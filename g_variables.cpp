#include "structures.h"
#include "fonctions.h"

// Variables globales du programme:
namespace game
{
    const double pi{3.14};
    int fini{0};
    VectCartes mainJ1, mainJ2;
    TabCartes terrain;
    Chaine pile{creerPile()};
    std::string nomJ1, nomJ2;
    std::vector<int> bornesJ1; // 5 est le nombre maximal de bornes qu'un joueur peut avoir,
    std::vector<int> bornesJ2; // au bout de 5 bornes on gagne, quoiqu'il arrive.
    int joueurDerniereCarte[9]; // On consid�re un tableau de taille 9 contenant le num�ro du dernier joueur � avoir pos� une carte dans la borne i
}



