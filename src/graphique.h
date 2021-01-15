#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <sys/time.h>

#define RESO 50
#define MAX_TOKENS 16
#define DUREE_MAX 120
#define PI 3.14159265358979323846264338

typedef struct {
    int col;
    int lig;
} Case;


/** 
 * Transforme le pixel d'un clic de souris en coordonnées de case 
 * @param mousex entier abscisse du pixel
 * @param mousey entier ordonnée du pixel
 * @return structure Case avec coordonnées
 */
Case mouse_to_square(int mousex, int mousey);

/** 
 * Ouvre une fenêtre vide à fond noir 
 * @param larg entier nombre de pixels de largeur
 * @param haut entier nombre de pixels de hauteur
 */
void window_open(int larg, int haut);

/** 
 * Dessine un token de forme et couleur donnés 
 * @param t structure Token à dessiner
 * @param c structure Case où dessiner
 */
void token_draw(Token t, Case c);

/** 
 * Dessine une liste de tokens sur une ligne
 * @param lst_tokens structure Liste de tokens à dessiner
 * @param nb_tokens entier nombre à dessiner
 * @param cible structure Case où dessiner
 */
void token_draw_list(Liste lst_tokens, int nb_tokens, Case cible);

/** 
 * Dessine un bouton avec une flèche dans la direction voulue
 * @param cible structure Case où dessiner
 * @param dir caractère
 */
void button_add_draw(Case cible, char dir) ;

/** 
 * Vérifie si un bouton d'ajout de jeton (gauche ou droit) a été cliqué
 * @param sizex entier largeur de la fenêtre en pixel
 * @param sizey entier hauteur de la fenêtre en pixel
 * @return 0 si non, 1 si gauche, 2 si droit
 */
int button_add_check(int sizex, int sizey, Case cible);

/** 
 * Vérifie si un token est cliqué 
 * @param sizex entier largeur de la fenêtre en pixels
 * @param sizey entier hauteur de la fenêtre en pixels
 * @param nb_tokens entier du nombre de tokens alignés
 * @param cible structure Case où dessiner
 * @param lst_tokens structure Liste des tokens alignés
 * @return position entier du n-ième token sélectionné
 */
int token_select_check(int sizex, int sizey, int nb_tokens, Case cible, Liste lst_tokens);

/**
 * Si la position donnée est strictement positive, dessine la sélection
 * @param cible structure Case où dessiner
 * @param lst_tokens structure Liste des tokens alignés
 * @param nb_tokens entier du nombre de tokens alignés
 * @param position entier du n-ième token sélectionné
 */
void token_select_draw(Case cible, Liste lst_tokens, int nb_tokens, int position);

/** 
 * Concatène le score à la fin du message 
 * @param message chaîne de caractères
 * @param score entier valeur du score
 */
void score_cat(char* message, int score);

/** 
 * Concatène le timer à la fin du message 
 * @param message chaîne de caractères
 * @param timer entier valeur du timer
 */
void timer_cat(char* message, int timer);

/** 
 * Renvoie le float de l'interval écoulé entre debut et maintenant 
 * @param debut structure timeval
 * @return flottant interval (en secondes) entre debut et l'heure actuel
 */
float time_usec(struct timeval debut);

/** 
 * Rafraichit l'affichage de base du jeu 
 * @param sizex entier largeur de la fenêtre
 * @param sizey entier hauteur de la fenêtre
 * @param g structure Game des paramètres de la partie
 * @param cible structure Case de la case cliquée en dernier
 */
void refresh_screen(int sizex, int sizey, Game g, Case cible);

/** 
 * Dessine une horloge pour une certaine durée 
 * @param cible structure Case où dessiner
 * @param duree flottant représentant la durée écoulée (en secondes)
 */
void clock_draw(Case cible, float duree);

#endif
