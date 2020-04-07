#include <stdio.h>
#include <stdlib.h> //pour pleins de fonctions nottament system clear
#include <time.h>//pour pouvoir récupérer le temps de la machine et l'utiliser pour génerer des nombres random
#include <unistd.h> //permet d'utiliser sleep()
# include <termios.h> //pour remplacer conio.h qui permet de détecter les entrées clavier sans demander d'appuyer sur entrer
#include "interface.h"
#include "menu.h"

/*int main () {
srand(time(NULL));   // Initialisation à faire une seule fois 
 menu();
return 0;
}*/

void menu() {
int run=0;
int  select=0, max=4; //turn pour définir les tours des joueurs, select pour que le menu tourne en boucle et max pour définir le nombre max de mots
    int c, d, v; //variables prenant la touche entrée
    int couleur =0; //applique la couleur sur le mot en fonction des flèches
    int fond =0; //couleur de fond du texte du menu lorsqu l'on se déplace avec les flèches
    char tab [4] [20] = {"Jouer", "Regles", "Credits", "Options"}; //tableau, 4 mots, 20 caractères max
    printf("Pour profiter de la meilleure experience possible il est recommandé d'aggrandir votre terminal");
    sleep(3);
while(run ==0) {
  titre3();
  printf("\n \nAppuyez sur une fleche directionelle pour vous deplacer dans le menu et sur ENTRER puis une flèche directionelle pour valider votre choix \n \
  Pour commencer : APPUYEZ SUR UNE FLECHE !");  
do {

      
c = getch(); //c prends la valeur de ce que le clavier a détecté, ce n'est pas l'entrée principale comme getchar pas besoin de faire "Entrer" 
d = getch();
v = getch();
//printf("%d  %d  %d", c, d, v);
if ((c ==27 && d ==91) || (d==27 && v==91) || (v==27 &&c==91)) { //si on a appuyé sur une flèche, donc commence par 27 et 91
    //65 = flèche du haut, 66 = flèche du bas, 67 = flèche de droite, 68 = flèche de gauche
//printf("\n%d", v);

couleur = deplacement(c, max, couleur); //3 fois car si jamais on appuis sur une autre touche, a ou ENTRER par exemple, les déplacements fonctionnent comme même correctement
couleur = deplacement(d, max, couleur);
couleur = deplacement(v, max, couleur);
//printf("La couleur est %d", couleur);

 if (c ==10 || d==10 ||v ==10) {//si on a appuyé sur entrée
switch (couleur) {
                case 0: //Jouer
                select =1;     //Lance le jeu et quitte le menu
                break;
                case 1: //Règles
                select = 5; //Affiche les règles du jeu
                break;
                case 2: //Credits
                credits(); //credits s'affichent, entrer pour quitter
                break;
                case 3: //Options
                select =6; //Ouvre les options
                break;
}
        }
                }
                else if (c ==10 || d==10 ||v ==10) {//si on a appuyé sur entrée
switch (couleur) {
                case 0: //Jouer
                select =1;     //Lance le jeu et quitte le menu
                break;
                case 1: //Règles
                select = 5; //Affiche les règles du jeu
                break;
                case 2: //Credits
                credits(); //credits s'affichent, entrer pour quitter
                break;
                case 3: //Options
                select =6; //Ouvre les options
                break;
}
        }
else {c =0; d=0; v=0;} //sinon on reset les valeurs
     system("clear");

    apparence(v,couleur,tab, max, fond);
//printf("%d",deplacement(c,d, couleur, col2, max));
} // fin do

while (select==0);

if (select ==1) {
    jeu(&select); //voir jeu.c
    system("clear"); //pour enlever le menu
    viderBuffer();
}

if (select ==5) {// Règles du jeu
printf("TEST\n");
system("clear");
//printf("%d\n", select);
printf(MAGENTA);
printf("                 ____                    ___\n");
printf("                /\\  _`\\                 /\\_ \\\n");
printf("                \\ \\ \\L\\ \\     __     __ \\//\\ \\      __    ____\n");
printf("                 \\ \\ ,  /   /'__`\\ /'_ `\\ \\ \\ \\   /'__`\\ /',__\\\n");
printf("                  \\ \\ \\\\ \\ /\\  __//\\ \\L\\ \\ \\_\\ \\_/\\  __//\\__, `\\\n");
printf("                   \\ \\_\\ \\_\\ \\____\\ \\____ \\/\\____\\ \\____\\/\\____/\n");
printf("                    \\/_/\\/ /\\/____/\\/___L\\ \\/____/\\/____/\\/___/\n");
printf("                                     /\\____/\n");
printf("                                     \\_/__/\n"); 

printf(YELLOW"\n \n Chaque joueur à son tour peut placer ou deplacer un de ses Gobblet dans une case vide,\n \
ou par-dessus un Gobblet de taille inférieure. Les Gobblet de chaque joueurs sont identifiables par leur couleurs :\n \
jaune pour le joueur 1 et vert pour le joueur 2. Il y a 3 tailles, small, medium et big \n \
Le premier qui aligne 3 Gobblets de sa couleur gagne la partie.\n \
On peut aligner les Gobblets sur une ligne, une colonne ou une diagonale \n \
Pour gagner il faut memoriser la couleur des Gobblets cachés et être concentré !\n"); 
printf(YELLOW"\nEntrez 0 2 fois ");
retour();

select =0;
            } //fin select = 5

if (select ==6) { //options
printf(YELLOW"Voici les options, en cours de developpement"RESET);
options(&fond);
retour();
    select =0; //retourne au menu
            } //fin select =6

    } //fin de run, donc le menu n'apparaitra plus
} //fin de menu

