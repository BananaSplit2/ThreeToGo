#define RESO 50
#define MAX_TOKENS 16

typedef struct {
    int col;
    int lig;
} Case;

Case mouse_to_square(int mousex, int mousey);
/** Transforme le pixel d'un clic de souris en coordonnées de case **/

void window_open(int larg, int haut);
/** Ouvre une fenêtre vide à fond noir **/

void token_draw(struct token t, Case c);
/** Dessine un token de forme et couleur donnés **/

void token_draw_list(Tokens lst_tokens, int nb_tokens, Case cible);
/** Dessine une liste de tokens sur une ligne **/