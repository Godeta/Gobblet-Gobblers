//fonctions de jeu.c

void plateau(int cote, board test); //carré rempli de lignes et colonnes d'étoiles sauf à l'intérieur des espaces
void pieces(size size, player joueur); //permet l'affichage d'une pièce en fonction de sa taille et du joueur
void action_choix (board test, player joueur, int *mode);//demande si on souhaite ajouter ou déplacer une pièce et agit en conséquence
void tour (board test, player joueur); //affiche "au tour de..."
void saisie_valid(int action, int type, int line, int column, int line_dest, int column_dest, int *valide, int joueur, board test); //vérifie que toutes les valeurs entrées sont cohérentes

void bot(player joueur, int mode, board test);