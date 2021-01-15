/**
 * @file
 * @brief Contient les fonctions du moteur du jeu
 */

#ifndef MOTEUR_H
#define MOTEUR_H

#include "threetogo.h"

/**
 * Structure utilisée pour caractériser des séquences de tokens consécutifs ayant
 * un caractère commun
 */
typedef struct sequence{
    Token *start; /**< Token au début de la séquence */
    int value; /**< Forme/couleur de la séquence */
    int size; /**< Taille de la séquence */
}Sequence;

/**
 * Initialise une queue de 5 tokens générés aléatoirement sous forme de liste chainée
 * @param queue adresse vers une liste de tokens
 * @return 0 en cas de problème d'allocation, 1 sinon
 */
int init_queue(Liste *queue);

/**
 * Libère toute la mémoire utilisée par la liste
 * @param liste à libérer
 */
void free_liste(Liste *liste);

/**
 * Déplace le prochain token dans la queue en tête de la liste de tokens
 * @param queue adresse vers la queue
 * @param tokens adresse vers la liste de tokens
 * @return 0 en cas de problème d'allocation ou d'extraction, 1 sinon
 */
int add_left(Liste *queue, Liste *tokens);

/**
 * Déplace le prochain token dans la queue en fin de la liste de tokens
 * @param queue adresse vers la queue
 * @param tokens adresse vers la liste de tokens
 * @return 0 en cas de problème d'allocation ou d'extraction, 1 sinon
 */
int add_right(Liste *queue, Liste *tokens);

/**
 * Cherche les chaines de plus de 3 tokens consécutifs d'une même couleur ou forme,
 * les retire et renvoie le score associé aux différentes chaines retirées
 * @param lst liste de tokens
 * @param mul multiplicateur du score renvoyé 
 */
int check_combinations(Liste *lst, int mul);

/**
 * Effectue un décalage circulaire vers la gauche des tokens de la même forme
 * @param lst adresse de la liste
 * @param tok adresse du token servant de base au décalage
 */
void shift_commonshape_left(Liste *lst, Token *tok);

/**
 * Effectue un décalage circulaire vers la gauche des tokens de la même couleur
 * @param lst adresse de la liste
 * @param tok adresse du token servant de base au décalage
 */
void shift_commoncolor_left(Liste *lst, Token *tok);

#endif
