/** 
 * Effectue l'allocation mémoire d'un token et renvoie son adresse
 * @param couleur Couleur du token
 * @param forme Forme du token
 * @return adresse du token alloué, NULL si échec
 */
Token *alloc_token(int couleur, int forme);

/** 
 * Initialise une liste de tokens avec un token initial
 * @param single adresse du token qui initialisera la liste
 * @return liste initialisée
 */
Liste create_liste(Token *single);

/**
 * Renvoie l'adresse du dernier token de la liste
 * (avant d'avoir fait un tour complet de la liste)
 * @param liste liste dont il faut trouver le dernier token
 * @return adresse du dernier token de la liste
 */
Token *find_tail(Liste liste);

/**
 * Attache un token en première position d'une liste
 * @param single adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_head(Token *single, Liste *liste);

/**
 * Attache un token en dernière position d'une liste
 * @param single adresse du token à rajouter
 * @param liste adresse de la liste à laquelle rajouter le token
 */
void attach_to_tail(Token *single, Liste *liste);