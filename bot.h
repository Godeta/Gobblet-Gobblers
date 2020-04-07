#include "board.h" //pour utiliser les fonctions getplaceholder(), getpiecesize()... et les types board, player...
#include "jeu.h" //pour être relié à jeu.c

#define VIDE 0
#define CROIX 1
#define ROND 2
#define AUTRE_JOUEUR(joueur) (3-(joueur))

#define INFINI 2
/* un entier plus grand que toutes les valeurs possibles pour l'evaluation */
#define MINEVAL -100000
#define MAXEVAL 100000

void bot (player joueur, int mode, board test);
    //Fonction qui calcule le prochain coup*/
    void calcIA(board test, int prof, player joueur);

    //Fonctions pour le calcul
    int calcMin(board test, int prof, player joueur);
    int calcMax(board test, int prof, player joueur);
        
    //Fonction qui évalue le jeu
    int calcScore(int cntpion, int cntjoueur);
    int evalue(board test, player joueur);
	int comptePions(board test);

void annuler_coup(board test,int joueur, int line, int column); //dans le board.c