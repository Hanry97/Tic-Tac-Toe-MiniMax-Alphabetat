#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"


int main(int argc, char *argv[])
{
    int context = MAIN;

    menu(&context);
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}