int getch(void) //pour récupérer la touche pressée sans attendre d'appuyer sur entrer
{
   struct termios oldattr, newattr; //structure du terminal, anciens attributs et nouveaux attributs
   int ch;
   tcgetattr(0, &oldattr); //0 pour ne pas afficher
   newattr=oldattr; //les nouveaux attributs récupèrent les anciens
   newattr.c_lflag &= ~( ICANON | ECHO ); //c_lflag est un champ défini dans termios.h, ici on ajoute les attributs canonical input qui permettent de gérer les input en lignes
   //&= correspond au ET binaire
   tcsetattr( 0, TCSANOW, &newattr); //change les attributs immédiatement
   ch=getchar(); //la fonction getchar() normale sauf que les nouveaux attributs du terminal n'attendent pas que l'on appuie sur ENTRER pour récupérer l'input
   tcsetattr(0, TCSANOW, &oldattr); //on restitue les anciens attribus après voir récupéré l'input
   return(ch); //on renvoie l'input récupéré
}

int deplacement(int v, int max, int couleur) {// déplacement des flèches
     switch (v) {
                case 65: //flèche du haut
                     couleur -=1;//instructions
                break;
             case 66: //flèche du bas
                couleur += 1;
                break;
            }
        

if (couleur <0) {couleur =0;}//sinon on ne verrai plus couleur au bout d'un moment
if (couleur >max) {couleur =max;}

    return couleur;
}

void apparence(int v, int couleur, char tab[] [20], int max, int fond) { //pour voir les couleurs au déplacement des flèches sur le menu
for(int i =0; i<max; i++){
printf(RESET);
    printf("\n                      ");//les espaces ne doivent pas êtres colorés
if(deplacement(v, couleur, max) ==i ){printf(YELLOW); 
switch (fond) {
    case 0: printf(BBLUE); break;
    case 1: printf(BRED); break;
    case 2: printf(BGREEN); break;
    case 3: printf(BBLACK); break;
}
} //fin if deplacement = i
 else{printf(RESET);}
    printf("%s", tab[i]);
printf(RESET); //pour éviter que la dernière couleur n'impacte les autres
}

}

