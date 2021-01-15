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
    game_init(&game);
    window_open(SIZEX, SIZEY);

    /* Boucle principale */
    game_loop(&game);

    /* Libération de la mémoire */
    game_free(&game);
    MLV_free_window();

    return 1;
}