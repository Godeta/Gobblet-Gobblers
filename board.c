#include "board.h"
#include <stdlib.h>

void annuler_coup(board test,int joueur, int line, int column); //rajouté pour le bot, comme ça il peut annuler une action et tester de nombreuses possibilités
/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author Arnaud GODET
 */

/**
 * @brief The board of the game and it's functions
 */
struct board_s {
	// Le typedef est dans board.h 
size taille[9]; //9 cases de type taille
player joueur[9]; //9 cases de type joueur 
size memoryS [2] [9]; // matrice de 2 lignes car il peut y avoir 2 pièces sous une pièce et 9 colonnes pour chaque cases
player memoryP [2] [9];//pareil mais pour le joueur à qui appartient la pièce
};

board new_game(){ 
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));
	for (int i = 0; i <9; i++) { //initialise toutes les cases du nouveau plateau à 0
		new_board->taille[i] =0;
		new_board->joueur[i] =0;
		for (int j=0; j<2; j++) { //il peut y avoir 2 pièces en mémoire
		new_board->memoryS[j][i] =0;
		new_board->memoryP[j][i] =0; } //fin for j
	}
	// TODO: Insérer les traitements que vous voudriez faire.
	return new_board;
}

board copy_game(board original_game) {
board copy = new_game();
for (int i =0; i<9; i++) {//on récupère toutes la valeurs de original_game dans copy
copy->taille[i] = original_game->taille[i];
copy->joueur[i] = original_game->joueur[i];
for (int j=0; j<2; j++) { //il peut y avoir 2 pièces en mémoire
copy->memoryS[j][i] = original_game->memoryS[j][i];
copy->memoryP[j][i] = original_game->memoryP[j][i]; }//fin for j
}
return copy;
}

void destroy_game(board game){
	// freeing memory, necessary for memory allocated with malloc 
	free(game);
}

player get_place_holder (board game, int line, int column) {
	if (line <0 ||line >3 ||column<0 ||column>3 ) {return 0;} //test si la ligne et colonne sont des valeurs valides
else {
//ligne 0 va de 0 à 2, ligne 1 va de 3 à 5 et ligne 2 de 6 à 8 

//line*3+column car si ligne =0 et column = 1 alors on retourne le joueur à la case 1, si line=1 et column =2 alors on retourne le joueur à la case 5
return game->joueur[line*3+column]; 
}

}

size get_piece_size (board game, int line, int column) {
if (line <0 ||line >3 ||column<0 ||column>3 ) {return 0;} //test si la ligne et colonne sont des valeurs valides
else {	return game->taille[line*3+column]; }
}

player get_winner (board game) {
// 3 possibilités, avoir 3 pièces du même joueur sur une ligne horizontale, verticale ou une diagonale
player gagnant =0; //le vainqueur à retourner

//possibilité 1 : si les 3 pièces sont sur la même ligne horizontale
	for (int i =0;i<3;i++) { //pour i de 0 à 2
	if (gagnant==0) { //si il n'y a pas encore de gagnant
		if (get_place_holder(game,i,0) == get_place_holder(game,i,1) && get_place_holder(game,i,1) == get_place_holder(game,i,2)) { //exemple si i= 1, si les 3 valeurs sont égales alors toute la ligne 1 appartient au joueur
		gagnant = get_place_holder(game,i,1); //le gagnant est le joueur à qui appartient la case i
				}
	}
		} //fin du premier for pour la première possibilité

if (gagnant ==0) { //si la première possibilité ne donne pas de gagnant

	//possibilité 2 : //si les 3 pièces sont sur la même colonne
	for (int i=0; i<3; i++) { //pour i de 0 à 2
	if (gagnant ==0) {
		if (get_place_holder(game,0,i) == get_place_holder(game,1,i) && get_place_holder(game,1,i) == get_place_holder(game,2,i)) { //exemple si i= 1, si les 3 valeurs sont égales alors toute la colonne 1 appartient au joueur
			gagnant = get_place_holder(game,0,i); //le gagnant est le joueur à qui appartient la case i
					}
		}
	}
}

if (gagnant ==0) { //si les 2 premières possibilités ne donnent pas de gagnant

	//possibilité 3 : //si les 3 pièces sont sur la même diagonale
	//2 diagonales
	if (get_place_holder(game,0,0) == get_place_holder(game,1,1) && get_place_holder(game,1,1) == get_place_holder(game,2,2)) { 
		gagnant = get_place_holder(game,1,1); //le gagnant est le joueur à qui appartient le milieu de la diagonale
				}
}
if (gagnant ==0) {
	if (get_place_holder(game,0,2) == get_place_holder(game,1,1) && get_place_holder(game,1,1) == get_place_holder(game,2,0)) { 
		gagnant = get_place_holder(game,1,1); //
				}
}

	return gagnant;
}

int get_nb_piece_in_house (board game, player checked_player, size piece_size) {
	int nb =2; //nombre de pèces à retourner
	if (checked_player ==0 || checked_player>2) return 0;
	else if (piece_size<1 || piece_size >3) return 0;
	else
for (int i =0; i<9; i++) { //une boucle for qui vérifie chaque case 
if (game->joueur[i] == checked_player) { //si la case appartient au joueur recherché
if (game->taille[i] == piece_size) { //si la taille correspond à la taille recherchée
	nb -=1; //car il y a une pièce de moins pour chaque pièces présentent sur le plateau
			}
		}
		for (int j=1; j<3;j++) { //il peut y avoir 2 pièces en mémoire
if (game->memoryP[j][i] == checked_player) { //si la pièce en mémoire appartient au joueur recherché
if (game->memoryS[j][i] == piece_size) { //si la taille en mémoire correspond à la taille recherchée
	nb -=1; //car il y a une pièce de moins pour chaque pièces présentent sur le plateau
				}
			}
		} //fin de la boucle for j
	} //fin de la boucle for i

//test si la valeur donnée est cohérente donc entre 0 et 2
if (nb<0 || nb>2) {return 0;} 
else {
return nb; }
}

