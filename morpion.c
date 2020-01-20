#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "morpion.h"


void afficher_gagnant(SDL_Surface *ecran,int victoire_joueur,char joueur){
    SDL_Surface *texte = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Rect position;
    char chaine_text[16] = "";

    if(victoire_joueur==1){
        strcat(chaine_text,"Victoire des ");
        if(joueur=='1'){
            strcat(chaine_text, "X");
        }else
        {
            strcat(chaine_text, "O");
        }
    }else{
        strcat(chaine_text,"Match Null");
    }

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    police = TTF_OpenFont("ka.ttf", 50);
    texte = TTF_RenderText_Blended(police, chaine_text, couleurNoire);

    position.x =  (LONGUEUR_GRILLE/2 - texte->w/2);
    position.y = (LONGUEUR_GRILLE/2 - texte->h/2);
    SDL_BlitSurface(texte, NULL, ecran, &position); 

    SDL_Flip(ecran);

    return;
}

void afficher_grille_vide(int* context,SDL_Surface *ecran,int taille){
    plateau grille;
    SDL_Surface *case_grille = NULL;
    SDL_Rect position;
    int i,j;
    *context = GRILLE;
    int unite,k;

    grille = (SDL_Surface***) malloc(taille * sizeof(SDL_Surface**));
    
    for(i=0;i<taille;i++){
        grille[i] = (SDL_Surface**) malloc(taille * sizeof(SDL_Surface*));
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    unite = (ecran->w)/taille;
    
    case_grille = SDL_CreateRGBSurface(SDL_HWSURFACE, unite, unite, 32, 0, 0, 0, 0);
    
    // boucle d'affichage de ma grille initialiser avec vide et s'affichant sur le rectangle noir
    k=0;
    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            k=k%2;
            grille[i][j]=case_grille;
            position.y=i*unite;
            position.x=j*unite;
            if(k==0)
            SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            else SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 236,239,241)); 
            SDL_BlitSurface(grille[i][j], NULL, ecran, &position); // Collage de la surface sur l'écran 
            k++;
        }
        if(taille%2==0) k++;
    }
 
    
    SDL_Flip(ecran); /* Mise à jour de l'écran */

}

morpion init_grille(morpion grille, int taille){

    int i,j;
    grille = (char**) malloc(taille * sizeof(char*));
    
    for(i=0;i<taille;i++){
        grille[i] = (char*) malloc(taille * sizeof(char));
    }

    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            grille[i][j] = 'x';
        }
    }
    return grille;
}

void update_interface(morpion grille_pion, int taille,int* context,SDL_Surface *ecran){
    plateau grille;
    SDL_Surface *case_grille = NULL;
    SDL_Rect position;
    int i,j;
    *context = GRILLE;
    int unite,k;

    SDL_Surface *pion = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Rect positionPion;

    grille = (SDL_Surface***) malloc(taille * sizeof(SDL_Surface**));
    
    for(i=0;i<taille;i++){
        grille[i] = (SDL_Surface**) malloc(taille * sizeof(SDL_Surface*));
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    unite = LONGUEUR_GRILLE/taille;
    
    case_grille = SDL_CreateRGBSurface(SDL_HWSURFACE, unite, unite, 32, 0, 0, 0, 0);

    police = TTF_OpenFont("keepcalm.ttf", 70);

    k=0;
    
    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            k=k%2;
            grille[i][j]=case_grille;
            position.y=i*unite;
            position.x=j*unite;
            
            if(grille_pion[i][j]=='1'){
                //rgb(77,182,172)
                SDL_Color xcolor = {77,182,172};
                pion = TTF_RenderText_Blended(police, "X", xcolor);
            }else if(grille_pion[i][j]=='0'){
                //rgb(66,165,245)
                SDL_Color ocolor = {66,165,245};
                pion = TTF_RenderText_Blended(police, "O", ocolor);
            }else{
                pion = TTF_RenderText_Blended(police, "", couleurNoire);
            }
            
            positionPion.x =  (position.x) + (unite/2) - 30;
            positionPion.y = (position.y) + (unite/2) - 30;
            
            if(k==0)
            SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            else SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 236,239,241)); 
            SDL_BlitSurface(grille[i][j], NULL, ecran, &position); // Collage de la surface sur l'écran
            SDL_BlitSurface(pion, NULL, ecran, &positionPion);
            k++;
            
        }
        
        if(taille%2==0) k++;
    }
    SDL_Delay(100);
    SDL_Flip(ecran); /* Mise à jour de l'écran */
    
}


