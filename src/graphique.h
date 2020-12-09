#define RESO 50

typedef struct token{
    int couleur;
    int forme;
    struct token* suivant;
    struct token* suivant_couleur;
    struct token* precedent_couleur;
    struct token* suivant_forme;
    struct token* precedent_forme;
}Tokens, *Liste;


typedef struct {
    int col;
    int lig;
} Case;









