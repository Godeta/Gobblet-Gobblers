#include <stdio.h>
#include <stdlib.h> //pour pleins de fonctions nottament system clear
#include <time.h>//pour pouvoir récupérer le temps de la machine et l'utiliser pour génerer des nombres random
#include "bot.h"

void bot (player joueur, int mode, board test) {
//random initialisé dans projetGG srand
int type, line, column; //type pour la taille de la pièce, line et column pour l'emplacement de la pièce

    if (mode ==1) { //bot facile, joue aléatoirement
printf("\n Voici le bot facile !!!");
//bot aléatoire
do {
type = rand () %3+1; //1,2,3 ou 4 
}
while (get_nb_piece_in_house(test, joueur, type)<=0); //pour qu'il n'essaye pas de placer des pièces d'une taille indisponible
do {
line = rand () %3; column = rand () %3;
}
while (get_piece_size(test, line, column) > type); //pour qu'il n'essaye pas de placer une pièce si la case contient déjà une pièce plus grande
place_piece(test, joueur, type, line ,column); 




//place_piece(test, joueur, type, line ,column);
//move_piece(test, line, column, line_dest, column_dest);

    }

    else { //bot difficile, utilise l'algorithme min-max
printf("\n Voici le bot difficile !!!");

calcIA(test, 2, joueur); //pour l'instant ne fonctionne pas bien

    }
    
}

int calcScore(int cntpion, int cntjoueur)
{
    //ne prend pas encore en compte les différentes tailles
//On regarde le nombre de pions
switch(cntpion)
    {
    case 1: //on attribue une valeur pour un pion
        return 10*cntjoueur;
    case 2: //on attribue une valeur plus grande pour deux pions cotes à cotes
        return 30*cntjoueur;
    default:
        return 0;
    }
}

int evalue(board test, player joueur) //fonction principale de l'ia qui évalue le jeu
{
    int score=0;

    int cntjoueur, cntpion; //contjoueur donne le score du joueur calculé, cntpion compte le nombre de pions d'affilés
    int i,j;
    int vainqueur = get_winner(test);

    //Si le jeu est fini
    if(vainqueur!=0)
        {
	    //Si l'IA a gagné, on retourne 1000 - le nombre de pions, cela permet de choisir la victoire la plus rapide si l'IA voit 2 victoires possibles
        if(vainqueur == joueur)
            {
            return 1000-comptePions(test);
            }
	    else
		    {
		    //Si l'IA a perdu, on retourne -1000 + le nombre de pions
	        return -1000+comptePions(test);
		    }
        }

   //on initialise le nombre de pions et le nombre de pions du joueur
    cntpion=0;
    cntjoueur=0;
     //Diagonale 1
    //On regarde chaque case
    for(i=0;i<3; i++) //diagonale donc (0,0), (1,1), (2,2)
        {
	    //Si la case n'est pas vide
        if(get_place_holder(test,i,i)!=0)
	        {
	        //On incrémente d'un pion
	        cntpion++;
            //Si c'est le même type du joueur courant
            if(get_place_holder(test,i,i)==joueur)
      		    //On incrémente le compteur
                cntjoueur++;
            else
       	        //On décrémente le compteur
                cntjoueur--;
            }
        }

    //On ajoute au score cette nouvelle participation
    score += calcScore(cntpion,cntjoueur);

    //Diagonale 2
    cntpion=0;
    cntjoueur=0;
    for(i=0;i<3; i++) //(0,2) (1,1) (2,0)
        {
        if(get_place_holder(test,i,2-i) !=0) //la case n'est pas vide
	    {
            cntpion++;
            if(get_place_holder(test,i,2-i)==joueur)
                cntjoueur++;
            else
                cntjoueur--;
            }
        }

    score += calcScore(cntpion,cntjoueur);

    //Lignes
    for(i=0;i<3;i++)
        {
        cntpion = 0;
        cntjoueur = 0;
        for(j=0;j<3;j++)
            {
            if(get_place_holder(test,i,j)!=0)
                {
                cntpion++;
                if(get_place_holder(test,i,j)==joueur)
                    cntjoueur++;
                else
                    cntjoueur--;
                }
            }

        score += calcScore(cntpion,cntjoueur);
        }

    //Colonnes
    for(i=0;i<3;i++)
        {
        cntpion = 0;
        cntjoueur = 0;
        for(j=0;j<3;j++)
            {
            if(get_place_holder(test,j,i)!=0)
                {
                cntpion++;
                if(get_place_holder(test,j,i)==joueur)
                    cntjoueur++;
                else
                    cntjoueur--;
                }
            }

        score += calcScore(cntpion,cntjoueur);
        }

    return score;
}

int comptePions(board test) //compte le nombre de pions sur le plateau
{
    int i,j,cnt=16;
    for(i=1;i<3;i++) //pour les deux joueurs
        for(j=1;j<4;j++) //taille de 1 à 4
            cnt -= get_nb_piece_in_house (test,i,j); //16 - les pions encore dans la maison
    return cnt;
}

