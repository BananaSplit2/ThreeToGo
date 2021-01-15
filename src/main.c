#include <stdlib.h>
#include <time.h>
#include "threetogo.h"
#include "graphique.h"
#include "MLV/MLV_all.h"

int main(void) {
    /* Initialisation de la graine du générateur aléatoire */
    srand(time(NULL));

    /* Initialisation de la librarie MLV */
    window_open(SIZEX, SIZEY);
    MLV_change_frame_rate(FRAME_RATE);

    /* Initialisation des images */
    MLV_Image *images[10];
    int nb_images = images_init(images);

    /* Initialisation de la partie */
    Game game;
    if (game_init(&game) != 1) {
        printf("Une erreur inattendue est survenue pendant l'initialisation du programme\n");
        return 1;
    }

    /* Boucle principale */
    if (game_loop(&game, images) != 1) {
        printf("Une erreur inattendue est survenue pendant l'exécution du programme\n");
        return 1;
    }
    
    /* Libération de la mémoire */
    game_free(&game);
    images_free(images, nb_images);
    MLV_free_window();

    return 0;
}