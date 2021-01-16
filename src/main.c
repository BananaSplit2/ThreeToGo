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
    if (MLV_init_audio()) {
        fprintf(stderr, "L'infrasctructure audio de la librairie MLV ne s'est pas initialisé\n");
        return 1;
    }

    /* Initialisation des images */
    MLV_Image *images[30];
    int nb_images = images_init(images);
    if (nb_images == 0) {
        printf("Une erreur inattendue est survenue pendant le chargement des images\n");
        return 1;
    }

    /* Initialisation de la police d'écriture */
    MLV_Font *police;
    police = MLV_load_font("assets/maturasc.ttf", RESO*0.6);
    if (police == NULL) {
        printf("Une erreur inattendue est survenue pendant de la police d'écriture\n");
        return 1;
    }

    /* Initialisation du son */
    MLV_Sound* sounds[10];
    int nb_sons = sons_init(sounds);
    if (nb_sons == 0) {
        printf("Une erreur inattendue est survenue pendant le chargement des sons\n");
        return 1;
    }

    /* Initialisation de la partie */
    Game game;
    if (game_init(&game) != 1) {
        printf("Une erreur inattendue est survenue pendant l'initialisation du programme\n");
        return 1;
    }

    /* Boucle principale */
    if (game_loop(&game, images, police, sounds) != 1) {
        printf("Une erreur inattendue est survenue pendant l'exécution du programme\n");
        return 1;
    }
    
    /* Libération de la mémoire */
    game_free(&game);
    images_free(images, nb_images);
    sons_free(sounds, nb_sons);
    MLV_free_font(police);
    MLV_free_window();

    return 0;
}