/**
 * @file
 * @brief Contient les fonctions permettant de faire tourner le jeu
 */

#ifndef THREETOGO_H
#define THREETOGO_H

#include "MLV/MLV_image.h"
#include "MLV/MLV_text.h"
#include "MLV/MLV_audio.h"

/** Entier correspondant à la couleur rouge */
#define RED 0
/** Entier correspondant à la couleur vert */
#define GREEN 1
/** Entier correspondant à la couleur bleu */
#define BLUE 2
/** Entier correspondant à la couleur jaune */
#define YELLOW 3

/** Entier correspondant à la forme cercle */
#define CIRCLE 0
/** Entier correspondant à la forme carré */
#define SQUARE 1
/** Entier correspondant à la forme triangle */
#define TRIANGLE 2
/** Entier correspondant à la forme diamant */
#define DIAMOND 3

/** Fréquence de rafraichissement du jeu par seconde */
#define FRAME_RATE 30
/** Longueur de la fenêtre */
#define SIZEX 1600
/** Largeur de la fenêtre */
#define SIZEY ((9*SIZEX)/16)
/** Nombre maximum de tokens dans la liste principale */
#define MAX_TOKENS 16
/** Durée d'une partie en secondes */
#define DUREE_MAX 120

/**
 * Représente une forme avec sa couleur et sa forme
 * Les formes peuvent être chainées entres elles
 * 
 * Le type Liste représente le chainage simple circulaire.
 * Il pointe vers le dernier élément de la liste
 */
typedef struct token{
    int color; /**< Couleur du token */
    int shape; /**< Forme du token */
    struct token* next; /**< Token suivant dans la liste */
    struct token* next_color; /**< Token suivant de la même couleur */
    struct token* previous_color; /**< Token précédent de la même couleur */
    struct token* next_shape; /**< Token suivant de la même forme */
    struct token* previous_shape; /**< Token précédent de la même forme */
}Token;

/**
 * Représente une liste de tokens
 */
typedef Token *Liste;

/**
 * Représente une partie avec son score et son timer
 * L'état de la partie est composée d'une queue et d'une liste
 * d'un certain nombre de tokens
 */
typedef struct game{
    int score; /**< Score de la partie */
    int combo; /**< Combo actuel */
    float timer; /**< Timer de la partie */
    int nb_tokens; /**< Nombre de tokens dans la liste principale */
    Liste* lst_tokens; /**< Liste principale de tokens */
    Liste* queue; /**< Queue contenant les prochains tokens à être ajoutés */
}Game;

int title_screen(MLV_Image *images[], MLV_Font *police);

int game_over(Game *game, MLV_Image *images[], MLV_Font *police);

/**
 * Initialise une partie
 * @param game adresse vers une partie
 * @return 0 si une erreur d'allocation a lieu, 1 sinon
 */
int game_init(Game *game);

/**
 * Libère tout l'espace mémoire utilisé par la partie
 * @param game adresse vers une partie
 */
void game_free(Game *game);

/**
 * Contient la boucle principale du jeu
 * @param game adresse vers une partie
 * @return 0 en cas d'erreur, 1 sinon
 */
int game_loop(Game *game, MLV_Image *images[], MLV_Font *police, MLV_Sound *sounds[]);


#endif
