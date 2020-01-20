#include <stdlib.h>
#include <stdio.h>
#include "morpion_simple.h"

void choix_taille_grille(int* context,SDL_Surface *ecran,int type_partie);
void pause();
void menu(int* context);
void playmusique(Mix_Music *musique);
void navigationInMenu(int positionYPointeur,SDL_Surface *ecran,
        SDL_Surface *buttonJ1vsJ2,SDL_Surface *buttonJvsIA,SDL_Surface *buttonQuitter,
            SDL_Surface *buttonPointeur_menu,
                SDL_Surface *texte, SDL_Rect positionBJ1vsJ2,SDL_Rect positionBJvsIA,
                    SDL_Rect positionBQuitter,
                        SDL_Rect *positionPointeurMenu, SDL_Rect positionTitre);

int main(int argc, char *argv[])
{
    int context = MAIN;

    menu(&context);
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            case SDL_KEYDOWN: /* Si appui sur une touche */
                continuer = 0;
                break;
        }
    }
}

void choix_taille_grille(int* context,SDL_Surface *ecran,int type_partie){
    
    *context = SELECT_TAILLE;
    int taille;
    SDL_Event event;
    int continuerChoixTaille = 1;

    SDL_Surface *texte_choix = NULL;
    SDL_Surface *buttonPointeur_choix = NULL;
    SDL_Surface *taille3 = NULL;
    SDL_Surface *taille4 = NULL;
    SDL_Surface *taille5 = NULL;
    SDL_Surface *taille6 = NULL;
    SDL_Surface *taille7 = NULL;
    SDL_Surface *taille8 = NULL;
    
    TTF_Font *police = NULL;
    
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Rect positionText_choix;
    SDL_Rect positionPointeurChoix;
    SDL_Rect positionTaille3;
    SDL_Rect positionTaille4;
    /*SDL_Rect positionTaille5;
    SDL_Rect positionTaille6;
    SDL_Rect positionTaille7;
    SDL_Rect positionTaille8;
    */
    police = TTF_OpenFont("alphawood.ttf", 40);
    texte_choix = TTF_RenderText_Blended(police, "Taille de la grille", couleurNoire);
    police = TTF_OpenFont("alphasnail.ttf", 30);
    buttonPointeur_choix = TTF_RenderText_Blended(police, ">", couleurNoire);
    police = TTF_OpenFont("alphawood.ttf", 30);
    taille3 = TTF_RenderText_Blended(police, "3", couleurNoire);
    taille4 = TTF_RenderText_Blended(police, "4", couleurNoire);
    /*taille5 = TTF_RenderText_Blended(police, "5", couleurNoire);
    taille6 = TTF_RenderText_Blended(police, "6", couleurNoire);
    taille7 = TTF_RenderText_Blended(police, "7", couleurNoire);
    taille8 = TTF_RenderText_Blended(police, "8", couleurNoire);
    */
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));

    positionText_choix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2);
    positionText_choix.y = 50;
    SDL_BlitSurface(texte_choix, NULL, ecran, &positionText_choix);

    positionPointeurChoix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2) - 25;
    positionPointeurChoix.y = 100;
    SDL_BlitSurface(buttonPointeur_choix, NULL, ecran, &positionPointeurChoix);

    positionTaille3.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2);
    positionTaille3.y = 100;
    SDL_BlitSurface(taille3, NULL, ecran, &positionTaille3);

    positionTaille4.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2);
    positionTaille4.y = 100 + 25;
    SDL_BlitSurface(taille4, NULL, ecran, &positionTaille4);

    SDL_Flip(ecran);

    while(continuerChoixTaille)
   {
      SDL_WaitEvent(&event);
       switch(event.type)
        {
            case SDL_QUIT:
                continuerChoixTaille = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: 
                        if(positionPointeurChoix.y == 125 && *context==SELECT_TAILLE){
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));
                            positionPointeurChoix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2) - 25;
                            positionPointeurChoix.y = 100;
                            SDL_BlitSurface(texte_choix, NULL, ecran, &positionText_choix);
                            SDL_BlitSurface(buttonPointeur_choix, NULL, ecran, &positionPointeurChoix);
                            SDL_BlitSurface(taille3, NULL, ecran, &positionTaille3);
                            SDL_BlitSurface(taille4, NULL, ecran, &positionTaille4);
                            SDL_Flip(ecran);
                        }
                        break;
                    case SDLK_DOWN: 
                        if(positionPointeurChoix.y == 100 && *context==SELECT_TAILLE){
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));
                            positionPointeurChoix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2) - 25;
                            positionPointeurChoix.y = 100 +25;
                            SDL_BlitSurface(texte_choix, NULL, ecran, &positionText_choix);
                            SDL_BlitSurface(buttonPointeur_choix, NULL, ecran, &positionPointeurChoix);
                            SDL_BlitSurface(taille3, NULL, ecran, &positionTaille3);
                            SDL_BlitSurface(taille4, NULL, ecran, &positionTaille4);
                            SDL_Flip(ecran);
                        }
                        break;
                    case SDLK_RETURN:
                        if(*context==SELECT_TAILLE){
                            if(positionPointeurChoix.y==100){
                                taille = 3;
                            }else{
                                taille = 4;
                            }
                            if(type_partie==1) partie1vs1(context,ecran,taille);
                            if(type_partie==2) partieIAvsJoueur(context,ecran,taille);
                            
                        }
                    break;
                }
        }
    }

    
}

