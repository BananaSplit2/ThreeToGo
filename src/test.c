#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "threetogo.h"
#include "token.h"
#include "ascii.h"

void createRandom(Liste *lst, int n) {
    int i;
    for (i = 0 ; i < n ; i++) {
        Token *tok = alloc_token(rand()%4, rand()%4);
        attach_to_tail(lst, tok);
    }
}

int main(void) {
    srand(time(NULL));
    Liste tokens = NULL;

    createRandom(&tokens, 4);

    print_tokens(tokens);

    printf("Chainage vert : ");
    print_colorlinks(tokens, GREEN);

    printf("\n apres permutation premier et dernier \n");
    swap(&tokens, tokens, tokens->next);

    print_tokens(tokens);

    printf("Chainage vert : ");
    print_colorlinks(tokens, GREEN);

    return 0;
}