int place_piece (board game, player current_player, size piece_size, int line, int column) {
	//tests
if (get_nb_piece_in_house(game,current_player,piece_size)==0) {return 1;} //si il n'y a plus de pièce de cette taille dans la maison du joueur
else if (get_piece_size(game,line,column)>=piece_size) {return 2;} //si la pièce à placer est plus petite ou de même taille que la pièce présente sur la case
else if (line <0 ||line >2 ||column<0 ||column>2) {return 3;} //ligne ou colonne incorrectes

else {//placer la pièce
		if (game->memoryP[2][line*3+column] !=0) { //si il y a déjà une pièce sur la deuxième ligne de la matrice mémoire player
			game->memoryP[1][line*3+column] = game->memoryP[2][line*3+column]; //on met en mémoire le joueur à qui appartenait la pièce en mémoire 2
			game->memoryS[1][line*3+column] = game->memoryS[2][line*3+column]; //on met en mémoire la taille de la pièce qui était présente en mémoire 2
		}
 //on met la pièce sur la case en mémoire dans la deuxième ligne
			game->memoryP[2][line*3+column] = get_place_holder(game,line,column); //on met en mémoire le joueur à qui appartenait la case sur laquelle on place notre pièce
			game->memoryS[2][line*3+column] = get_piece_size(game,line,column); //on met en mémoire la taille de la pièce qui était présente sur cette case
		

	game->joueur[line*3+column] = current_player;
	game->taille[line*3+column] = piece_size; }//fin else
return 0;
}

int move_piece (board game, int source_line, int source_column, int target_line, int target_column) { //il faut supprimer la pièce après l'avoir déplacée !!!
//Les tests
if (get_place_holder(game,source_line,source_column) ==0) {return 1;} //si il n'y a pas de pièce à l'emplacement initial
else if(get_piece_size(game,source_line,source_column)<=get_piece_size(game,target_line,target_column)) {return 2;} //si la pièce à déplacer est plus petite
else if(target_line <0 ||target_line >2 ||target_column<0 ||target_column>2) {return 3;}//la ligne ou colonne entrée est incorrecte
else { //le déplacement

//on met en mémoire la pièce sur la case de destination
		if (game->memoryP[2][target_line*3+target_column] !=0) { //si il y a déjà une pièce sur la deuxième ligne de la matrice mémoire player
			game->memoryP[1][target_line*3+target_column] = game->memoryP[2][target_line*3+target_column]; //on met en mémoire le joueur à qui appartenait la case sur laquelle on place notre pièce
			game->memoryS[1][target_line*3+target_column] = game->memoryS[2][target_line*3+target_column]; //on met en mémoire la taille de la pièce qui était présente sur cette case
		}
		
		 //on met la pièce sur la case en mémoire dans la deuxième ligne
			game->memoryP[2][target_line*3+target_column] = get_place_holder(game,target_line,target_column); //on met en mémoire le joueur à qui appartenait la case sur laquelle on place notre pièce
			game->memoryS[2][target_line*3+target_column] = get_piece_size(game,target_line,target_column); //on met en mémoire la taille de la pièce qui était présente sur cette case
		

game->joueur[target_line*3+target_column] = game->joueur[source_line*3+source_column] ;//la case de destination récupère la valeur de la case source
game->taille[target_line*3+target_column] = game->taille[source_line*3+source_column] ;

//la case source prend en valeur la pièce présente en mémoire
game->joueur[source_line*3+source_column] = game->memoryP[2][source_line*3+source_column] ;
game->taille[source_line*3+source_column] = game->memoryS[2][source_line*3+source_column] ;
//la case mémoire 2 prend la valeur de la case mémoire 1, comme ça si il y avait deux pièces en mémoires après le déplacement, la case mémoire 2 devient la case normale et la case mémoire 1 devient la case mémoire 2
game->memoryS[2][source_line*3+source_column] = game->memoryS[1][source_line*3+source_column] ;
game->memoryP[2][source_line*3+source_column] = game->memoryP[1][source_line*3+source_column] ; //problème la case 1 n'est jamais remplie
//printf("\nValeur case mémoire 1 %d et case mémoire 2 %d",game->memoryS[1][source_line*3+source_column], game->memoryS[2][source_line*3+source_column] );
game->memoryP[1][source_line*3+source_column] =0;
game->memoryS[1][source_line*3+source_column] =0 ; //réinitialisation à 0 de la valeur en mémoire 1 après avoir passée la valeur en mémoire 2

return 0; }
}

player next_player (player current_player) {

	return current_player %2 +1; //si c'est 0 alors ça devient le joueur 1, si c'est 1 alors joueur 2 et si c'est 2 alors cela donne 1
}

void annuler_coup(board test,int joueur, int line, int column)
{
  test->taille[line*3+column] = 0; //je change la valeur de test de type board défini selon board.c 
  test->joueur[line*3+column] = 0;
}