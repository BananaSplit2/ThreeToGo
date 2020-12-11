/** 
 * Effectue l'allocation mémoire d'un token et renvoie son adresse
 * @param color Couleur du token
 * @param shape Forme du token
 * @return adresse du token alloué, NULL si échec
 */
Token *alloc_token(int color, int shape);

/**
 * Affiche le contenu d'une liste de tokens dans le terminal
 * @param tokens Liste de tokens
 */
void print_tokens(Liste tokens);

/**
 * Renvoie le prochain token de la même forme dans la liste
 * @param token
 * @return adresse du token suivant de la même forme
 */
Token *next_shape(Token *token);

/**
 * Renvoie le prochain token de la même couleur dans la liste
 * @param token
 * @return adresse du token suivant de la même couleur
 */
Token *next_color(Token *token);

/**
 * Met à jour le double chainage des formes au niveau du token
 * @param token
 */
void update_shape_links(Token *token);

/**
 * Met à jour le double chainage des couleurs au niveau du token
 * @param token
 */
void update_color_links(Token *token);

/**
 * Attache un token en première position d'une liste
 * @param source adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_head(Liste *liste, Token *source);

/**
 * Attache un token en dernière position d'une liste
 * @param source adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_tail(Liste *liste, Token *source);