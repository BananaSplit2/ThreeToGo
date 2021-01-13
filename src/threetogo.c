#include "threetogo.h"
#include "graphique.h"
#include "moteur.h"
#include "token.h"
#include <time.h>



int main(void) {
	
	int sizex = 1000, sizey = 500;
	
	int nb_tokens = 0, score = 0, check = 0;
	
	int mousex, mousey;
	Case cible, ciblebis;
	
	Liste queue = NULL, lst_tokens = NULL;
	init_queue(&queue);
	
	window_open(sizex, sizey); printf("OK Start...\n");
	int debut = time(NULL);
	MLV_Event event;
	
	/* Boucle principale */
	do {
		
		do {
			refresh_screen(sizex, sizey, queue, lst_tokens, nb_tokens, time(NULL)-debut, score);
			event = MLV_wait_mouse_or_seconds(&mousex, &mousey, 1);
		}
		while(event != 1 && time(NULL)-debut < 120);
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
			
			do {
				refresh_screen(sizex, sizey, queue, lst_tokens, nb_tokens, time(NULL)-debut, score);
				token_select_check(sizex, sizey, nb_tokens, cible, lst_tokens);
				event = MLV_wait_mouse_or_seconds(&mousex, &mousey, 1);
			}
			while(event != 1 && time(NULL)-debut < 120);
			ciblebis = mouse_to_square(mousex, mousey);
			
			if(ciblebis.col == cible.col) {
				
				/* Choix du haut : on décale les formes sur la gauche */
				if(ciblebis.lig == cible.lig - 1) {
					shift_commoncolor_left(&lst_tokens, tok);
				}
				/* Choix du bas : on décale les couleurs sur la gauche */
				else if(ciblebis.lig == cible.lig + 1) {
					shift_commonshape_left(&lst_tokens, tok);
				}
			}
		}
		score += check_combinations(&lst_tokens);
		nb_tokens = length(lst_tokens);
		
	}
	while(time(NULL) - debut < 120);
	
	printf("\n--GAME OVER--\nScore final = %d\n\n", score);

    return 0;
}
