#define RESO 50
#define MAX_TOKENS 16

typedef struct {
    int col;
    int lig;
} Case;

/** Transforme le pixel d'un clic de souris en coordonnées de case */
Case mouse_to_square(int mousex, int mousey);

/** Ouvre une fenêtre vide à fond noir */
void window_open(int larg, int haut);

/** Dessine un token de forme et couleur donnés */
void token_draw(Token t, Case c);

/** Dessine une liste de tokens sur une ligne */
void token_draw_list(Token lst_tokens, int nb_tokens, Case cible);
