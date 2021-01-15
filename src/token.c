#include <stdlib.h>
#include <stdio.h>
#include "token.h"

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

int length(Liste tokens) {
    int i = 0;
    Token *index = tokens;
    if (tokens == NULL) {
        return 0;
    }
    do {
        i++;
        index = index->next;
    } while(index != tokens);
    
    return i;
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
   Token *current = token;

   do {
       Token *next = next_shape(current);

        current->next_shape = next;
        next->previous_shape = current;

        current = next;
   } while (current != token);
}

void update_color_links(Token *token) {
    Token *current = token;

    do {
       Token *next = next_color(current);

        current->next_color = next;
        next->previous_color = current;

        current = next;
   } while (current != token);
}

void attach_to_head(Liste *liste, Token *newtok) {
    if (*liste == NULL) {
        /* Initialisation de la liste */
        *liste = newtok;
    }
    else {
        /* Chainage de source au premier token de la liste */
        newtok->next = (*liste)->next;

        /* Chainage du dernier token à source */
        (*liste)->next = newtok;

        /* MaJ du chainage couleur/forme */
        update_shape_links(newtok);
        update_color_links(newtok);

    } 
}

void attach_to_tail(Liste *liste, Token *newtok) {
    if (*liste == NULL) {
        *liste = newtok;
    }
    else {
        /* Chainage de source au premier token de la liste */
        newtok->next = (*liste)->next;

        /* Chainage du dernier token à source */
        (*liste)->next = newtok;

        /* Source devient le nouveau dernier token de la liste */
        *liste = newtok;

        /* MaJ du chainage couleur/forme */
        update_shape_links(newtok);
        update_color_links(newtok);
    }
}

Token *detach_token(Liste *liste, Token *tok) {
    /* Liste vide ou aucun token entré */
    if (*liste == NULL || tok == NULL) {
        return NULL;
    }

    /* Liste a un élément */
    if (tok->next == tok) {
        if (tok == *liste) {
            *liste = NULL;
            return tok;
        }
        else {
            /* tok n'est pas dans la liste */
            return NULL;
        }
        
    }

    Token *tmp1_prev = *liste;
    /* On cherche le token avant tok */
    while (tmp1_prev->next != tok && tmp1_prev->next != *liste) {
        tmp1_prev = tmp1_prev->next;
    }
    if (tmp1_prev->next != tok) {
        /* tok n'est pas dans la liste */
        return NULL;
    }

    /* MaJ du dernier élément */
    if (tok == *liste) {
        *liste = tmp1_prev;
    }

    /* MaJ simple chainage */
    tmp1_prev->next = tok->next;
    tok->next = tok;

    /* MaJ double chainage couleur */
    tok->next_color->previous_color = tok->previous_color;
    tok->previous_color->next_color = tok->next_color;
    tok->next_color = tok;
    tok->previous_color = tok;

    /* MaJ double chainage forme */
    tok->next_shape->previous_shape = tok->previous_shape;
    tok->previous_shape->next_shape = tok->next_shape;
    tok->next_shape = tok;
    tok->previous_shape = tok;

    return tok;
}

int swap(Liste *lst, Token *tok1, Token *tok2) {
    /* Un des éléments est vide */
    if (*lst == NULL || tok1 == NULL || tok2 == NULL) {
        return 0;
    }
    /* Les deux éléments sont le même */
    if (tok1 == tok2) {
        return 1;
    }

    Token *tmp1_prev = *lst, *tmp2_prev = *lst;

    /* On recherche le token avait tok1 */
    do {
        tmp1_prev = tmp1_prev->next;
    } while(tmp1_prev != *lst && tmp1_prev->next != tok1);

    /* tok1 non trouvé */
    if (tmp1_prev->next != tok1) {
        return 0;
    }

    /* On recherche le token avait tok2 */
    do {
        tmp2_prev = tmp2_prev->next;
    } while(tmp2_prev != *lst && tmp2_prev->next != tok2);

    /* tok1 non trouvé */
    if (tmp2_prev->next != tok2) {
        return 0;
    }

    /* L'échange proprement dit */
    tmp2_prev->next = tok1;
    tmp1_prev->next = tok2;

    Token *tmp = tok2->next;
    tok2->next = tok1->next;
    tok1->next = tmp;
    
    /* On met à jour la queue de la liste si nécessaire */
    if (*lst == tok1) {
        *lst = tok2;
    }
    else if (*lst == tok2) {
        *lst = tok1;
    }

    return 1;
}
