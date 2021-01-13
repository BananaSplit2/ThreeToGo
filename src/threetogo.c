#include "threetogo.h"
#include "graphique.h"
#include "moteur.h"
#include "token.h"
#include <time.h>


int main(void) {
	
	int sizex = 1000, sizey = 500;
	Case origin = {2, 1}, caseg = {2, 3}, cased = {sizex/RESO - 5, 3};
	
	int nb_tokens = 0, score = 0, check = 0;
	char message_s[100] = "Score = ", message_t[20] = "Timer = ";
	
	int mousex, mousey;
	Case cible, ciblebis;
	
	Liste queue = NULL, lst_tokens = NULL;
	init_queue(&queue);
	
	window_open(sizex, sizey); printf("OK Start...\n");
	int debut = time(NULL);
	
	/* Boucle principale */
	do {
		MLV_draw_rectangle((origin.col+5)*RESO, origin.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
		token_draw_list(queue, 5, origin);
		
		button_add_draw(caseg, 'l');
		button_add_draw(cased, 'r');
		
		cible.lig = 5;
		cible.col = (sizex/2)/RESO - nb_tokens/2 -1;
		token_draw_list(lst_tokens, nb_tokens, cible);
		
		score_cat(message_s, score);
		MLV_draw_text(0, sizey - RESO, message_s, MLV_COLOR_CYAN);
		timer_cat(message_t, time(NULL) - debut);
		MLV_draw_text(0, sizey - RESO*2, message_t, MLV_COLOR_CYAN);
		MLV_actualise_window();
		
		/* On attend un clic */
		printf("temps = %ld\n", time(NULL) - debut);
		MLV_wait_mouse(&mousex, &mousey);
		cible = mouse_to_square(mousex, mousey);
		
		/* Si le clic est sur un bouton d'ajout */
		switch((check = button_add_check(sizex, sizey, cible))) {
			
			case 0 : break;
			case 1 : add_left(&queue, &lst_tokens); nb_tokens += 1; break;
			case 2 : add_right(&queue, &lst_tokens); nb_tokens += 1; break;
		}
		
		/* Si le clic est sur un jeton de la liste */
		if((check = token_select_check(sizex, sizey, nb_tokens, cible, lst_tokens))) {
			
			Liste tok = lst_tokens;
			if(check != nb_tokens) {
				int i;
				for(i=0; i<check; i++) {
					tok = tok->next;
				}
			}
			MLV_wait_mouse(&mousex, &mousey);
			ciblebis = mouse_to_square(mousex, mousey);
			
			if(ciblebis.col == cible.col) {
				
				/* Choix du haut : on décale les formes sur la gauche */
				if(ciblebis.lig == cible.lig -1) {
					shift_color_left(&lst_tokens, tok);
					printf("Shift Color ON\n");
				}
				/* Choix du bas : on décale les couleurs sur la gauche */
				else if(ciblebis.lig == cible.lig +1) {
					shift_shape_left(&lst_tokens, tok);
					printf("Shift Shape ON\n");
				}
			}
		}
		score += check_combinations(&lst_tokens);
		nb_tokens = length(lst_tokens);
		
		MLV_clear_window(MLV_COLOR_BLACK);
	}
	while(time(NULL) - debut < 120);
	
	MLV_wait_mouse(&mousex, &mousey);
	
	printf("\n--GAME OVER--\nScore final = %d\n\n", score);

    return 0;
}