void gobblet () { // utilisé dans credits
//gobblet
printf("\n                                                               .,**,\n                                                            ,***,.\n                                                          .,****.\n                                                          .*****,...\n");                             
    printf("                                                       ..****////*,.\n                                                       .,,*****///*,\n                                                   .******///*,.\n                                                       ,*****///*,.\n                                                       ,***////*,\n                                                       ,**////*,\n                                                       ,**////*.\n                                                       .,,///*.\n");                                
    printf("                                                      ..*//,.\n                                                       ...,*/*,,,,,..\n                                                  ...,,,,,,***,,,,,,.....\n                                                .,,,,,,,,,,,,,,,,,,,,,,,....\n                                             ..,,,,,,,,,,,,,,,,,,,,,,,,,,,,....\n                                            .,,,,,,,,,,,,,,...,,,,,,,,,,,,,,,...\n                                           .,,,,,,,,,,,.........,,,,,,,,,,,,,,,..\n                                         ..,*,,,,,,,,.................,,,,,,,,,,,.\n");               
    printf("                                        .,,**,,,,,,,,,..................,,,,,,,,,,..\n                                       .,****,,,,,,,,,,,,,,,,,,,,,......,,,,,,,,,,,.\n                                      .,*****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*,..\n                                     .,*******,,,,,,,,,,,,,,,,,,,*********,,,,,,,***,,.\n                                     .,********,,,,,,,,,,,,,,,****,.....,*/*,,,,****,,.\n                                     .,*********,,,,,,,,,,,,,****.      .,***,,,****,,.\n                                     .,**********,,,,***//***/*.          ,/*,,*****,,.\n                    ,,,.             .,**************//,.......           ,*********,,.\n                    .,**,.           .,,************/*.      ..,**,.     .,****(#(/*,,.\n");         
    printf("                     .,***,..        ..,,******/(/**/*.    .*(((%%%%/.    .,****/(##/,,,.\n                     .,*//***,       ..,,,,**/#%%%%#(***/*... .,**,*,.. ...,****/#%%%%#/,,,.\n                      .,*//***,.      .,,,,***(%%%%(/***//**,.....,...,******/(%%%%%%%%#/,,,.\n                       .,*////*,.     .,,,,***(%%%%&%%%%(/***///**,,,***********/(%%%%%%%%%%%%(*,,.\n                         .*////*,.    .,,,,,*/(%%%%&&&%%%%#(/***************//(#%%%%%%%%%%%%%%%%(*,,.\n                          .**(((*.    .,,,,,*/#&&&@@&&%%%%##(///////////##%%%%%%%%%%%%%%%%%%%%#*,,.\n                          .,,/((/,....,,,,,**/#&&&@@@@&&&*,,,,,....*##%%%%%%%%%%%%%%%%%%%%#/,,..\n                       ..,,,,******,,,,,,,,**/#%%&&@@@@@&&&%%/,.......,(%%%%&%%%%%%%%%%%%%%%%%%#/,,..\n                    .,,,,,,,,,,,,,,,,,,,,,,,*/#%%&&&@@@@&&&&(*......,(%%&&&%%%%%%##(##%%#/,,..\n                  .,,,,,,,,,,,,,,,,,,,,,,,,,,,/(%%&&@@@@@&&&%%#(((##%%%%&&&&%%%%#/*,,*(##/,,..\n");        
    printf("                 .,,,,,,,,,,,....,,,,,,,,,,,,,*/#&&@@@@@&&&&%%%%%%%%&&&&&&&&%%%%(*,,,*(##/,,..\n                .,*,,,,,,,,..........,,,,,,,,,,*/#&@@@@@&&&&&&&&&&@@&&&&%%#/*,,,*(##/,,..\n               .,**,,,,,,,,,,...........,,,,,,,,*/#&@@@@&&&&&&&&&&@@&#/**,,**/(%%#/,,..\n");      
    printf("             ..,***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**(%%&@@@&&&&&&&&&&@@&%%((*******(#%%#/,,,.\n             ..,****,,,,,,,,,,,,,,,,,,*****,,,,,,*/%%&@@@&&&&&&&&&&@@&#/****/(#%%%%(*,,,..\n            .,,*********,,,,,,******,.     .*******#&@@@&&&&&&&&&&&(***,,,*,,,,,,,,,,..\n            .,,**********,,,,**/***,.      .***//**#&@@@&&&&&&&&&&%%#/*,,,,,,,,,,,,,,,,,..\n             ..,*************/*.....,/*. ..,**/((/*(&@@@@@&&&&&&/*,,,,,,,,,,,,,,,,,,,,.\n             ..,,********//**/*...****,..,,,*/#%%#/*(%%@@@@@@&&&&%%#/*,,,,,,,,,,,,,,,,,,,,,.\n             ..,,,******(#(*****,,,,,,,****/(%%&&%%(/(%%@@@@@@&&&/*,,,,,,,,,,,,,,,,,,,,,,.\n              ..,,,,*****(%%%%##/**********/##%%%%%%&&%%#//%%&@@@@@@&&%%#/**,,,,,,,,,,,,,,*******,.\n             ..,,,,,***/#%%&&&%%%%%%#(/**,,,*((%%%%%%&&//(%%&@@@@@@&%%#/***,,,,,,,,,,,*****,,,**.\n             ..,,,,,,**(%%&&&&&&&%%#*....,/##%%%%%%&&/*/(#%%%%%%&&&&/****,,,,,,***********/(*.\n             ..,,,,,,**(%%&&&&&&&%%#/,..,*(%%%%%%%%%%&&/*/(((###%%%%%%%%(/****,,,,,,*//*****///((/.\n             ..,,,,,,*/#%%%%&&&&&&&%%%%###%%%%%%%%%%%%%%%%&&&%%/*****////*********,******/##((///((##/.\n             ...,,,,,,/#%%%%&&&&&&&&&%%%%%%%%%%%%%%%%%%%%%%%%&/,.          .,***,,,,,,,*/#%%%%%%(**//##/,\n               .,,,,,,*#%%%%&&&%%&&&&%%%%%%%%%%%%%%%%%%%%%%%%%%&%%#/,.          .,***,,,,,,,*/#%%&%%%%##%%%%%%#(,\n");        
    printf("               .,,,,,,*(%%%%%%%%%%%%%%&&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#*,.          .,***,,,,,,,*/#%%&&%%%%%%%%%%%%#(*.\n               .,,,,,,*/#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#(*,,.          .,,,,,,,,,,*(%%&&%%%%%%%%%%%%%%#(,.\n               .,,,,,,,*/#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#(*,,,.          .,,,,,,,,,*/#%%&%%%%%%%%%%%%%%#(*,\n               .,,,,,,,*/(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#/*,,.           .,,,,,**,**/#%%%%%%%%%%%%%%##(/,.\n               .,,,,,,,,**(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#/*,..             .,,,*******/(####(/**,.\n                .,,,,,,,,,*//#%%%%%%%%%%%%%%%%%%%%%%%%%%%%#(*,..                 .,,,,,,,,,,,,,,..\n                 .,,,****,,***/(##%%%%%%%%##(((/*,..\n");
}

