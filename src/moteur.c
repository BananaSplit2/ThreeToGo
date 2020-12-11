#include <stdio.h>
#include <stdlib.h>
#include "threetogo.h"
#include "moteur.h"

Token *alloc_token(int color, int shape) {
    Token *tmp = (Token*) malloc(sizeof(Token));
    if (tmp != NULL) {
        tmp->color = color;
        tmp->shape = shape;
        tmp->next = tmp;
        tmp->next_color = tmp;
        tmp->previous_color = tmp;
        tmp->next_shape = tmp;
        tmp->previous_shape = tmp;
    }
    return tmp;
}

void print_tokens(Liste tokens) {
    Token *tmp = tokens->next;
    do {
        printf("(%d, %d) -> ", tmp->color, tmp->shape);
        tmp = tmp->next;
    } while(tmp->next != tokens->next->next);
    printf("\n");
}

Token *next_shape(Token *token) {
    if (token == NULL) {
        return NULL;
    }

    Token *tmp = token->next;
    while (tmp->shape != token->shape) {
        tmp = tmp->next;
    }
    return tmp;
}

Token *next_color(Token *token) {
    if (token == NULL) {
        return NULL;
    }

    Token *tmp = token->next;
    while (tmp->color != token->color) {
        tmp = tmp->next;
    }
    return tmp;
}

void update_shape_links(Token *token) {
    Token *next = next_shape(token);
    Token *previous = next->previous_shape;

    /* MaJ du chainage double */
    token->next_shape = next;
    token->previous_shape = previous;
    next->previous_shape = token;
    previous->next_shape = token;
}

void update_color_links(Token *token) {
    Token *next = next_color(token);
    Token *previous = next->previous_color;

    /* MaJ du chainage double */
    token->next_color = next;
    token->previous_color = previous;
    next->previous_color = token;
    previous->next_color = token;
}

void attach_to_head(Liste *liste, Token *source) {
    if (*liste == NULL) {
        /* Initialisation de la liste */
        *liste = source;
    }
    else {
        /* Chainage de source au premier token de la liste */
        source->next = (*liste)->next;

        /* Chainage du dernier token à source */
        (*liste)->next = source;

        /* MaJ du chainage couleur/forme */
        update_shape_links(source);
        update_color_links(source);

    } 
}

void attach_to_tail(Liste *liste, Token *source) {
    if (*liste == NULL) {
        *liste = source;
    }
    else {
        /* Chainage de source au premier token de la liste */
        source->next = (*liste)->next;

        /* Chainage du dernier token à source */
        (*liste)->next = source;

        /* Source devient le nouveau dernier token de la liste */
        *liste = source;

        /* MaJ du chainage couleur/forme */
        update_shape_links(source);
        update_color_links(source);
    }
}