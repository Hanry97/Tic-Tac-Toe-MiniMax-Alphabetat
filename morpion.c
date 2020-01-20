#include <stdio.h>
#include <stdlib.h>
#include "morpion_simple.h"


int main(){

    int partie, game;

    game = 1;
    
    while(game == 1){
        system("clear");

        printf(" Jeux du morpion : \n");
        printf(" ---------------   \n");
        printf("\n");
        printf(" 1 - Joueur 1 vs Joueur 2 \n");
        printf(" 2 - Joueur Vs IA min-Max \n");
        printf(" 3 - IA min-Max Vs IA min-Max \n");
        printf(" 4 - Quitter le jeux \n");
        printf("\n choix utilisateur : ");
        scanf("%d", &partie);
        system("clear");
        
        switch (partie)
        {
        case 1:
            partie1vs1();
            break;
        case 2:
            partieIAvsJoueur();
            break;
        case 3:
            partieIAvsIA();
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
         
    }
    return 0;
}