void vider_memoire(morpion grille, int taille)
{
    int i;
    for(i=0;i<taille;i++){
        free(grille[i]);
    }
    free(grille);
}

int verif_coordonne(morpion grille,int taille, int x,int y)  
{
    
    if(x<taille && x>=0 ){ 
        if(y<=taille-1 && y>=0){
            if(grille[x][y] =='x') return 0; //case vide donc possibiité de jeux
            else return 1;  //case occupé
        }
    }
    return 1;
}

void update_matrice(morpion grille,int x,int y, char joueur)
{
    grille[x][y]=joueur;
}

int victoire(morpion grille, int taille, char joueur)
{
    int i,j,compteur,fin;
    i=0;
    fin=0;
    compteur = 0;
    
    //victoire ligne
    while(i<taille && fin!=1){
        for(j=0;j<taille;j++){
            if(grille[i][j]==joueur)compteur++;           
        }
        if(compteur==taille) fin = 1;
        compteur = 0;
        i++;
    }

    //victoire colone
    j=0;
    while(j<taille && fin!=1){
        for(i=0;i<taille;i++){
            if(grille[i][j]==joueur)compteur++;        
        }
        if(compteur==taille) fin = 1;
        compteur = 0;
        j++;
    }

    //victoire diagonale1
    for(i=0;i<taille;i++){
        if(grille[i][i]==joueur)compteur++;        
    }
    if(compteur==taille) fin = 1;
    i++;

    //victoire diagonale2
    i=0;
    j=taille-1;
    compteur = 0;
    while (i<taille && j>=0)
    {
        if(grille[i][j]==joueur)compteur++;
        if(compteur==taille) fin = 1;
        i++;
        j--;
    }
    
    return fin;
}

void jouer(int* context,SDL_Surface *ecran,morpion grille, int taille, char joueur)
{
    int x,y,cord_ok = -99;
    SDL_Event event;
    int waitForUser=1;
    int coordXcursor;
    int coordYcursor;
    int unite;

    *context = JOUER_PION;
    unite = LONGUEUR_GRILLE/taille;
    while (waitForUser!=0 && cord_ok!=0)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                waitForUser = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if(*context==JOUER_PION){
                    coordXcursor = event.button.x;
                    coordYcursor = event.button.y;
                    waitForUser = 0;

                    if(taille==4 && coordYcursor<unite) x = 0;
                    else if(taille==4 && coordYcursor>unite && coordYcursor<(unite*2)) x = 1;
                    else if(taille==4 && coordYcursor>(unite*2) && coordYcursor<(unite*3)) x = 2;
                    else if(taille==4 && coordYcursor>(unite*3) && coordYcursor<(unite*4)) x = 3;

                    if(taille==4 && coordXcursor<unite) y = 0;
                    else if(taille==4 && coordXcursor>unite && coordXcursor<(unite*2)) y = 1;
                    else if(taille==4 && coordXcursor>(unite*2) && coordXcursor<(unite*3)) y = 2;
                    else if(taille==4 && coordXcursor>(unite*3) && coordXcursor<(unite*4)) y = 3;
                    if(taille==3 && coordYcursor<unite) x = 0;
                    else if(taille==3 && coordYcursor>unite && coordYcursor<(unite*2)) x = 1;
                    else if(taille==3 && coordYcursor>(unite*2) && coordYcursor<(unite*3)) x = 2;
 
                    if(taille==3 && coordXcursor<unite) y = 0;
                    else if(taille==3 && coordXcursor>unite && coordXcursor<(unite*2)) y = 1;
                    else if(taille==3 && coordXcursor>(unite*2) && coordXcursor<(unite*3)) y = 2;
                    
                    cord_ok=verif_coordonne(grille, taille, x, y);                
                }
                break;
        }

    }
    update_matrice(grille,x,y,joueur);
    return;
}

