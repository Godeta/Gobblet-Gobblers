# Indique les dépendances :
projetGG: menu.o bot.o jeu.o projetGG.o board.o
	gcc menu.o bot.o jeu.o projetGG.o board.o -o projetGG
test : libtest.a board.o #si l'on fait "make test" on peut constater que board.o est conforme selon les tests efectués
	gcc libtest.a board.o -o runtest
	./runtest

# Compile les dépendances :
bot.o : bot.c
	gcc -c -Wall bot.c
jeu.o : jeu.c
	gcc -c -Wall jeu.c
menu.o : menu.c
	gcc -c -Wall menu.c
board.o : board.c
	gcc -c -Wall board.c
projetGG.o : projetGG.c
	gcc -c -Wall projetGG.c #si on déclenche juste cette fonction commentaire s'affiche

clean : #chmod n'est plus nécessaire maintenant que j'ai codé board.c
	#chmod board.o -w #interdit l'ecriture et donc la suppresion de board.o
	rm *.o #supprime tous les fichiers binaires non executables créés au cours de la compilation
	#chmod board.o +w #redonne les droits d'ecriture sur board.o
	#-v ajoute un commentaire


#En cas d'erreur "makefile ... missing separator", le nombre après makefile indique la ligne et le separateur manquant et tab
#les noms projetGG, clean etc... sont des fonctions dont on peu preciser le nom pour uniquement déclencher la fonction voulue lors de la commande