#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "threetogo.h"
#include "graphique.h"
#include <time.h>

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
	
	switch(t.shape) {
		/**cercle**/
		case 0 : MLV_draw_filled_circle((c.col+0.5)*RESO, (c.lig+0.5)*RESO, 
												RESO*0.4, couleurs[t.color]);
				 break;
		
		/**carré**/
		case 1 : MLV_draw_filled_rectangle((c.col+0.1)*RESO, (c.lig+0.1)*RESO, 
										RESO*0.8, RESO*0.8, couleurs[t.color]);
				 break;
		
		/**triangle**/
		case 2 : {
				 const int list_x[3] = {(c.col+0.5)*RESO, (c.col+0.1)*RESO, (c.col+0.9)*RESO};
				 const int list_y[3] = {(c.lig+0.1)*RESO, (c.lig+0.9)*RESO, (c.lig+0.9)*RESO};
				 MLV_draw_filled_polygon(list_x, list_y, 3, couleurs[t.color]);
				 break;
		}
		
		/**diamant**/
		case 3 : {
				 const int list_x[4] = {(c.col+0.5)*RESO, (c.col+0.9)*RESO, (c.col+0.5)*RESO, (c.col+0.1)*RESO};
				 const int list_y[4] = {(c.lig+0.1)*RESO, (c.lig+0.5)*RESO, (c.lig+0.9)*RESO, (c.lig+0.5)*RESO};
				 MLV_draw_filled_polygon(list_x, list_y, 4, couleurs[t.color]);
				 break;
		}
	}
	
	MLV_actualise_window();
}


void token_draw_list(Liste lst_tokens, int nb_tokens, Case cible) {
	
	if(lst_tokens != NULL && nb_tokens != 0) {
		
		Liste tok = lst_tokens;
		
		int i;
		for(i=1; i < nb_tokens; i++) {
			tok = tok->next;
			cible.col += 1;
			token_draw(*tok, cible);
		}
		cible.col += 1;
		token_draw(*lst_tokens, cible);
	}
}


void button_add_draw(Case cible, char dir) {
	
	switch(dir) {
		case 'l' :
			MLV_draw_filled_rectangle(cible.col*RESO, cible.lig*RESO, RESO*3, RESO, MLV_COLOR_CYAN);
			MLV_draw_text((cible.col+1.2)*RESO, (cible.lig+0.3)*RESO, "<----", MLV_COLOR_BLACK);
			break;
		case 'r' :
			MLV_draw_filled_rectangle(cible.col*RESO, cible.lig*RESO, RESO*3, RESO, MLV_COLOR_CYAN);
			MLV_draw_text((cible.col+1.2)*RESO, (cible.lig+0.3)*RESO, "---->", MLV_COLOR_BLACK);
			break;
			
	}
	
	MLV_actualise_window();
}


int button_add_check(int sizex, int sizey, Case cible) {
	
	if(cible.lig == 3) {
		
		if(cible.col > 1 && cible.col < 5)
			return 1;
		
		if(cible.col > sizex/RESO - 6 && cible.col < sizex/RESO - 2)
			return 2;
	}
	
	return 0;
}


int token_select_check(int sizex, int sizey, int nb_tokens, Case cible, Liste lst_tokens) {
	
	int position;
	if(cible.lig == 5) {
		
		if(cible.col > (sizex/2)/RESO - nb_tokens/2 -1 && cible.col < (sizex/2)/RESO + nb_tokens/2 +nb_tokens%2) {
			MLV_draw_rectangle(cible.col*RESO, cible.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
			
			position = cible.col - (sizex/2)/RESO + nb_tokens/2 +1;
			
			Liste tok = lst_tokens;
			if(position != nb_tokens) {
				int i;
				for(i=0; i<position; i++) {
					tok = tok->next;
				}
			}
			
			Token tokup = {tok->color, (tok->shape+1)%4}, tokdo = {(tok->color+1)%4, tok->shape};
			cible.lig -= 1;
			token_draw(tokup, cible);
			cible.lig += 2;
			token_draw(tokdo, cible);
			
			MLV_actualise_window();
			return position;
		}
	}
	
	return 0;
}


void score_cat(char* message, int score) {
	
	char scoremess[100];
	sprintf(scoremess, "%d", score);
	
	int ind = 0;
	char letter = scoremess[ind];
	while(letter != '\0' && ind < 90) {
		message[ind+8] = letter;
		ind += 1;
		letter = scoremess[ind];
	}
	message[ind+8] = letter;
}


void timer_cat(char* message, int timer) {
	
	char timermess[100];
	sprintf(timermess, "%d", timer);
	
	int ind = 0;
	char letter = timermess[ind];
	while(letter != '\0' && ind < 90) {
		message[ind+8] = letter;
		ind += 1;
		letter = timermess[ind];
	}
	message[ind+8] = ' ';
	message[ind+9] = 's';
	message[ind+10] = letter;
}


void refresh_screen(int sizex, int sizey, Liste queue, Liste lst_tokens, int nb_tokens, int timer, int score) {
	
	MLV_clear_window(MLV_COLOR_BLACK);
	
	Case origin = {2, 1}, caseg = {2, 3}, cased = {sizex/RESO - 5, 3};
	char message_s[100] = "Score = ", message_t[20] = "Timer = ";
	
	MLV_draw_rectangle((origin.col+5)*RESO, origin.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
	token_draw_list(queue, 5, origin);
	
	button_add_draw(caseg, 'l');
	button_add_draw(cased, 'r');
	
	origin.lig = 5;
	origin.col = (sizex/2)/RESO - nb_tokens/2 -1;
	token_draw_list(lst_tokens, nb_tokens, origin);
	
	score_cat(message_s, score);
	MLV_draw_text(0, sizey - RESO, message_s, MLV_COLOR_CYAN);
	timer_cat(message_t, timer);
	MLV_draw_text(0, sizey - RESO*2, message_t, MLV_COLOR_CYAN);
	MLV_actualise_window();
}