void gobbletS() { // utilisé dans credits
    printf(BLUE); printf(BWHITE);
printf("                  ,*//////*.\n");
printf("                ,///***////,\n");
printf("              .*******/***\n");
printf("              ,,*******,*,,\n");
printf("              ,,*,,*,,*,,*,**\n");
printf("              .,*,*,,,,*****.\n");
printf("               .,*//******\n");
printf("                 ,*,*,\n");
printf(RED"           ,////////////////,\n");
printf("       .////////////////////////.\n");
printf("     *////////////////////////////,\n");
printf("   ,////////////////////////////////\n");
printf("  ,///////////////*       .#/////////.\n");
printf("  //////////(. "BLACK"..     ,%%%%%%"RED" .#/////////\n");
printf(" .//////////(.."BLACK"%%%%,"RED"    ."BLACK"##"RED"*.((/////////.\n");
printf(" .////////////("BLACK"##"RED"(#(%%#((##////////////,\n");
printf(" .///(@%%(//////////////////////(#/////,\n");
printf(" .////(@&/////////////////////(&////,\n");
printf(" ./////%%"BLACK"@@@@@@@@@@@@@@@@@@@@@@@@"RED"//////,\n");
printf("  /////("BLACK"@@@@@@@@@@@@@@@@@@@@@@@"RED"(//////,\n");
printf("  //////"BLACK"@@@@@@@@@,.,,,,%%@@@@@@@"RED"///////,\n");
printf("  //////&"BLACK"@@@@@@@@/.,,,,@@@@@@@"RED"&///////,\n");
printf("  //////"BLACK"@@@@@@@@@@@@@@@@@@@@@@"RED"#///////,\n");
printf("  ////("BLACK"@@@@@@@@@@@@@@@@@@@@@@@@"RED"#//////,\n");
printf("  ////"BLACK"@@@@@@@@@@@@@@@@@@@@@@@@@@"RED"#/////,\n");
printf("  //"BLACK"(@@@@@@@@@@@@@@@@@@@@@@@@@@@@"RED"(////,\n");
printf("  ///"BLACK"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"RED"(///,\n");
printf("  ////"BLACK"@@@@@@@@@@@@@@@@@@@@@@@@@@@"RED"(////,\n");
printf("  //////(&"BLACK"@@@@@@@@@@@@@@@@@@@@"RED"#///////,\n");
printf("    .*/////////(########(//////////*.\n");
printf(RESET);
}

