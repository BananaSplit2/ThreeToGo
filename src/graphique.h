#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

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
void token_draw_list(Liste lst_tokens, int nb_tokens, Case cible);

/** Dessine un bouton avec une flèche dans la direction voulue */
void button_add_draw(Case cible, char dir) ;

/** Vérifie si un des boutons d'ajout de jeton (gauche ou droit)
 * a été cliqué. 
 * Renvoie 0 si non, 1 si gauche, 2 si droit. */
int button_add_check(int sizex, int sizey, Case cible);

/** Vérifie si un token est cliqué */
int token_select_check(int sizex, int sizey, int nb_tokens, Case cible, Liste lst_tokens);

/** Concatène le score à la fin du message */
void score_cat(char* message, int score);

/** Concatène le timer à la fin du message */
void timer_cat(char* message, int timer);

#endif
