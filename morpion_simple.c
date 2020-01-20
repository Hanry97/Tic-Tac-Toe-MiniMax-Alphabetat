#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "morpion_simple.h"


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

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));

    police = TTF_OpenFont("alphawood.ttf", 65);
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
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));
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
            else SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 119, 136, 153)); 
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
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 194, 194, 194));
    unite = LONGUEUR_GRILLE/taille;
    
    case_grille = SDL_CreateRGBSurface(SDL_HWSURFACE, unite, unite, 32, 0, 0, 0, 0);

    police = TTF_OpenFont("alphawood.ttf", 70);

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
                pion = TTF_RenderText_Blended(police, "X", couleurNoire);
            }else if(grille_pion[i][j]=='0'){
                pion = TTF_RenderText_Blended(police, "O", couleurNoire);
            }else{
                pion = TTF_RenderText_Blended(police, "", couleurNoire);
            }
            
            positionPion.x =  (position.x) + (unite/2) - 30;
            positionPion.y = (position.y) + (unite/2) - 30;
            
            if(k==0)
            SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 245, 255, 255));
            else SDL_FillRect(grille[i][j], NULL, SDL_MapRGB(ecran->format, 119, 136, 153)); 
            SDL_BlitSurface(grille[i][j], NULL, ecran, &position); // Collage de la surface sur l'écran
            SDL_BlitSurface(pion, NULL, ecran, &positionPion);
            k++;
            
        }
        
        if(taille%2==0) k++;
    }
    
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
        else{
            return 2; //y pas conforme
        }
    }
    else{
        return 3;//x pas conforme
    }
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

                    if(taille==4 && ((coordXcursor%unite)<unite)) y = 0;
                    else if(taille==4 && ((coordXcursor%unite)<unite*2)) y = 1;
                    else if(taille==4 && ((coordXcursor%unite)<unite*3)) y = 2;
                    else if(taille==4 && ((coordXcursor%unite)<unite*4)) y = 3;

                    if(taille==4 && ((coordYcursor%unite)<unite)) x = 0;
                    else if(taille==4 && ((coordYcursor%unite)<unite*2)) x = 1;
                    else if(taille==4 && ((coordYcursor%unite)<unite*3)) x = 2;
                    else if(taille==4 && ((coordYcursor%unite)<unite*4)) x = 3;

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
    morpion grille;
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
            jouer(context,ecran,grille,taille,joueur);
            fprintf(stderr, "IA a jouer\n");
        }else{ 
            joueur = '1';
            jouer(context,ecran,grille,taille,joueur);
            fprintf(stderr, "Joueur a jouer\n");
        }
        
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        tourDeJeu++;
        update_interface(grille,taille,context,ecran);
    }

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

/*void calcIA(morpion grille,int taille, int prof, int* x,int* y)
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
}*/



void iaJoue(int* context,SDL_Surface *ecran, morpion grille, int taille, char joueur)
{
    int x,y;
    
    minmax(grille,taille,&x,&y);
    update_matrice(grille,x,y,joueur);
}

void partieIAvsJoueur(int* context,SDL_Surface *ecran,int taille)
{
    morpion grille;
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
            fprintf(stderr, "IA a jouer\n");
        }else{ 
            joueur = '1';
            jouer(context,ecran,grille,taille,joueur);
            fprintf(stderr, "Joueur a jouer\n");
        }
        
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        tourDeJeu++;
        update_interface(grille,taille,context,ecran);
    }

    vider_memoire(grille, taille);

    afficher_gagnant(ecran,victoire_joueur,joueur);


    return;
}

/*void partieIAvsIA(){
    morpion grille;
    int taille;
    char joueur;
    int victoire_joueur;
    int tour, maxTour, jTour,tourDeJeu;

    printf("Taille de la grille : ");
    scanf("%d", &taille);
    system("clear");
    affiche_grille_vide(taille);
    grille = init_grille(grille,taille);
    
    
    maxTour = taille*taille;
    tour = 0;
    tourDeJeu = rand() % 2;
    victoire_joueur = -1;

    while(victoire_joueur!=1 && tour<maxTour){

        jTour = tourDeJeu%2;
        if(jTour==0) {
            joueur = '0';
            iaJoue(grille,taille,joueur);
        }else{ 
            joueur = '1';
            iaJoue(grille,taille,joueur);
        }
        
        victoire_joueur = victoire(grille,taille,joueur);
        tour++;
        tourDeJeu++;
        update_screen(grille,taille);
    }

    vider_memoire(grille, taille);

    if(victoire_joueur == 1){
        printf("\n \n Partie finie le joueur %c gagne. \n", joueur);
    }else{
        printf("\n \n Match nul! \n");
    }

    printf("\n Presser [Entrer] pour revenir au menu ...");
    fflush(stdin);
    while(getchar()!='\n');
    getchar();

    return;
}*/