void playmusique(Mix_Music *musique){
  
   musique = Mix_LoadMUS("song.mp3"); //Chargement de la musique
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
   
}

void menu(int *context){

    *context = MENU;
    int continuer = 1;
    int type_partie;
    SDL_Event event;

    SDL_Surface *ecran = NULL;
    SDL_Surface *buttonJ1vsJ2 = NULL;
    SDL_Surface *buttonJvsIA = NULL;
    SDL_Surface *buttonQuitter = NULL;
    SDL_Surface *buttonPointeur_menu = NULL;

    SDL_Surface *texte = NULL, *fond = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};

    SDL_Rect positionBJ1vsJ2;
    SDL_Rect positionBJvsIA;
    SDL_Rect positionBQuitter;
    SDL_Rect positionTitre;
    SDL_Rect positionPointeurMenu;
    Mix_Music *musique; //Création du pointeur de type Mix_Music

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    TTF_Init();

    ecran = SDL_SetVideoMode(LONGUEUR_GRILLE, LARGEUR_GRILLE, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    
    /* Chargement de la police */
    police = TTF_OpenFont("alphawood.ttf", 65);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, "Tic Tact Toe", couleurNoire);

    police = TTF_OpenFont("alphawood.ttf", 30);
    buttonQuitter = TTF_RenderText_Blended(police, "Quitter", couleurNoire);
    buttonJ1vsJ2 = TTF_RenderText_Blended(police, "Joueur 1 VS Joueur 2", couleurNoire);
    buttonJvsIA = TTF_RenderText_Blended(police, "Joueur VS IA", couleurNoire);
    police = TTF_OpenFont("alphasnail.ttf", 40);
    buttonPointeur_menu = TTF_RenderText_Blended(police,">",couleurNoire);

    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
     {
        printf("%s", Mix_GetError());
     }

    // Coloration de la surface ecran 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));

    positionBJ1vsJ2.x = (LONGUEUR_GRILLE / 2) - (buttonJ1vsJ2->w/2);
    positionBJ1vsJ2.y = (LARGEUR_GRILLE / 2) - (50 / 2);
    SDL_BlitSurface(buttonJ1vsJ2, NULL, ecran, &positionBJ1vsJ2);

    positionBJvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonJvsIA->w / 2);
    positionBJvsIA.y = positionBJ1vsJ2.y + 56;
    SDL_BlitSurface(buttonJvsIA, NULL, ecran, &positionBJvsIA);

    positionBQuitter.x = (LONGUEUR_GRILLE / 2) - (buttonQuitter->w / 2);
    positionBQuitter.y = positionBJvsIA.y + 56;
    SDL_BlitSurface(buttonQuitter, NULL, ecran, &positionBQuitter);

    positionPointeurMenu.x = positionBJ1vsJ2.x - 25;
    positionPointeurMenu.y = positionBJ1vsJ2.y;
    SDL_BlitSurface(buttonPointeur_menu, NULL, ecran, &positionPointeurMenu);

    positionTitre.x =  (LONGUEUR_GRILLE/2 - texte->w/2);
    positionTitre.y = 50;
    SDL_BlitSurface(texte, NULL, ecran, &positionTitre); /* Blit du texte */

    /* Mise à jour de l'écran avec sa nouvelle couleur */
    SDL_Flip(ecran);

    SDL_WM_SetCaption("Morpion AlphaBeta", NULL);

    playmusique(musique);

    while(continuer && *context==MENU)
   {
      SDL_WaitEvent(&event);
       switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: // Flèche haut
                        if(positionPointeurMenu.y>positionBJ1vsJ2.y && *context==MENU){
                            navigationInMenu(1,ecran,
                            buttonJ1vsJ2,buttonJvsIA,buttonQuitter,
                                buttonPointeur_menu,
                                    texte, positionBJ1vsJ2,positionBJvsIA,
                                        positionBQuitter,
                                            &positionPointeurMenu, positionTitre);
                        }
                        break;
                    case SDLK_DOWN: // Flèche bas
                        if(positionPointeurMenu.y<positionBQuitter.y && *context==MENU){
                            navigationInMenu(-1,ecran,
                            buttonJ1vsJ2,buttonJvsIA,buttonQuitter,
                                buttonPointeur_menu,
                                    texte, positionBJ1vsJ2,positionBJvsIA,
                                        positionBQuitter,
                                            &positionPointeurMenu, positionTitre);
                                            
                        }
                        break;
                    case SDLK_RETURN:
                        if(*context==MENU){
                            SDL_FreeSurface(buttonJ1vsJ2);
                            SDL_FreeSurface(buttonJvsIA);
                            SDL_FreeSurface(buttonQuitter);
                            SDL_FreeSurface(buttonPointeur_menu);
                            SDL_FreeSurface(texte);
                        
                            if(positionPointeurMenu.y==positionBJ1vsJ2.y) {
                                type_partie =1;
                                choix_taille_grille(context,ecran,type_partie);
                            }
                            if(positionPointeurMenu.y==positionBJvsIA.y){ 
                                type_partie =2;
                                choix_taille_grille(context,ecran,type_partie);
                            }
                            
                            if(positionPointeurMenu.y==positionBQuitter.y) continuer = 0;
                            
                            
                        }
                    break;
                }
                break;
        }
   }

    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API

    TTF_CloseFont(police);
    TTF_Quit();
    
    SDL_FreeSurface(buttonJ1vsJ2);
    SDL_FreeSurface(buttonJvsIA);
    SDL_FreeSurface(buttonQuitter);
    SDL_FreeSurface(buttonPointeur_menu);
    SDL_FreeSurface(texte);
    
}

