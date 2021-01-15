#include <stdlib.h>
#include <time.h>
#include "threetogo.h"
#include "graphique.h"
#include "MLV/MLV_all.h"

int main(void) {
    /* Initialisation de la graine du générateur aléatoire */
    srand(time(NULL));

    /* Initialisation de la partie */
    Game game;
    if (game_init(&game) != 1) {
        printf("Une erreur inattendue est survenue pendant l'initialisation du programme\n");
        return 1;
    }
    window_open(SIZEX, SIZEY);
    MLV_change_frame_rate(FRAME_RATE);

    /* Boucle principale */
    if (game_loop(&game) != 1) {
        printf("Une erreur inattendue est survenue pendant l'exécution du programme\n");
        return 1;
    }
    

    /* Libération de la mémoire */
    game_free(&game);
    MLV_free_window();

    return 0;
}