void credits() {
        int n=5; //pour le compteur de 5 à 1
    printf("\n \n"YELLOW);
    printf("Ce programme est developper par Arnaud GODET, etudiant en premiere annee a l' IUT Grand Ouest Normandie dans le TD3.");
    printf(RESET "\n \n");
gobbletS();
printf(YELLOW "\n \n Cette page s'affiche pendant 5s");
printf(" \n Aggrandissez la console si necessaire pour voir correctement le gobelet");
printf("\n"RESET);
sleep(5);

while(n>0) {
system("clear");
printf(YELLOW"Les credits vont déclencher une serie d'actions durant environ 15s\n");
printf("\nProchaine action dans %d\n", n); printf(RESET);
n-=1;
sleep(1);
}
    gobblet();
    sleep(4);
blink();

}

void options(int *fond) {
printf(YELLOW"\nAPPUYEZ SUR 0 PUIS ENTRER ");
scanf("%d",fond);
viderBuffer();
do {
printf("Choisissez le fond du texte du menu lorsque l'on se déplace, 0 pour bleu, 1 pour rouge, 2 pour vert et 3 pour noir ");
scanf("%d", fond); //fond est un pointeur donc pas de &
}
while (*fond<0 || *fond >3);
}

//les titres sont dans blink et les credits
void titre1() {
    printf("\n");
printf(BLUE"   ______      __    __    __     __     ______      __    __    __"RESET"\n");
printf(BLUE"  / ____/___  / /_  / /_  / /__  / /_   / ____/___  / /_  / /_  / /__  __________ "RESET"\n");
printf(WHITE" / / __/ __ \\/ __ \\/ __ \\/ / _ \\/ __/  / / __/ __ \\/ __ \\/ __ \\/ / _ \\/ ___/ ___"RESET"\n");
printf(WHITE"/ /_/ / /_/ / /_/ / /_/ / /  __/ /_   / /_/ / /_/ / /_/ / /_/ / /  __/ /  (__  )"RESET"\n");
printf(RED"\\____/\\____/_.___/_.___/_/\\___/\\__/   \\____/\\____/_.___/_.___/_/\\___/_/  /____/"RESET"\n"); 
                                                                                 

}
void titre2() {
    printf("\n");
printf(MAGENTA"   )\\.-.      .-./(     /(,-.     /(,-.   .')       )\\.---.  .-,.-.,-.         )\\.-.      .-./(     /(,-.     /(,-.   .')       )\\.---.     /`-.    )\\.--."RESET"\n");
printf(MAGENTA" ,' ,-,_)   ,'     )  ,' _   )  ,' _   ) ( /       (   ,-._( ) ,, ,. (       ,' ,-,_)   ,'     )  ,' _   )  ,' _   ) ( /       (   ,-._(  ,' _  \\  (   ._.'"RESET"\n");
printf(BLUE"(  .   __  (  .-, (  (  '-' (  (  '-' (   ))        \\  '-,   \\( |(  )/      (  .   __  (  .-, (  (  '-' (  (  '-' (   ))        \\  '-,   (  '-' (   `-.`."RESET"\n");
printf(BLUE" ) '._\\ _)  ) '._\\ )  )  _   )  )  _   )  )'._.-.    ) ,-`      ) \\          ) '._\\ _)  ) '._\\ )  )  _   )  )  _   )  )'._.-.    ) ,-`    ) ,_ .'  ,_ (  \\"RESET"\n");
printf(YELLOW"(  ,   (   (  ,   (  (  '-' /  (  '-' /  (       )  (  ``-.     \\ (         (  ,   (   (  ,   (  (  '-' /  (  '-' /  (       )  (  ``-.  (  ' ) \\ (  '.)  )"RESET"\n");
printf(YELLOW" )/'._.'    )/ ._.'   )/._.'    )/._.'    )/,__.'    )..-.(      )/          )/'._.'    )/ ._.'   )/._.'    )/._.'    )/,__.'    )..-.(   )/   )/  '._,_.'"RESET"\n");
}

