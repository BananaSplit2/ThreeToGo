#ifndef ASCII_H
#define ASCII_H

#include "threetogo.h"

/**
 * Renvoie le caractère correspondant à la couleur
 */
char repr_color(int color);

/**
 * Renvoie le caractère correspondant à la forme
 */
char repr_shape(int shape);

/**
 * Affiche le contenu d'une liste de tokens dans le terminal
 * @param tokens Liste de tokens
 */
void print_tokens(Liste tokens);

/**
 * Affiche le double chainage de la couleur indiquée dans la liste tokens
 * @param tokens Liste
 * @param color Couleur du double chainage à afficher
 */
void print_colorlinks(Liste tokens, int color);

#endif