#ifndef _MORPION_SIMPLE_H
#define _MORPION_SIMPLE_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

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

void calcIA(morpion grille, int taille,int prof,int* bestI,int* bestJ);
int calcMin(morpion grille, int taille,int prof, int alpha, int beta);
int calcMax(morpion grille, int taille,int prof, int alpha, int beta);


void partieIAvsIA();


void afficher_grille_vide(int* context,SDL_Surface *ecran,int taille);
void update_interface(morpion grille, int taille,int* context,SDL_Surface *ecran);
void afficher_gagnant(SDL_Surface *ecran,int victoire_joueur,char joueur);

#endif
