#include <stdlib.h>
#include "moteur.h"
#include "token.h"
#include <stdio.h>

int init_queue(Liste *queue) {
    int i;
    for (i = 0 ; i < 5 ; i++) {
        Token *tok = alloc_token(rand()%4, rand()%4);
        if (tok == NULL) {
            return 0;
        }
        attach_to_head(queue, tok);
    }
    return 1;
}

void free_liste(Liste *liste) {
    Token *tmp, *index = *liste;
    do {
        tmp = index->next;
        free(index);
        index = tmp;
    }while (index != *liste);
    *liste = NULL;
}

int add_left(Liste *queue, Liste *tokens) {
    /* On extrait le dernier élément de la queue */
    Token *tok = detach_token(queue, *queue);
    if (tok == NULL) {
        return 0;
    }

    /* On le rattache à la tête de la liste de tokens */
    attach_to_head(tokens, tok);

    /* On génère un nouveau token dans la queue */
    tok = alloc_token(rand()%4, rand()%4);
    if (tok == NULL) {
        return 0;
    }
    attach_to_head(queue, tok);

    return 1;
}

int add_right(Liste *queue, Liste *tokens) {
    /* On extrait le dernier élément de la queue */
    Token *tok = detach_token(queue, *queue);
    if (tok == NULL) {
        return 0;
    }

    /* On le rattache à la tête de la liste de tokens */
    attach_to_tail(tokens, tok);

    /* On génère un nouveau token dans la queue */
    tok = alloc_token(rand()%4, rand()%4);
    if (tok == NULL) {
        return 0;
    }
    attach_to_head(queue, tok);

    return 1;
}

static int already_in(Token *elem, Token *array[], int size) {
    int j;
    for (j = 0 ; j < size ; j++) {
        if (array[j] == elem) {
            return 1;
        }
    }
    return 0;
}

static void add_addresses(Token *start, int n, Token *array[], int *size) {
    int i;
    for (i = 0 ; i < n ; i++) {
        if (already_in(start, array, *size) == 0) {
            array[*size] = start;
            (*size)++;
        }
        start = start->next;
    }
}

int check_combinations(Liste *lst) {
    /* Liste vide */
    if (*lst == NULL) {
        return 0;
    }

    Token *index = (*lst)->next;
    int score = 0;

    /* Tableau statique qui contiendra la liste des adresses des tokens à retirer à la fin */
    Token* to_delete[length(*lst)];
    int size_array = 0;

    /* Contient les informations sur la séquence actuelle de tokens de la même forme/couleur */
    Sequence colors = {index, index->color, 1};
    Sequence shapes = {index, index->shape, 1};

    index = index->next;

    while (index != (*lst)->next) {
        /* Code pour les couleurs */
        if (index->color == colors.value) {
            (colors.size)++;
        }
        else {
            if (colors.size >= 3) {
                score += 100 * colors.size;
                /* Ajout des adresses au tableau */
                add_addresses(colors.start, colors.size, to_delete, &size_array);
            }
            colors.start = index;
            colors.size = 1;
            colors.value = index->color;
        }

        /* Code pour les formes */
        if (index->shape == shapes.value) {
            (shapes.size)++;
        }
        else {
            if (shapes.size >= 3) {
                score += 100 * shapes.size;
                /* Ajout des adresses au tableau */
                add_addresses(shapes.start, shapes.size, to_delete, &size_array);
            }
            shapes.start = index;
            shapes.size = 1;
            shapes.value = index->shape;
        }

        index = index->next;
    }

    /* Vérifications pour la dernière chaine */
    if (colors.size >= 3) {
        score += 100 * colors.size;
        /* Ajout des adresses au tableau */
        add_addresses(colors.start, colors.size, to_delete, &size_array);
    }
    if (shapes.size >= 3) {
        score += 100 * shapes.size;
        /* Ajout des adresses au tableau */
        add_addresses(shapes.start, shapes.size, to_delete, &size_array);
    }

    /* Suppression de tous les tokens marqués pour délétion */
    int i;
    for (i = 0 ; i < size_array ; i++) {
        detach_token(lst, to_delete[i]);
        free(to_delete[i]);
    }

    if (score > 0) {
        score += check_combinations(lst);
    }

    return score;
}

void shift_commonshape_left(Liste *lst, Token *tok) {
    /* Liste vide ou token vide */
    if (*lst == NULL || tok == NULL) {
        return;
    }

    /* Succession de permutations permettant de réaliser le décalage circulaire */
    Token *tok2 = tok->previous_shape;
    Token *tok1 = tok;
    while (tok2 != tok) {
        /* On doit MaJ le chainage couleur avec les déplacements (le chainage 
        des formes n'est pas changé par le déplacement circulaire) */
        swap(lst, tok1, tok2);
        update_color_links(tok1);
        update_color_links(tok2);
        tok1 = tok2;
        tok2 = tok2->previous_shape;
    }
}

void shift_commoncolor_left(Liste *lst, Token *tok) {
    /* Liste vide ou token vide */
    if (*lst == NULL || tok == NULL) {
        return;
    }

    /* Succession de permutations permettant de réaliser le décalage circulaire */
    Token *tok2 = tok->previous_color;
    Token *tok1 = tok;
    while (tok2 != tok) {
        /* On doit MaJ le chainage forme avec les déplacements (le chainage 
        des couleurs n'est pas changé par le déplacement circulaire) */
        swap(lst, tok1, tok2);
        update_shape_links(tok1);
        update_shape_links(tok2);
        
        tok1 = tok2;
        tok2 = tok2->previous_color;
    }
}