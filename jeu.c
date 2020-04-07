#include <stdio.h>
#include <stdlib.h> //pour pleins de fonctions nottament system clear
#include "board.h" //pour utiliser les fonctions de board.c
#include "interface.h" //pour mettre les prototypes de mes fonctions
#include <time.h>//pour pouvoir récupérer le temps de la machine et l'utiliser pour génerer des nombres random
#include "jeu.h"
#include <unistd.h> //pour utiliser sleep()

# include <termios.h>

/*int main() {
    int select =1;
jeu(&select);

return 0;
}*/

void jeu(int *select) {
    printf("\n");
    system("clear"); //pour enlever le menu
    printf(RED BWHITE"PRESSEZ 0 et APPUYEZ sur ENTRER pour commencer"RESET);
        int mode =12;
board test = new_game(); //création d'un type board appelé test
player joueur =0; //objet joueur de type player, 3 valeurs possibles : no_player, player1, player 2

    while (*select ==1) { //valeur issue de menu indiquant que l'on a choisie l'option jouer
//board test1 = copy_game (test); //création d'une copie appelée test1 à chaque tour ce qui permet d'annuler une action passée
//destroy_game(test1);
if (mode ==12) {
    if (joueur ==0) printf(BLACK);
    else {printf(YELLOW);}
    printf("Choisissez le mode de jeu : 0 pour 2 joueurs, 1 pour jouer contre un bot facile, 2 contre un bot fort et 3 voir un affrontement entre 2 bots" RESET);
    scanf("%d", &mode);
}
if (mode ==0) {
action_choix(test, joueur, &mode); //demande si on souhaite ajouter ou déplacer une pièce et agit en conséquence
}
else if (mode ==1 || mode ==2) {
    if (joueur ==2) { //joueur 2 est le bot
    bot(joueur, mode, test); }
    else {action_choix(test, joueur, &mode);
    printf(YELLOW "Au tour du bot de jouer ! "RESET); } //joueur 1 est vous
}
else if (mode ==3) {bot(joueur, mode, test);}
//while ( getchar() != '\n'); //toujours vider le buffer après un scanf si on veut en réutiliser un autre !!! Si on vide le buffer avant cela nous demande 2 fois d'entrer notre nombre


joueur = next_player(joueur); //joueur suivant, ne pas oublier joueur = sinon la valeur de joueur ne change pas
tour (test, joueur); //affiche "au tour du joueur..."
if (mode ==1 || mode ==2) { printf(YELLOW "A votre tour de jouer ! Entrez un nombre pour jouer. "RESET);}
else if (mode ==3) {printf(YELLOW"Entrez un nombre pour continuer"RESET);}
/*printf("Continuer ? 0 pour non et 1 pour oui\n");
scanf("%d", select); //si non alors select = 0 donc retour au menu
while ( getchar() != '\n');*/
while ( getchar() != '\n'); //vider le buffer

if (get_winner(test) ==1) {//si le joueur 1 gagne
printf(RED"Victoire du joueur 1 !!!");
sleep(3);
system("clear");
destroy_game(test); //libérer la mémoire
printf(YELLOW "Appuyez sur ENTRER pour reprendre depuis le menu" RESET);
*select =0;
}
else if (get_winner(test)==2) {//si le joueur 2 gagne
printf(RED"Victoire du joueur 2 !!!");
sleep(3);
system("clear");
destroy_game(test); //libérer la mémoire
printf(YELLOW "Appuyez sur ENTRER pour reprendre depuis le menu" RESET);
*select =0;
}

                } //fin select = 1

    *select =0; //retour au menu
}

