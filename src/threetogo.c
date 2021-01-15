#include "threetogo.h"
#include "graphique.h"
#include "moteur.h"
#include "token.h"
#include <time.h>
#include <MLV/MLV_all.h>
#include <sys/time.h>

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
	
	int mousex, mousey;
	Case cible = {0, 0}, ciblebis;

	Token *token_clique;
	int attend_clique = 0;
	
	struct timeval debut;
	gettimeofday(&debut, NULL);
	MLV_change_frame_rate(FRAME_RATE);
	MLV_Event event;
	MLV_Button_state button;
	/* Boucle principale */
	while (time_usec(debut) < DUREE_MAX) {
		
		game->timer = time_usec(debut);
		refresh_screen(SIZEX, SIZEY, *game, cible);

		/* Gestion de la file d'évènement */
		do {
			event = MLV_get_event(NULL, NULL, NULL, NULL, NULL, &mousex, &mousey, NULL, &button);

			/* Clic de bouton */
			if (event == MLV_MOUSE_BUTTON && button == MLV_PRESSED) {
				if (attend_clique == 0) {
					cible = mouse_to_square(mousex, mousey);
			
					/* Si le clic est sur un bouton d'ajout */
					switch((check = button_add_check(SIZEX, SIZEY, cible))) {
						
						case 0 : break;
						case 1 : add_left(game->queue, game->lst_tokens); game->nb_tokens += 1; break;
						case 2 : add_right(game->queue, game->lst_tokens); game->nb_tokens += 1; break;
					}
					
					/* Si le clic est sur un jeton de la liste */
					if((check = token_select_check(SIZEX, SIZEY, game->nb_tokens, cible, *(game->lst_tokens)))) {
						token_clique = *(game->lst_tokens);
						if(check != game->nb_tokens) {
							int i;
							for(i=0; i<check; i++) {
								token_clique = token_clique->next;
							}
						}
						attend_clique = 1;
					}
				}
				else if (attend_clique == 1) {
					ciblebis = mouse_to_square(mousex, mousey);
					
					if(ciblebis.col == cible.col) {
						
						/* Choix du haut : on décale les formes sur la gauche */
						if(ciblebis.lig == cible.lig - 1) {
							shift_commoncolor_left(game->lst_tokens, token_clique);
						}
						/* Choix du bas : on décale les couleurs sur la gauche */
						else if(ciblebis.lig == cible.lig + 1) {
							shift_commonshape_left(game->lst_tokens, token_clique);
						}
					}
					cible = mouse_to_square(0, 0);
					attend_clique = 0;
				}
				game->score += check_combinations(game->lst_tokens);
				game->nb_tokens = length(*(game->lst_tokens));
			}
		} while (event != MLV_NONE);

		MLV_actualise_window();
		MLV_delay_according_to_frame_rate();
	}
	
	printf("\n--GAME OVER--\nScore final = %d\n\n", game->score);

    return 0;
}
