#include <stdio.h>
#include <stdlib.h>
#include "threetogo.h"
#include "moteur.h"

int main(void) {
    Token* token_1 = alloc_token(RED, 0);
    Token* token_2 = alloc_token(GREEN, 0);
    Token* token_3 = alloc_token(BLUE, 0);

    Liste tokens = create_liste(token_1);
    attach_to_tail(token_2, &tokens);
    attach_to_tail(token_3, &tokens);

    printf("Couleur token 1 : %d\n", tokens->couleur);
    printf("Couleur token 2 : %d\n", tokens->suivant->couleur);
    printf("Couleur token 3 : %d\n", tokens->suivant->suivant->couleur);
    printf("Couleur token 1 : %d\n", tokens->suivant->suivant->suivant->couleur);

    return 0;
}