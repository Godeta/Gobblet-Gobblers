#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#define WIDTH 1024
#define HEIGHT 575
#define IMAGEPATH "./data/gobblet.png"
#define FONTPATH "./data/font.ttf"

void quitter() //pour tout fermer à la fin du programme
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main()
{
    //création d'un évènement
    //SDL_Event clic; // Cette variable servira plus tard à gérer les événements
// 2 possibilités, waitEvent -> stop le programme en attendant de voir si un évènement se produit, PollEvent -> vérifie si un évènement se produit sinon retour au main
 //initialisation des surfaces
    SDL_Surface* pWindowSurface = NULL; // Ecran principal
    SDL_Surface* Gobblet = NULL; // Logo
    SDL_Surface* background = NULL; // Fond
    SDL_Surface* clic = NULL; //image lors du clic de la souris
    char mustContinue = 1; // Indicateur boolean pour la boucle principale

    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF; // Flags pour charger le support du JPG, PNG et TIF
    //coordonnées + hauteur et largeur
    SDL_Rect blitDestination;
    SDL_Rect blitFond;
    SDL_Rect positionClic; //coordonnées du clic de la souris
    SDL_Rect texteDestination;

    TTF_Font* pFont = NULL;
    SDL_Color fontColor = {99, 140, 222}; //couleur du texte
    SDL_Surface* pFontSurface = NULL;



    //série de test avec if pour vérifier que tout fonctionne bien et indiquer ce qui pose problème dans le cas contraire
    // Demarre SDL
    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
        return -1;
    }

    if ( IMG_Init(imgFlags) != imgFlags )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_image : '%s'\n",IMG_GetError());
        quitter();
        return -1;
    }

    if ( TTF_Init() == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_TTF : '%s'\n",TTF_GetError());
        quitter();
        return -1;
    }
SDL_WM_SetIcon(IMG_Load("./data/anime_thumb_up.png"), NULL); //change l'icône en haut à gauche de la fenêtre
    // Creer la fenetre
    pWindowSurface = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
	if ( pWindowSurface == NULL ) //test si la fenêtre s'est ouverte
	{
	    fprintf(stderr,"Erreur lors de l'ouverture de la fenetre\n");
	    quitter();
        return -2;
	}

	//charge l'image
	background = IMG_Load( "./data/fondB.jpg" ); //le fond
	Gobblet = IMG_Load(IMAGEPATH); //gobblet gobblers
	clic = IMG_Load( "./data/clic.png" ); //le fond
	if ( Gobblet == NULL )
    {
        fprintf(stderr,"Erreur de chargement de l'image %s : %s\n",IMAGEPATH,IMG_GetError());
        quitter();
        return -3;
    }

    // Charge la police
    pFont = TTF_OpenFont(FONTPATH,32); //32 règle la taille de la police
    if ( pFont == NULL )
    {
        fprintf(stderr,"Erreur de chargement de la police %s : %s\n",FONTPATH,TTF_GetError());
        quitter();
        return -3;
    }

    // Genere la SDL_Surface a partir de la police
    pFontSurface = TTF_RenderText_Solid(pFont,"Bienvenu dans GOBBLET GOBBLERS !",fontColor); //affiche le texte
    if ( !pFontSurface )
    {
        fprintf(stderr,"Erreur pour generer le texte '%s'\n",TTF_GetError());
        quitter();
        return -4;
    }

    // Une fois l'image chargée, nous pouvons calculer une position relative à celle-ci
    // Nous centrons l'image dans la fenêtre
    blitDestination.x = WIDTH/2 - Gobblet->w/2;
    blitDestination.y = HEIGHT/3 - Gobblet->h/2;
    blitDestination.w = Gobblet->w;
    blitDestination.h = Gobblet->h;

    //image de fond
    blitFond.x = 0- background->w;
    blitFond.y = 0-background->h;

    //clic
    positionClic.x = 0; positionClic.y =-0;

    // Nous avons notre surface pour le texte donc nous calculons la position relative
    // Le texte est à un 16ème de la hauteur de l'ecran
    texteDestination.x = WIDTH/2 - pFontSurface->w/2;
    texteDestination.y = HEIGHT/16;
    texteDestination.w = pFontSurface->w;
    texteDestination.h = pFontSurface->h;

    // Boucle principale
	while ( mustContinue )
	{
	    //On applique le fond sur l'écran
	SDL_BlitSurface(background,NULL,pWindowSurface,&blitFond);
	    // Affiche le logo au centre de la fenêtre
	    if ( SDL_BlitSurface(Gobblet,NULL,pWindowSurface,&blitDestination) != 0 )
        {
            fprintf(stderr,"Erreur de copie de la surface sur l'écran\n");
            mustContinue=0;
        }
        // Affiche le texte
	    if ( SDL_BlitSurface(pFontSurface,NULL,pWindowSurface,&texteDestination) != 0 )
        {
            fprintf(stderr,"Erreur de copie du texte sur l'écran\n");
            mustContinue=0;
        }
        SDL_BlitSurface(clic,NULL,pWindowSurface,&positionClic); //affiche clic là où on a cliqué
        //positionClic.x =-1000;
        SDL_Flip(pWindowSurface);

	    SDL_Event event;
	    SDL_WaitEvent(&event);

        // Detecte si on clique sur la croix de la fenêtre
	    if( event.type == SDL_QUIT )
	    {
            //On quitte le programme
            mustContinue = 0;
		}
		// Detecte si une touche est appuyee
		else if( event.type == SDL_KEYDOWN )
		{
            if ( event.key.keysym.sym == SDLK_ESCAPE )
            {
                mustContinue = 0;
            }
		}
		else if ( event.type ==SDL_MOUSEBUTTONUP) {

           positionClic.x = 0;//event.button.x - positionClic.w;
           positionClic.y = 0;//event.button.y - positionClic.h;
		}
		else if (event.type ==SDL_MOUSEMOTION) {
           positionClic.x = event.motion.x - positionClic.w/2;
           positionClic.y = event.motion.y - positionClic.h/2;
		}

	} //fin de la boucle principale

    SDL_FreeSurface(pFontSurface);
    TTF_CloseFont(pFont);
    SDL_FreeSurface(Gobblet);
    quitter();
    /*appeler programme ProjetGG*/

    return 0;
}