void partie1vs1(int* context,SDL_Surface *ecran,int taille)
{
    morpion grille = NULL;
    char joueur;
    int victoire_joueur;
    int tour, maxTour, jTour;

    grille = init_grille(grille,taille);
    afficher_grille_vide(context,ecran,taille);
    
    maxTour = taille*taille;
    tour = 0;
    victoire_joueur = -1;

    while(victoire_joueur!=1 && tour<maxTour){

        jTour = tour%2;
        if(jTour==0) joueur = '0';
        else joueur = '1';
        jouer(context,ecran,grille,taille,joueur);
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        update_interface(grille,taille,context,ecran);
    }
    SDL_Delay(1500);
    vider_memoire(grille, taille);

    afficher_gagnant(ecran,victoire_joueur,joueur);


    return;
}


int matriceIsFull(morpion grille,int taille){
  
  int i,j;
 
  for(i=0;i<taille;i++){
    for(j=0;j<taille;j++){
        if(grille[i][j] == 'x') return 0;
    }
  }

    return 1;
}

int min(morpion grille,int taille){
    int score = INFINI;
    int i,j,valeur;

    if(victoire(grille,taille,'1')) return 10;
    else if (victoire(grille,taille,'0')) return -10;
    else if(matriceIsFull(grille,taille)==1) return 0;

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '0';
                valeur = max(grille,taille);
                if(score>valeur){
                    score = valeur;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

int max(morpion grille,int taille){
    int score = -INFINI;
    int i,j,valeur;

    if(victoire(grille,taille,'1')) return 10;
    else if (victoire(grille,taille,'0')) return -10;
    else if(matriceIsFull(grille,taille)==1) return 0;

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '1';
                valeur = min(grille,taille);
                if(score<valeur){
                    score = valeur;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

int minmax(morpion grille,int taille,int* bestI,int* bestJ){
    int score = INFINI;
    int i,j,valeur;

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '0';
                valeur = max(grille,taille);
                if(score>valeur){
                    score = valeur;
                    *bestI = i;
                    *bestJ = j;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

//ALPHA-BETA
void calcIA(morpion grille,int taille, int prof, int* x,int* y)
{
    int i,j,tmp;
    int maxi=-1,maxj=-1;
    int alpha = -INFINI;
    int beta = INFINI;

    //On met en place le joueur courant
    //joueurCourant = jeu->getTour();

    //Si la profondeur est nulle ou la partie est finie, 
    //on ne fait pas le calcul
    if((prof!=0)||(!matriceIsFull(grille,taille)))
        {
	//On parcourt les cases du morpion
        for(i=0;(i<taille); i++)
            for(j=0;(j<taille);j++)
                {
		//Si la case est vide
                if(grille[i][j])
                    {
                    //On simule qu'on joue cette case
                    grille[i][j]='1';
		    //On appelle la fonction calcMin pour lancer l'IA
                    tmp = calcMin(grille,taille, prof-1,alpha,beta);

		    //Si ce score est plus grand
                    if(alpha<tmp)
                        {
			//On le choisit
                        alpha = tmp;
                        maxi = i;
                        maxj = j;
                        }
 
		    //On annule le coup
                    grille[i][j]='x';
                    }
                }
        }
    //On jouera le coup maximal
    i=maxi;
    j=maxj;    
}

int calcMin(morpion grille,int taille, int prof, int alpha, int beta)
{
    int i,j,tmp;

    if(prof==0)
       {
        if(victoire(grille,taille,'1')) return 10;
        else if (victoire(grille,taille,'0')) return -10;
        else if(matriceIsFull(grille,taille)==1) return 0;
       }

    if(matriceIsFull(grille,taille)==1)
       {
	    if(victoire(grille,taille,'1')) return 10;
        else if (victoire(grille,taille,'0')) return -10;
        else if(matriceIsFull(grille,taille)==1) return 0;
       }
    
    //On parcourt le plateau de jeu et on le joue si la case est vide
    for(i=0;i<taille; i++)
        for(j=0;j<taille;j++)
            {
            if(grille[i][j]=='x')
                {
		//On joue le coup
                grille[i][j]='O';

                tmp = calcMax(grille,taille, prof-1,alpha,beta);
		
		//On annule le coup
                grille[i][j]='x';

		//Mis a jour de beta
		if(beta>tmp)
		    {
		    beta = tmp;
		    }

		if(beta<=alpha)
			{
		        return beta;
			}
                }
            }
    return beta;
}

int calcMax(morpion grille,int taille, int prof, int alpha, int beta)
{
    int i,j,tmp;

    if(prof==0)
       {
        if(victoire(grille,taille,'1')) return 10;
        else if (victoire(grille,taille,'0')) return -10;
        else if(matriceIsFull(grille,taille)==1) return 0;
       }

    if(matriceIsFull(grille,taille)==1)
       {
	    if(victoire(grille,taille,'1')) return 10;
        else if (victoire(grille,taille,'0')) return -10;
        else if(matriceIsFull(grille,taille)==1) return 0;
       }
    
    for(i=0;i<taille; i++)
        for(j=0;j<taille;j++)
            {
            if(grille[i][j]=='x')
                {
                grille[i][j]='1';

                tmp = calcMin(grille,taille, prof-1,alpha,beta);
		
                grille[i][j]='x';
		
		//Mis a jour de la valeur de alpha
		if(alpha<tmp)
		    {
		    alpha = tmp;
		    }

		if(beta <= alpha)
		    {
		    return alpha;
		    }
                }
            }
    
    return alpha;
}


//L'IA utilise le MINIMAX classique
void iaJoue(int* context,SDL_Surface *ecran, morpion grille, int taille, char joueur)
{
    int x,y;
    
    minmax(grille,taille,&x,&y);
    update_matrice(grille,x,y,joueur);
}

void iaJoueSwitchingPlayer(int* context,SDL_Surface *ecran, morpion grille, int taille, char joueur)
{
    int x,y;
    
    minmaxSwitchingPlayer(grille,taille,&x,&y,joueur);
    update_matrice(grille,x,y,joueur);
}

void partieIAvsJoueur(int* context,SDL_Surface *ecran,int taille)
{
    morpion grille = NULL;
    char joueur;
    int victoire_joueur;
    int tour, maxTour, jTour,tourDeJeu;

    grille = init_grille(grille,taille);
    afficher_grille_vide(context,ecran,taille);
    
    maxTour = taille*taille;
    tour = 0;
    tourDeJeu = rand() % 2;
    victoire_joueur = -1;

    while(victoire_joueur!=1 && tour<maxTour){

        jTour = tourDeJeu%2;
        if(jTour==0) {
            joueur = '0';
            iaJoue(context,ecran,grille,taille,joueur);
            
        }else{ 
            joueur = '1';
            jouer(context,ecran,grille,taille,joueur);
            
        }
        
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        tourDeJeu++;
        update_interface(grille,taille,context,ecran);
    }
    SDL_Delay(1500);
    vider_memoire(grille, taille);

    afficher_gagnant(ecran,victoire_joueur,joueur);


    return;
}
//IA vs IA
void partieIAvsIA(int* context,SDL_Surface *ecran,int taille)
{
    morpion grille = NULL;
    char joueur;
    int victoire_joueur;
    int tour, maxTour, jTour,tourDeJeu;

    grille = init_grille(grille,taille);
    afficher_grille_vide(context,ecran,taille);
    
    maxTour = taille*taille;
    tour = 0;
    tourDeJeu = rand() % 2;
    victoire_joueur = -1;

    while(victoire_joueur!=1 && tour<maxTour){

        jTour = tourDeJeu%2;
        if(jTour==0) {
            joueur = '0';
            iaJoueSwitchingPlayer(context,ecran,grille,taille,joueur);
            
        }else{ 
            joueur = '1';
            iaJoueSwitchingPlayer(context,ecran,grille,taille,joueur);
            
        }
        
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        tourDeJeu++;
        SDL_Delay(100);
        update_interface(grille,taille,context,ecran);
    }
    SDL_Delay(1500);
    vider_memoire(grille, taille);

    afficher_gagnant(ecran,victoire_joueur,joueur);


    return;
}


int minSwitchingPlayer(morpion grille,int taille,int currentPlayer){
    int score = INFINI;
    int i,j,valeur;
    char nextPlayer = 0;

    if(currentPlayer=='0') nextPlayer = '1';

    if(victoire(grille,taille,'1')) return 10;
    else if (victoire(grille,taille,'0')) return -10;
    else if(matriceIsFull(grille,taille)==1) return 0;

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '0';
                valeur = maxSwitchingPlayer(grille,taille,nextPlayer);
                if(score>valeur){
                    score = valeur;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

int maxSwitchingPlayer(morpion grille,int taille,int currentPlayer){
    int score = -INFINI;
    int i,j,valeur;
    char nextPlayer = 0;

    if(currentPlayer=='0') nextPlayer = '1';

    if(victoire(grille,taille,'1')) return 10;
    else if (victoire(grille,taille,'0')) return -10;
    else if(matriceIsFull(grille,taille)==1) return 0;

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '1';
                valeur = minSwitchingPlayer(grille,taille,nextPlayer);
                if(score<valeur){
                    score = valeur;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

int minmaxSwitchingPlayer(morpion grille,int taille,int* bestI,int* bestJ,char currentPlayer){
    int score = INFINI;
    int i,j,valeur;
    char nextPlayer = 0;

    if(currentPlayer=='0') nextPlayer = '1';

    for (i=0;i<taille;i++)
    {
        for (j=0;j<taille;j++)
        {
            if(grille[i][j]=='x'){
                grille[i][j] = '0';
                valeur = maxSwitchingPlayer(grille,taille,nextPlayer);
                if(score>valeur){
                    score = valeur;
                    *bestI = i;
                    *bestJ = j;
                    
                }
                grille[i][j] = 'x'; 
            }       
        }   
    }
       
    return score;
}

//FONCTIONS LIEES A L'INTERFACE GRAPHIQUE

void choix_taille_grille(int* context,SDL_Surface *ecran,int type_partie){
    
    *context = SELECT_TAILLE;
    int taille;
    SDL_Event event;
    int continuerChoixTaille = 1;

    SDL_Surface *texte_choix = NULL;
    SDL_Surface *buttonPointeur_choix = NULL;
    SDL_Surface *taille3 = NULL;
    SDL_Surface *taille4 = NULL;
    /*SDL_Surface *taille5 = NULL;
    SDL_Surface *taille6 = NULL;
    SDL_Surface *taille7 = NULL;
    SDL_Surface *taille8 = NULL;*/
    
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
    

    police = TTF_OpenFont("ka.ttf", 40);
    texte_choix = TTF_RenderText_Blended(police, "Taille de la grille", couleurNoire);
    police = TTF_OpenFont("ka.ttf", 30);
    buttonPointeur_choix = TTF_RenderText_Blended(police, "@", couleurNoire);
    police = TTF_OpenFont("ka.ttf", 30);
    taille3 = TTF_RenderText_Blended(police, "3", couleurNoire);
    taille4 = TTF_RenderText_Blended(police, "4", couleurNoire);
    /*taille5 = TTF_RenderText_Blended(police, "5", couleurNoire);
    taille6 = TTF_RenderText_Blended(police, "6", couleurNoire);
    taille7 = TTF_RenderText_Blended(police, "7", couleurNoire);
    taille8 = TTF_RenderText_Blended(police, "8", couleurNoire);
    */
   
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    positionText_choix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2);
    positionText_choix.y = 50;
    SDL_BlitSurface(texte_choix, NULL, ecran, &positionText_choix);

    positionPointeurChoix.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2) - 25;
    positionPointeurChoix.y = 100;
    SDL_BlitSurface(buttonPointeur_choix, NULL, ecran, &positionPointeurChoix);

    positionTaille3.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2 +10);
    positionTaille3.y = 100;
    SDL_BlitSurface(taille3, NULL, ecran, &positionTaille3);

    positionTaille4.x =  (LONGUEUR_GRILLE/2 - texte_choix->w/2 +10);
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
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
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
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
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
                            if(type_partie==3) partieIAvsIA(context,ecran,taille);
                        }
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }

    
}

void playmusique(Mix_Music *musique){
  
   musique = Mix_LoadMUS("music/song.mp3"); //Chargement de la musique
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
   
}

void menu(int *context){

    *context = MENU;
    int continuer = 1;
    int type_partie;
    int playMusique = 1;
    SDL_Event event;

    SDL_Surface *ecran = NULL;
    SDL_Surface *buttonJ1vsJ2 = NULL;
    SDL_Surface *buttonJvsIA = NULL;
    SDL_Surface *buttonIAvsIA = NULL;
    SDL_Surface *buttonQuitter = NULL;
    SDL_Surface *buttonPointeur_menu = NULL;

    SDL_Surface *texte_mute = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *texte_dev = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};

    SDL_Rect positionBJ1vsJ2;
    SDL_Rect positionBJvsIA;
    SDL_Rect positionBQuitter;
    SDL_Rect positionBIAvsIA;
    SDL_Rect positionTitre;
    SDL_Rect positionPointeurMenu;
    SDL_Rect positionMuteButton;
    SDL_Rect positionTextdev;

    Mix_Music *musique = NULL; //Création du pointeur de type Mix_Music
    

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    TTF_Init();

    ecran = SDL_SetVideoMode(LONGUEUR_GRILLE, LARGEUR_GRILLE, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    
    /* Chargement de la police */
    police = TTF_OpenFont("ka.ttf", 65);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, "Tic Tact Toe", couleurNoire);

    police = TTF_OpenFont("ka.ttf", 25);
    buttonQuitter =TTF_RenderText_Blended(police, "Quitter", couleurNoire);
    buttonJ1vsJ2 = TTF_RenderText_Blended(police, "Joueur 1 VS Joueur 2", couleurNoire);
    buttonIAvsIA = TTF_RenderText_Blended(police,"IA vs IA",couleurNoire);
    buttonJvsIA =  TTF_RenderText_Blended(police, "Joueur VS IA MinMax", couleurNoire);
    police = TTF_OpenFont("ka.ttf", 20);
    buttonPointeur_menu = TTF_RenderText_Blended(police,"@",couleurNoire);
    police = TTF_OpenFont("ka.ttf", 15);
    texte_mute = TTF_RenderText_Blended(police,"Musique Play Resume",couleurNoire);
    police = TTF_OpenFont("ka.ttf", 10);
    texte_dev = TTF_RenderText_Blended(police,"Hanry Nzale  Cheick Gnankene © POLYTECH MARSEILLE 2020", couleurNoire);

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
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    positionBJ1vsJ2.x = (LONGUEUR_GRILLE / 2) - (buttonJ1vsJ2->w/2);
    positionBJ1vsJ2.y = (LARGEUR_GRILLE / 2) - (50 / 2);
    SDL_BlitSurface(buttonJ1vsJ2, NULL, ecran, &positionBJ1vsJ2);

    positionBJvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonJvsIA->w / 2);
    positionBJvsIA.y = positionBJ1vsJ2.y + 56;
    SDL_BlitSurface(buttonJvsIA, NULL, ecran, &positionBJvsIA);
    
    positionBIAvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonIAvsIA->w / 2);
    positionBIAvsIA.y = positionBJvsIA.y + 56;
    SDL_BlitSurface(buttonIAvsIA, NULL, ecran, &positionBIAvsIA);

    positionBQuitter.x = (LONGUEUR_GRILLE / 2) - (buttonQuitter->w / 2);
    positionBQuitter.y = positionBIAvsIA.y + 56;
    SDL_BlitSurface(buttonQuitter, NULL, ecran, &positionBQuitter);

    positionPointeurMenu.x = positionBJ1vsJ2.x - 25;
    positionPointeurMenu.y = positionBJ1vsJ2.y;
    SDL_BlitSurface(buttonPointeur_menu, NULL, ecran, &positionPointeurMenu);

    positionTitre.x =  (LONGUEUR_GRILLE/2 - texte->w/2);
    positionTitre.y = 50;
    SDL_BlitSurface(texte, NULL, ecran, &positionTitre); /* Blit du texte */

    positionMuteButton.x= (LONGUEUR_GRILLE / 2) - (texte_mute->w / 2);
    positionMuteButton.y= LARGEUR_GRILLE - 100;
    SDL_BlitSurface(texte_mute, NULL, ecran, &positionMuteButton);

    positionTextdev.x = 30;
    positionTextdev.y = LONGUEUR_GRILLE - 30;
    SDL_BlitSurface(texte_dev, NULL, ecran, &positionTextdev);

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
                                            &positionPointeurMenu, positionTitre,
                                                texte_mute,positionMuteButton,
                                                    buttonIAvsIA, positionBIAvsIA,
                                                    texte_dev,positionTextdev);
                        }
                        break;
                    case SDLK_DOWN: // Flèche bas
                        if(positionPointeurMenu.y<positionBQuitter.y && *context==MENU){
                            navigationInMenu(-1,ecran,
                            buttonJ1vsJ2,buttonJvsIA,buttonQuitter,
                                buttonPointeur_menu,
                                    texte, positionBJ1vsJ2,positionBJvsIA,
                                        positionBQuitter,
                                            &positionPointeurMenu, positionTitre,
                                                texte_mute,positionMuteButton,
                                                    buttonIAvsIA,positionBIAvsIA,
                                                        texte_dev,positionTextdev);
                                            
                        }
                        break;
                    case SDLK_RETURN:
                        if(*context==MENU){
                            SDL_FreeSurface(buttonJ1vsJ2);
                            SDL_FreeSurface(buttonJvsIA);
                            SDL_FreeSurface(buttonQuitter);
                            SDL_FreeSurface(buttonPointeur_menu);
                            SDL_FreeSurface(texte);
                            SDL_FreeSurface(texte_dev);
                            SDL_FreeSurface(texte_mute);
                            SDL_FreeSurface(buttonIAvsIA);
                            if(positionPointeurMenu.y==positionBJ1vsJ2.y) {
                                type_partie =1;
                                choix_taille_grille(context,ecran,type_partie);
                            }
                            if(positionPointeurMenu.y==positionBJvsIA.y){ 
                                type_partie =2;
                                choix_taille_grille(context,ecran,type_partie);
                            }
                            if(positionPointeurMenu.y==positionBIAvsIA.y){
                                type_partie = 3;
                                choix_taille_grille(context,ecran,type_partie);
                            }
                            
                            if(positionPointeurMenu.y==positionBQuitter.y) continuer = 0;
                            
                        
                            
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.x>=((LONGUEUR_GRILLE / 2) - (texte_mute->w / 2)) && event.button.x<=((LONGUEUR_GRILLE / 2) + (texte_mute->w) -  (texte_mute->w / 2))
                                     && event.button.y>=(LONGUEUR_GRILLE - 100) && event.button.y<=(LONGUEUR_GRILLE - 100 + texte_mute->h)){
                     if(playMusique==1){
                        Mix_PauseMusic();
                        playMusique = -1;
                        }
                     else {
                        Mix_ResumeMusic();
                        playMusique = 1;
                     }
                }
                break;
            default:
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
    SDL_FreeSurface(buttonIAvsIA);
    SDL_FreeSurface(texte_mute);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte_dev);
    SDL_FreeSurface(texte_mute);
    
}

