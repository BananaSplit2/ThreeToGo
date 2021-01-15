#include <MLV/MLV_all.h>
#include <time.h>
#include <sys/time.h>
#include "threetogo.h"
#include "graphique.h"
#include "moteur.h"
#include "token.h"

int game_init(Game *game) {
	/* Allocations des listes */
	game->queue = malloc(sizeof(Liste));
	if (game->queue == NULL)
		return 0;
	
	game->lst_tokens = malloc(sizeof(Liste));
	if (game->lst_tokens == NULL) {
		free(game->queue);
		return 0;
	}

	/* Initialisation du jeu */
	*(game->queue) = NULL;
	if (init_queue(game->queue) != 1) {
		return 0;
	}
	*(game->lst_tokens) = NULL;
	game->nb_tokens = 0;
	game->score = 0;
	game->timer = 0;

	return 1;
}

void game_free(Game *game) {
	free_liste(game->queue);
	free_liste(game->lst_tokens);
	free(game->queue);
	free(game->lst_tokens);
	game->queue = NULL;
	game->lst_tokens = NULL;
}

int game_loop(Game *game) {
	int check = 0;
	
	int mousex, mousey; /* Stocke des coordonnées de clic */
	Case cible = {0, 0}, ciblebis; /* Stocke des coordonées de case */

	Token *token_clique; /* Stocke l'adresse d'un token qui a été cliqué */
	int attend_clique = 0; /* Booléen indiquant un second clic est attendu après avoir cliqué sur un token */
	
	/* Stocke un temps de manière précise pour l'horloge et l'initialise */
	struct timeval debut;
	gettimeofday(&debut, NULL);

	MLV_Event event;
	MLV_Button_state button;

	/* Boucle principale */
	while (time_usec(debut) < DUREE_MAX) {

		/* Traitement de la file d'évènement */
		do {
			/* Récuparation du prochain évènement sur la liste */
			event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mousex, &mousey, NULL, &button);

			/* Clic de bouton */
			if (event == MLV_MOUSE_BUTTON && button == MLV_PRESSED) {
				if (attend_clique == 0) {
					cible = mouse_to_square(mousex, mousey);
			
					/* Si le clic est sur un bouton d'ajout et qu'il reste de la place */
					if(game->nb_tokens < MAX_TOKENS)
						switch(button_add_check(cible)) {
							case 1 : 
								add_left(game->queue, game->lst_tokens); 
								break;
							case 2 : 
								add_right(game->queue, game->lst_tokens); 
								break;
						}
					
					/* Si le clic est sur un jeton de la liste */
					if ((check = token_select_check(game->nb_tokens, cible, *(game->lst_tokens))) != 0) {
						/* On cherche et stocke l'adresse du token cliqué */
						token_clique = *(game->lst_tokens);
						if (check != game->nb_tokens) {
							int i;
							for(i = 0 ; i < check ; i++) {
								token_clique = token_clique->next;
							}
						}
						/* On attend un second clic */
						attend_clique = 1;
					}
				}
				else if (attend_clique == 1) {
					ciblebis = mouse_to_square(mousex, mousey);
					
					if (ciblebis.col == cible.col) {
						/* Choix du haut : on décale les formes sur la gauche */
						if (ciblebis.lig == cible.lig - 1) {
							shift_commoncolor_left(game->lst_tokens, token_clique);
						}
						/* Choix du bas : on décale les couleurs sur la gauche */
						else if (ciblebis.lig == cible.lig + 1) {
							shift_commonshape_left(game->lst_tokens, token_clique);
						}
					}
					cible = mouse_to_square(0, 0);
					attend_clique = 0;
				}

				/* Vérification des combinaisons */
				game->score += check_combinations(game->lst_tokens, 1);
				game->nb_tokens = length(*(game->lst_tokens));
			}
		} while (event != MLV_NONE);

		/* Rafraichissement de l'écran */
		refresh_screen(*game, cible); 
		MLV_actualise_window();
		MLV_delay_according_to_frame_rate();

		/* Met à jour le timer de la partie */
		game->timer = time_usec(debut); 
	}
	
	printf("\n--GAME OVER--\nScore final = %d\n\n", game->score);

    return 0;
}