void plateau(int cote, board test){ //carré rempli de 6 lignes et 3 colonnes mais il y a 3 cases vides sur 3 colonnes donc de quoi mettre 9 pièces
printf(MAGENTA" colonnes :  0       1       2\n"RESET);
for (int i =0; i<=cote*2; i++) { //cote *2 car une ligne sur deux est simplement constituée de ligne séparatrice donc il faut 2 * plus de ligne pour avec 3 cases 
printf("         "); //marge avant le plateau
    for (int j=0; j<=cote; j++){ //nombre de colonnes
        
        
        if (j==cote) { //pour la dernière colonne uniquement !
            if (i%2 ==0) { //si i est pair
            printf("+");
        }
        else { //sinon, lorsque i est impair
            printf("|");

            if (i ==1) { //pour la deuxième ligne
                printf(MAGENTA"    ligne 0"RESET); 
                printf("    Contenu des maisons :");
            }
            if (i== 3) {// joueur1
            printf(MAGENTA"    ligne 1    "RESET);
            printf (BLUE); 
            for (int i=0; i<get_nb_piece_in_house(test,1,1); i++) { //récupère le nombre de petites pièces du joueur 1
            printf("°");} printf(" ");
            for (int i=0; i<get_nb_piece_in_house(test,1,2); i++) { //nb pièces moyennes
            printf("o");} printf(" ");
            for (int i=0; i<get_nb_piece_in_house(test,1,3); i++) { //nb pièces grandes
            printf("O");} printf(" "); printf(RESET);
            }
            if (i ==5) {// joueur 2
            printf(MAGENTA"    ligne 2    "RESET);
                printf (GREEN);
                 for (int i=0; i<get_nb_piece_in_house(test,2,1); i++) { //récupère le nombre de petites pièces du joueur 1, 2 car c'est le joueur 2 et 1 pour la taille 
            printf("x");} printf(" ");
            for (int i=0; i<get_nb_piece_in_house(test,2,2); i++) { //nb pièces moyennes
            printf("X");} printf(" ");
            for (int i=0; i<get_nb_piece_in_house(test,2,3); i++) { //nb pièces grandes
            printf("#");} printf(" "); printf(RESET);
                    }
                } //fin i impair
            } //fin j = cote, dernière colonne

        
        else { //pour le reste du plateau

            if (i%2 ==0) { //si i est pair
                printf("+---+---");
            }
            else { //sinon
                printf("|   ");
                    //i /2 car dans le plateau affiché il y a 6 lignes au lieu de 3
                    pieces(get_piece_size(test, i/2, j), get_place_holder(test, i/2, j)); //fonction pieces pour afficher une pièce avec en paramètre la taille de la pièce et le joueur

                    printf("   ");
                    }
                    } //fin pour le reste du plateau
        } //fin de la boucle for j
printf("\n");
    } //fin de la boucle for i
}

void pieces(size size, player joueur) { //prend size retourne une pièce affichée correspondant (none,small,middle,big)

switch (joueur) {
case 0: //aucun joueur donc pas de pièce
      printf(RESET); //pour que l'espace ne soit pas coloré
      printf(" ");//instruction : afficher un espace
      break;

case 1: //joueur 1
printf(BLUE);
switch (size) {
    case 0: break; //impossible donc je le laisse vide pour arrêter le warning
             case 1: //small
                printf("°");
                break;
             case 2: //medium
                printf("o");
                break;
             case 3: //big
                printf("O");
                break;
            }
break;

case 2: //joueur 2
printf(GREEN);
switch (size) {
    case 0: break;
             case 1: //small
                printf("x");
                break;
             case 2: //medium
                printf("X");
                break;
             case 3: //big
                printf("#");
                break;
            }
break;
}
printf(RESET); //enlever la couleur pour les prochains        

}