void navigationInMenu(int positionYPointeur,SDL_Surface *ecran,
        SDL_Surface *buttonJ1vsJ2,SDL_Surface *buttonJvsIA,SDL_Surface *buttonQuitter,
            SDL_Surface *buttonPointeur_menu,
                SDL_Surface *texte, SDL_Rect positionBJ1vsJ2,SDL_Rect positionBJvsIA,
                    SDL_Rect positionBQuitter,
                        SDL_Rect *positionPointeurMenu, SDL_Rect positionTitre,
                            SDL_Surface *texte_mute,SDL_Rect positionMuteButton,
                                SDL_Surface *buttonIAvsIA, SDL_Rect positionBIAvsIA,
                                    SDL_Surface *texte_dev, SDL_Rect positionTextdev){

    // Coloration de la surface ecran 
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,255, 255, 255));

    positionBJ1vsJ2.x = (LONGUEUR_GRILLE / 2) - (buttonJ1vsJ2->w/2);
    positionBJ1vsJ2.y = (LARGEUR_GRILLE / 2) - (50 / 2);
    SDL_BlitSurface(buttonJ1vsJ2, NULL, ecran, &positionBJ1vsJ2);

    positionBJvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonJvsIA->w / 2);
    positionBJvsIA.y = positionBJ1vsJ2.y + 56;
    SDL_BlitSurface(buttonJvsIA, NULL, ecran, &positionBJvsIA);

    positionBIAvsIA.x = (LONGUEUR_GRILLE / 2) - (buttonIAvsIA->w / 2);
    positionBIAvsIA.y = positionBJvsIA.y + 56;
    SDL_BlitSurface(buttonIAvsIA, NULL, ecran, &positionBIAvsIA);

    positionBQuitter.x = (LONGUEUR_GRILLE / 2) - (buttonQuitter->w / 2);
    positionBQuitter.y = positionBIAvsIA.y + 56;
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

    positionMuteButton.x= (LONGUEUR_GRILLE / 2) - (texte_mute->w / 2);
    positionMuteButton.y= LARGEUR_GRILLE - 100;
    SDL_BlitSurface(texte_mute, NULL, ecran, &positionMuteButton);

    positionTextdev.x = 30;
    positionTextdev.y = LONGUEUR_GRILLE - 30;
    SDL_BlitSurface(texte_dev, NULL, ecran, &positionTextdev);

    /* Mise à jour de l'écran avec sa nouvelle couleur */
    SDL_Flip(ecran);
}
