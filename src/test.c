#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "threetogo.h"
#include "token.h"
#include "ascii.h"
#include "moteur.h"

int main(void) {
    srand(time(NULL));
    Liste tokens = NULL;
    Liste queue = NULL;

    int score = 0;
    int tmp;

    char choix;

    init_queue(&queue);

    while (1) {
        printf("Queue : ");
        print_tokens(queue);

        printf("Tokens :\n");
        print_tokens(tokens);

        printf("\nl ou r : ");
        scanf(" %c", &choix);

        /* Ajout à gauche ou à droite */
        switch (choix) {
            case 'l':
                add_left(&queue, &tokens);
                break;
            case 'r':
                add_right(&queue, &tokens);
                break;
            case 'c':
                shift_color_left(&tokens, tokens->next);
                break;
            case 's':
                shift_shape_left(&tokens, tokens->next);
                break;
            default:
                printf("Erreur");
                break;
        }

        /* On s'assure de prendre en compte des combos (combinaisons qui apparaissent après un premier check) */
        while ((tmp = check_combinations(&tokens)) > 0) {
            score += tmp;
        }

        printf("Score actuel : %d\n\n", score);
    }


    return 0;
}