void titre3() {
    printf("\n");
printf(GREEN"  ______       _     _     _                ______       _     _     "RESET"\n");
printf(CYAN" / _____)     | |   | |   | |      _       / _____)     | |   | |   | "RESET"\n");
printf(GREEN"| /  ___  ___ | | _ | | _ | | ____| |_    | /  ___  ___ | | _ | | _ | | ____  ____ "RESET"\n");
printf(GREEN"| | (___)/ _ \\| || \\| || \\| |/ _  )  _)   | | (___)/ _ \\| || \\| || \\| |/ _  )/ ___)"RESET"\n");
printf(CYAN"| \\____/| |_| | |_) ) |_) ) ( (/ /| |__   | \\____/| |_| | |_) ) |_) ) ( (/ /| |  "RESET"\n");
printf(CYAN" \\_____/ \\___/|____/|____/|_|\\____)\\___)   \\_____/ \\___/|____/|____/|_|\\____)_|  "RESET"\n");
}

void blink() {
int r =0, f=0; //r pour un nombre random dans blink, f pour sortir de la boucle
do {
    system("clear");
    //system("sl"); //si on a téléchargé dans le terminal cela lance un train
    r = rand()%3;
    //printf("\nCeci est r %d\n",r);
    switch(r) {
        case 0:
        titre1();
        break;
        case 1:
         titre2();
        break;
        case 2:
        titre3();
        break;
    }
    sleep(1);
    //printf("\n Voici f %d \n", f);
    f++;
}
while(f<9);
    printf("\nRetour au menu :\n");

} 

void retour () {
    int back =1;
printf("\n \n Entrez 0 pour revenir au menu\n");
viderBuffer();
while (back !=0) {
scanf("%d", &back);
}
system("clear");
viderBuffer(); //sinon il detecte encore que l'on a appuyé sur entrer et nous fait revenir dans Regles
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF) //end of file, valeur particulière retournée nottament lorsque l'on utilise fgetc()
    {
        c = getchar();
    }
}