#include <stdio.h>
#include <stdlib.h>
#include "threetogo.h"
#include "moteur.h"

int main(void) {
    Liste tokens = NULL;

    Token* tok_1 = alloc_token(RED, TRIANGLE);
    Token* tok_2 = alloc_token(GREEN, TRIANGLE);
    Token* tok_3 = alloc_token(BLUE, SQUARE);
    Token* tok_4 = alloc_token(RED, CIRCLE);
    Token* tok_5 = alloc_token(GREEN, SQUARE);
    Token* tok_6 = alloc_token(GREEN, CIRCLE);
    Token* tok_7 = alloc_token(BLUE, TRIANGLE);
    Token* tok_8 = alloc_token(BLUE, DIAMOND);
    
    attach_to_tail(&tokens, tok_1);
    attach_to_tail(&tokens, tok_2);
    attach_to_tail(&tokens, tok_3);
    attach_to_tail(&tokens, tok_4);
    attach_to_tail(&tokens, tok_5);
    attach_to_tail(&tokens, tok_6);
    attach_to_tail(&tokens, tok_7);
    attach_to_tail(&tokens, tok_8);

    print_tokens(tokens);

    printf("(%d, %d) -> ", tok_1->color, tok_1->shape);
    printf("(%d, %d) -> ", tok_1->previous_shape->color, tok_1->previous_shape->shape);
    printf("(%d, %d) -> ", tok_1->previous_shape->previous_shape->color, tok_1->previous_shape->previous_shape->shape);
    printf("(%d, %d) -> ", tok_1->previous_shape->previous_shape->previous_shape->color, tok_1->previous_shape->previous_shape->previous_shape->shape);
    printf("\n");

    return 0;
}