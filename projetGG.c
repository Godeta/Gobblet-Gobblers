#include <stdio.h>
#include <stdlib.h> //pour pleins de fonctions nottament system clear

#include <time.h>//pour pouvoir récupérer le temps de la machine et l'utiliser pour génerer des nombres random
#include <unistd.h> //permet d'utiliser sleep()

//pour remplacer conio.h qui permet de détecter les entrées clavier sans demander d'appuyer sur entrer avec getch()
# include <termios.h> //contient les définitions utilisées par les interfaces Input et Output du terminal pour plus de détails : https://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html

#include "interface.h"//contient les prototypes des fonctions et plusieurs constantes nottament pour les couleurs

int main() {
    srand(time(NULL));   // Initialisation à faire une seule fois 
    
    menu(); //jeu est déjà dans menu
    /*menu fonctionne ainsi :
 ->    variable select commence à 0
 ->    déclenchement du titre puis d'un menu où l'on peut naviguer à l'aide des flèches directionnelles
 ->    si l'on appuit sur ENTRER cela déclenche les actions liées à l'emplacement du menu sur lequel nous sommes
 ->    la variable select prend une autre valeur le temps que toutes les actions soient effectuées par exemple :
 ->    si on appuie sur ENTRER lorsque l'on est sur "options" select =6, plusieurs actions sont effectuées et à la fin
 ->    select reprend la valeur 0 pour que l'on retourne au menu
 ->    Dans le cas de jeu, les actions effectuées se situent directement dans "jeu.c"
 ->
 ->    La navigation s'effectue à l'aide des fonctions "void deplacement", "void affichage" et du contenu de menu lorsque select =0
    */
    printf("Vous êtes sorti du jeu lol");

    return 0;
}