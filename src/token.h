#ifndef TOKEN_H
#define TOKEN_H

#include "threetogo.h"

/** 
 * Effectue l'allocation mémoire d'un token et renvoie son adresse
 * @param color Couleur du token
 * @param shape Forme du token
 * @return adresse du token alloué, NULL si échec
 */
Token *alloc_token(int color, int shape);

/**
 * Renvoie le nombre de tokens dans la liste
 */
int length(Liste tokens);

/**
 * Renvoie le prochain token de la même forme dans la liste
 * @param token adresse du token dont on cherche le suivant de la même forme
 * @return adresse du token suivant de la même forme
 */
Token *next_shape(Token *token);

/**
 * Renvoie le prochain token de la même couleur dans la liste
 * @param token adresse du token dont on cherche le suivant de la même couleur
 * @return adresse du token suivant de la même couleur
 */
Token *next_color(Token *token);

/**
 * Met à jour le double chainage de la forme du token
 * @param token adresse du token rajouté
 */
void update_shape_links(Token *token);

/**
 * Met à jour le double chainage de la couleur du token
 * @param token adresse du token rajouté
 */
void update_color_links(Token *token);

/**
 * Attache un token en première position d'une liste
 * @param source adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_head(Liste *liste, Token *newtok);

/**
 * Attache un token en dernière position d'une liste
 * @param source adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_tail(Liste *liste, Token *newtok);

/**
 * Détache le token de la liste
 * @param liste addresse de la liste dans laquelle tok se trouve
 * @param tok adresse du token à détacher
 * @return NULL en cas d'erreur (le token n'est pas dans la liste, la liste est vide ou le token est vide)
 * sinon l'adresse du token retiré
 */
Token *detach_token(Liste *liste, Token *tok);

/**
 * Echange tok1 et tok2 dans la liste lst.
 * ATTENTION, NE CHANGE PAS LES DOUBLES CHAINAGES
 * @param lst
 * @param tok1
 * @param tok2
 * @return 0 en cas d'erreur (tokens pas dans la liste, liste vide, etc.), 1 en cas d'échange réussi
 */
int swap(Liste *lst, Token *tok1, Token *tok2);

#endif
