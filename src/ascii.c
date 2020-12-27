#include <stdio.h>
#include "ascii.h"

char repr_color(int color) {
    switch (color) {
        case 0:
            return 'r';
        case 1:
            return 'v';
        case 2:
            return 'b';
        case 3:
            return 'j';
    }
    return 0;
}

char repr_shape(int shape) {
    switch (shape) {
        case 0:
            return 'O';
        case 1:
            return 'C';
        case 2:
            return 'T';
        case 3:
            return 'D';
    }
    return 0;
}

void print_tokens(Liste tokens) {
    if (tokens == NULL) {
        printf("(Vide)\n");
        return;
    }
    Token *tmp = tokens->next;
    do {
        printf("--> %c %c ", repr_shape(tmp->shape), repr_color(tmp->color));
        tmp = tmp->next;
    } while(tmp->next != tokens->next->next);
    printf("-->>\n");
}

void print_colorlinks(Liste tokens, int color) {
    Token *index = tokens;
    while (index->color != color && index->next != tokens) {
        index = index->next;
    }
    if (index->color != color) {
        printf("Vide\n");
    }
    else {
        Token *tmp = index;
        do {
            printf("<-> %c %c ", repr_shape(index->shape), repr_color(index->color));
            index = index->next_color;
        } while (index != tmp);
        printf("<->>\n");
    }
}
