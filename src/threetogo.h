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
 * 
 * Le type Liste représente le chainage simple circulaire.
 * Il pointe vers le dernier élément de la liste
 */
typedef struct token{
    int color;
    int shape;
    struct token* next;
    struct token* next_color;
    struct token* previous_color;
    struct token* next_shape;
    struct token* previous_shape;
}Token, *Liste;