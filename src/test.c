#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "threetogo.h"
#include "token.h"
#include "ascii.h"
#include "moteur.h"

int main(void) {
    srand(time(NULL));
    Liste tokens = NULL, queue = NULL;

    int tmp, score = 0;
    char choix, continuer = 1;

    init_queue(&queue);

    while (continuer == 1) {
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
                shift_commoncolor_left(&tokens, tokens->next);
                break;
            case 's':
                shift_commonshape_left(&tokens, tokens->next);
                break;
            case 'e':
                continuer = 0;
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

    /* Libération de la mémoire */
    free_liste(&queue);
    free_liste(&tokens);

    return 0;
}