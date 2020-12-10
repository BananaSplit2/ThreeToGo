#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3

#define CIRCLE 0
#define SQUARE 1
#define TRIANGLE 2
#define DIAMOND 3

/**
 * Représente une forme avec sa couleur et sa forme
 * Les formes peuvent être chainées entres elles
 */
typedef struct token{
    int couleur;
    int forme;
    struct token* suivant;
    struct token* suivant_couleur;
    struct token* precedent_couleur;
    struct token* suivant_forme;
    struct token* precedent_forme;
}Token, *Liste;