void calcIA(board test, int prof, player joueur) //fonction principale, calcule selon une certaine profondeur et effectue des actions
{
    int i,j,tmp;
    int max = MINEVAL;
    int maxi=-1,maxj=-1; int maxt =1;

    

    //Si la profondeur est nulle ou la partie est finie on ne fait pas le calcul
    if((prof!=0)||get_winner(test)==0)
        {
        //On parcourt les cases du morpion
        for(i=0;i<3; i++)
            for(j=0;j<3;j++) {
                for (int tail =1; tail<4; tail++) {
                //Si la case est vide
                if(get_place_holder(test,i,j)==0)
                    {
                    //On simule qu'on joue cette case
                    place_piece(test, joueur, tail, i ,j); 
                    //On appelle la fonction calcMin pour lancer l'IA
                    tmp = calcMin(test, prof-1, joueur);
                    //Si ce score est plus grand
                    if(tmp>max)
                        {
                        //On le choisit
                        max = tmp;
                        maxi = i;
                        maxj = j;
                        maxt = tail;
                        }
                    //On annule le coup
                    annuler_coup(test, joueur, i, j);
                    }
                }
            }
        }
    //On jouera le coup maximal
    place_piece(test, joueur, maxt, maxi ,maxj);
}

int calcMin(board test, int prof, player joueur)
{
    int i,j,tmp;
    int min = MAXEVAL;

    //Si on est à la profondeur voulue, on retourne l'évaluation
    if(prof==0)
        return evalue(test, joueur);

    //Si la partie est finie, on retourne l'évaluation de jeu
    if(get_winner(test) !=0)
        return evalue(test, joueur);

    //On parcourt le plateau de jeu et on le joue si la case est vide
    for(i=0;i<3; i++)
        for(j=0;j<3;j++)
            {
                for (int tail=1; tail<4; tail++) {
            if(get_place_holder(test,i,j)==0)
                {
                //On joue le coup
                place_piece(test, joueur, tail, i ,j);
                tmp = calcMax(test, prof-1, joueur);
                if(tmp<min)
                    {
                    min = tmp;
                    }
                //On annule le coup
                annuler_coup(test, joueur, i, j);
                }
            } }
    return min;
}

int calcMax(board test, int prof, player joueur)
{
    int i,j,tmp;
    int max = MINEVAL;

    //Si on est à la profondeur voulue, on retourne l'évaluation
    if(prof==0)
        return evalue(test, joueur);

    //Si la partie est finie, on retourne l'évaluation de jeu
    if(get_winner(test) !=0)
        return evalue(test, joueur);

    //On parcourt le plateau de jeu et on le joue si la case est vide
    for(i=0;i<3; i++)
        for(j=0;j<3;j++)
            {
                for (int tail=1;tail<4; tail++) {
            if(get_place_holder(test,i,j)==0)
                {
                //On joue le coup
                place_piece(test, joueur, tail, i ,j);
                tmp = calcMin(test, prof-1, joueur);
                if(tmp>max)
                    {
                    max = tmp;
                    }
                //On annule le coup
                annuler_coup(test, joueur, i, j);
                }
            } }
    return max;
}



/*compteur_noeuds = 0;
	  eval = minimax(test,joueur, &i, &j,&compteur_noeuds);
	  printf("%d noeuds\n", compteur_noeuds);
	  printf("mon evaluation : ");
	  if (eval == 1)
	    printf("x gagne\n");
	  else if (eval == -1)
	    printf("o gagne\n");
	  else printf("partie nulle\n");*/

/*
int minimax(board test, int joueur, int *mi, int *mj, int *compteur_noeuds)
{
  int i, j, tail; //ligne, colonne, taille
  int eval, e;
  int mi2, mj2; //variables utilisées pour la récursivité de la fonction
  
  compteur_noeuds++;

  if (joueur == ROND) {
    // on cherche tous les coups pour ROND et on renvoie le minimum
      // des evaluations aux noeuds fils 
    eval = INFINI;		// et non pas 1, sinon il pourrait 
				   //ne pas y avoir de coup renvoye. 
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
            for (tail=1; tail<4; tail++) {
	if (get_place_holder(test, i,j) ==VIDE) {
        place_piece(test, joueur, tail, i ,j);
        if (get_winner(test)==ROND) {
            *mi = i; *mj = j;
            eval = -1;
        }
        else {
            e = minimax(test, CROIX, &mi2, &mj2, compteur_noeuds);
            if (e < eval) {
            *mi = i; *mj = j;
            eval = e;
            }
        }
        annuler_coup(test, ROND, i, j);
	}
            } } }
    return eval;
  }
  else {
    //on cherche tous les coups pour CROIX et on renvoie le maximum
       //des evaluations aux noeuds fils 
    eval = -INFINI;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
            for (tail=1; tail<4; tail++) {
	if (get_place_holder(test, i,j) ==VIDE) {
	    place_piece(test, joueur, tail, i ,j);
            if (get_winner(test)==CROIX) {
            *mi = i; *mj = j;
            eval = 1;
            }
            else {
            e = minimax(test, ROND, &mi2, &mj2, compteur_noeuds);
            if (e > eval) {
            *mi = i; *mj = j;
            eval = e;
            }
            }
            annuler_coup(test, CROIX, i, j);
	}
            } } }
    return eval;
  }
}*/