#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "threetogo.h"
#include "graphique.h"


Case mouse_to_square(int mousex, int mousey) {
	
	Case cible = {mousex/RESO, mousey/RESO};
	
	return cible;
}

void window_open(int larg, int haut) {
	
	MLV_create_window("three-to-Go", "three-to-Go", larg, haut);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
}

void token_draw(Token t, Case c) {
	
	MLV_Color couleurs[4] = { MLV_COLOR_RED, 
							MLV_COLOR_GREEN, 
							MLV_COLOR_BLUE, 
							MLV_COLOR_YELLOW };
	
	switch(t.forme) {
		/**cercle**/
		case 0 : MLV_draw_filled_circle((c.col+0.5)*RESO, (c.lig+0.5)*RESO, 
												RESO*0.4, couleurs[t.couleur]);
				 break;
		
		/**carré**/
		case 1 : MLV_draw_filled_rectangle((c.col+0.1)*RESO, (c.lig+0.1)*RESO, 
										RESO*0.8, RESO*0.8, couleurs[t.couleur]);
				 break;
		
		/**triangle**/
		case 2 : {
				 const int list_x[3] = {(c.col+0.5)*RESO, (c.col+0.1)*RESO, (c.col+0.9)*RESO};
				 const int list_y[3] = {(c.lig+0.1)*RESO, (c.lig+0.9)*RESO, (c.lig+0.9)*RESO};
				 MLV_draw_filled_polygon(list_x, list_y, 3, couleurs[t.couleur]);
				 break;
		}
		
		/**diamant**/
		case 3 : {
				 const int list_x[4] = {(c.col+0.5)*RESO, (c.col+0.9)*RESO, (c.col+0.5)*RESO, (c.col+0.1)*RESO};
				 const int list_y[4] = {(c.lig+0.1)*RESO, (c.lig+0.5)*RESO, (c.lig+0.9)*RESO, (c.lig+0.5)*RESO};
				 MLV_draw_filled_polygon(list_x, list_y, 4, couleurs[t.couleur]);
				 break;
		}
	}
	
	MLV_actualise_window();
}


void token_draw_list(Token lst_tokens, int nb_tokens, Case cible) {
	
	token_draw(lst_tokens, cible);
	
	int i;
	for(i=0; i < nb_tokens-1; i++) {
		cible.col += 1;
		token_draw(lst_tokens.suivant[i], cible);
	}
}
