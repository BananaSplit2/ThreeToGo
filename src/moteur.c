#include <stdio.h>
#include <stdlib.h>
#include "threetogo.h"
#include "moteur.h"

Token *alloc_token(int couleur, int forme) {
    Token *tmp = (Token*) malloc(sizeof(Token));
    if (tmp != NULL) {
        tmp->couleur = couleur;
        tmp->forme = forme;
    }d
    return tmp;
}

Liste create_liste(Token *single) {
    single->suivant = single;
    single->suivant_couleur = single;
    single->suivant_forme = single;
    single->precedent_couleur = single;
    single->precedent_forme = single;
    return single;
}

Token *find_tail(Liste liste) {
    Token *tmp = liste;
    while(tmp->suivant != liste) {
        tmp = tmp->suivant;
    }
    return tmp;
}

void attach_to_head(Token *single, Liste *liste) {
    /* Chainage de single au premier élément de la liste */
    single->suivant = *liste;

    /* Chainage du dernier élément à single */
    find_tail(*liste)->suivant = single;

    /* Le nouveau token devient la premier élément */
    *liste = single;
}

void attach_to_tail(Token *single, Liste *liste) {
    /* Chainage de single au premier élément de la liste */
    single->suivant = *liste;

    /* Chainage du dernier élément à single */
    find_tail(*liste)->suivant = single;
}