//couleurs, voir code ascii http://ascii-table.com/ansi-escape-sequences.php :
#define BLACK   "\033[30m"
#define RED   "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE   "\033[34m"
#define MAGENTA   "\033[35m"
#define CYAN   "\033[36m"
#define WHITE   "\033[37m"
#define RESET "\033[0m"
#define BLINK "\033[5m"
#define RESMODE "\033[0l"

#define BBLACK "\033[40m"
#define BRED "\033[41m"
#define BGREEN   "\033[42m"
#define BYELLOW   "\033[43m"
#define BBLUE   "\033[44m"
#define BMAGENTA   "\033[45m"
#define BCYAN   "\033[46m"
#define BWHITE   "\033[47m"

//ici se trouvent les fonctions pouvant être communes à tous les programmes

//pour faire un menu
int getch(void); //pour detecter lorsque l'on presse une touche sans avoir à appuyer sur entrer
int deplacement(int v, int max, int couleur);
void apparence(int v, int couleur, char tab[] [20], int max, int fond);

void jeu(); //utilisé dans menu

void menu(); //utilisé dans projetGG

void gobbletS(); //image de gobblet souriant reconstituée dans la console

