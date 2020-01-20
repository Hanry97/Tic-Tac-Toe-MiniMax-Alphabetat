#ifndef _MORPION_H
#define _MORPION_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_image.h"

#define LONGUEUR_GRILLE 640
#define LARGEUR_GRILLE 640
#define INFINI 99999999
#define TRUE 1
#define FALSE 0
#define CASE_VIDE ' '
#define AUTRE_JOUEUR(joueur) (3-(joueur))
#define PERSONNE CASE_VIDE
#define MAIN 0
#define MENU 1
#define SELECT_TAILLE 2
#define GRILLE 3
#define JOUER_PION 4

typedef char** morpion;
typedef SDL_Surface*** plateau;

void affiche_grille_vide(int taille);
morpion init_grille(morpion grille, int taille);
void update_screen(morpion grille, int taille);
void vider_memoire(morpion grille, int taille);
int verif_coordonne(morpion grille,int taille, int x,int y);
void update_matrice(morpion grille,int x,int y, char joueur);
int victoire(morpion grille, int taille, char joueur);
int matriceIsFull(morpion grille,int taille);
void jouer(int* context,SDL_Surface *ecran,morpion grille, int taille, char joueur);
void partie1vs1(int* context,SDL_Surface *ecran,int taille);

//Algorithme MINIMAX
int min(morpion grille,int taille);
int max(morpion grille,int taille);
int minmax(morpion grille,int taille,int* bestI,int* bestJ);

int verifPartieTerminee(morpion grille,int taille,int nbrcaselibres);
int evaluation(morpion grille,int taille,char joueur,int nbrcaselibre);
int caseLibre(morpion grille,int i,int j);
void dejouerUnCoup(morpion grille,int i,int j,int* nbrcaselibre);
void jouerUnCoup(morpion grille,int i,int j,char joueur,int* nbrcaselibre);
int miniMaxVersion2(morpion grille,char joueur,char tourDeJeu,int *bestI, int *bestJ,int taille,int *nbrcaselibre);
void iaJoue(int* context,SDL_Surface *ecran, morpion grille, int taille, char joueur);
void partieIAvsJoueur(int* context,SDL_Surface *ecran,int taille);

//ALPHA-BETA Version 1
void calcIA(morpion grille, int taille,int prof,int* bestI,int* bestJ);
int calcMin(morpion grille, int taille,int prof, int alpha, int beta);
int calcMax(morpion grille, int taille,int prof, int alpha, int beta);


void partieIAvsIA();
void iaJoueSwitchingPlayer(int* context,SDL_Surface *ecran, morpion grille, int taille, char joueur);
int minSwitchingPlayer(morpion grille,int taille,int currentPlayer);
int maxSwitchingPlayer(morpion grille,int taille,int currentPlayer);
int minmaxSwitchingPlayer(morpion grille,int taille,int* bestI,int* bestJ,char currentPlayer);

//Fonctions liées à l'interface graphique
void afficher_grille_vide(int* context,SDL_Surface *ecran,int taille);
void update_interface(morpion grille, int taille,int* context,SDL_Surface *ecran);
void afficher_gagnant(SDL_Surface *ecran,int victoire_joueur,char joueur);

void choix_taille_grille(int* context,SDL_Surface *ecran,int type_partie);

void menu(int* context);
void playmusique(Mix_Music *musique);
void navigationInMenu(int positionYPointeur,SDL_Surface *ecran,
        SDL_Surface *buttonJ1vsJ2,SDL_Surface *buttonJvsIA,SDL_Surface *buttonQuitter,
            SDL_Surface *buttonPointeur_menu,
                SDL_Surface *texte, SDL_Rect positionBJ1vsJ2,SDL_Rect positionBJvsIA,
                    SDL_Rect positionBQuitter,
                        SDL_Rect *positionPointeurMenu, SDL_Rect positionTitre,
                            SDL_Surface *texte_mute,SDL_Rect positionMuteButton,
                                SDL_Surface *buttonIAvsIA, SDL_Rect positionBIAvsIA,
                                    SDL_Surface *texte_dev, SDL_Rect positionTextdev);

#endif