void action_choix (board test, player joueur, int *mode) {
    int action= 0,line=0, column=0, type=1; //action pour savoir si on déplace ou ajoute une pièce, ligne et colonne où l'on ajoute la pièce, le type de pièce à ajouter
    int line_dest =0, column_dest =0; //si l'on a choisi de déplacer une pièce, ligne et colonnes de destination, initialisé à 0 pour que saisie_valid trouve cela correct
    int valide =1; //pour la vérification de la saisie
    //  size; //size objet de type size, 4 valeurs possibles : none, small, medium, big

    while (valide!=0) {
    printf("Voulez vous ajouter (0) ou déplacer (1) une pièce ? (3 pour changer de mode) ");
scanf("%d", &action);
if(action ==0) { //ajouter
printf("Sur qu'elle ligne voulez vous jouer ? ");
scanf("%d", &line);
printf("Sur qu'elle colonne voulez vous jouer ? ");
scanf("%d", &column);
printf("Qu'elle taille de pièce voulez-vous jouer ?\n(1: petit, 2:moyen, 3:grand) ");
scanf("%d", &type);

saisie_valid(action, type, line, column, line_dest, column_dest, &valide, joueur, test);
place_piece(test, joueur, type, line ,column);  
        }//fin de ajouter

else if (action ==1) { //deplacer
printf("Qu'elle est la ligne de la pièce a déplacer ? ");
scanf("%d", &line);
printf("Qu'elle est la colonne de la pièce a déplacer ? ");
scanf("%d", &column);

printf("Qu'elle est la ligne de destination ? ");
scanf("%d", &line_dest);
printf("Qu'elle est la colonne de destination ? ");
scanf("%d", &column_dest);

saisie_valid(action, type, line, column, line_dest, column_dest, &valide, joueur, test);
move_piece(test, line, column, line_dest, column_dest);
        }//fin de deplacer

else if(action ==3) {printf("Choisissez le mode de jeu : "BLUE "(0) pour 2 joueurs, "GREEN "(1) pour jouer contre un bot facile," RED" (2) contre un bot fort" YELLOW " et (3) voir un affrontement entre 2 bots"RESET);
    scanf("%d", mode);
    valide =0;}
//saisie_valid(action, type, line, column, line_dest, column_dest, &valide, joueur, test);
    }//fin while valide !=0
}

void tour (board test, player joueur) {
    if (joueur ==1) {//tour de joueur 1
system("clear");
printf("\n Au tour du "); printf(BLUE); printf("joueur 1 !"); printf(RESET); printf("\n");
plateau(3, test);

}

if (joueur ==2) { //si tour est impair alors au tour de joueur 2
system("clear"); //pareil que cls sur windows
printf("\n Au tour du "); printf(GREEN); printf("joueur 2 !"); printf(RESET); printf("\n");
plateau(3, test);
}
}

void saisie_valid(int action, int type, int line, int column, int line_dest, int column_dest, int *valide, int joueur, board test) {//vérifie les valeurs saisies et indique ce qui ne va pas en cas d'erreur

*valide = 0;

if (action <0 || action >1) { //vérifie que l'on ai bien choisi 0 ou 1 pour l'action
printf(RED"\nAttention pour l'action veuillez entrer 0 (pour ajouter) ou 1 (pour déplacer) !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (type <1 || type >3) {//vérifie que type est égal à 1, 2 ou 3
printf(RED"\nAttention veuillez entrer 1, 2 ou 3 pour la taille de la pièce !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (column<0 ||column>2) { //vérifie que column est compris entre 0 et 2
printf(RED"\nAttention la colonne est comprise entre 0 et 2 !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (column_dest<0 ||column_dest>2) { //vérifie que column_dest est compris entre 0 et 2
printf(RED"\nAttention la colonne de destination est comprise entre 0 et 2 !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (line<0 ||line>2) { //vérifie que line est compris entre 0 et 2
printf(RED"\nAttention la ligne est comprise entre 0 et 2 !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (line_dest<0 ||line_dest>2) { //vérifie que line_dest est compris entre 0 et 2
printf(RED"\nAttention la ligne de destination est comprise entre 0 et 2 !\n");
*valide = 1; //pas valide, la boucle recommence
}

if (action ==1 && joueur != get_place_holder(test,line,column)) { //pour éviter qu'un joueur déplace la pièce d'un autre
printf(RED"\nAttention la pièce que vous essayez de déplacer ne vous appartient pas !\n");
*valide = 1; //pas valide, la boucle recommence
}
if (action ==0 && type < get_piece_size(test,line,column)) { // si on tente de placer une pièce sur une autre plus grosse
    printf(RED"\nImpossible de placer votre pièce sur une pièce de taille supérieure !\n");
*valide = 1; //pas valide, la boucle recommence
}

printf(RESET); //pour éviter que les textes après la vérification ne soient en rouge
}