void navigationInMenu(int positionYPointeur,SDL_Surface *ecran,
        SDL_Surface *buttonJ1vsJ2,SDL_Surface *buttonJvsIA,SDL_Surface *buttonQuitter,
            SDL_Surface *buttonPointeur_menu,
                SDL_Surface *texte, SDL_Rect positionBJ1vsJ2,SDL_Rect positionBJvsIA,
                    SDL_Rect positionBQuitter,
                        SDL_Rect *positionPointeurMenu, SDL_Rect positionTitre){

    // Coloration de la surface ecran 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));

    positionBJ1vsJ2.x = (LONGUEUR_GRILLE / 2) - (buttonJ1vsJ2->w/2);
    positionBJ1vsJ2.y = (LARGEUR_GRILLE / 2) - (50 / 2);
    SDL_BlitSurface(buttonJ1vsJ2, NULL, ecran, &positionBJ1vsJ2);

    positionBJvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonJvsIA->w / 2);
    positionBJvsIA.y = positionBJ1vsJ2.y + 56;
    SDL_BlitSurface(buttonJvsIA, NULL, ecran, &positionBJvsIA);

    positionBQuitter.x = (LONGUEUR_GRILLE / 2) - (buttonQuitter->w / 2);
    positionBQuitter.y = positionBJvsIA.y + 56;
    SDL_BlitSurface(buttonQuitter, NULL, ecran, &positionBQuitter);

    positionPointeurMenu->x = positionBJ1vsJ2.x - 25;
    if(positionYPointeur == -1){
        positionPointeurMenu->y = positionPointeurMenu->y + 56;
        
    }else if(positionYPointeur == 1){
        positionPointeurMenu->y = positionPointeurMenu->y - 56;
    }
    SDL_BlitSurface(buttonPointeur_menu, NULL, ecran, positionPointeurMenu);

    positionTitre.x =  (LONGUEUR_GRILLE/2 - texte->w/2);
    positionTitre.y = 50;
    SDL_BlitSurface(texte, NULL, ecran, &positionTitre); /* Blit du texte */

    /* Mise à jour de l'écran avec sa nouvelle couleur */
    SDL_Flip(ecran);
}

