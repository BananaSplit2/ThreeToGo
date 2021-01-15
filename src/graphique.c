#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "threetogo.h"
#include "graphique.h"
#include <math.h>

Case mouse_to_square(int mousex, int mousey) {
	
	Case cible = {mousex/RESO, mousey/RESO};
	
	return cible;
}

void window_open(int larg, int haut) {
	
	MLV_create_window("three-to-Go", "three-to-Go", larg, haut);
	MLV_clear_window(MLV_COLOR_BLACK);
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
}

void token_draw_list(Liste lst_tokens, int nb_tokens, Case cible) {
	
	/** vérification pour exclure les listes vides **/
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
		/**bouton ajout à gauche**/
		case 'l' :
			MLV_draw_filled_rectangle(cible.col*RESO, cible.lig*RESO, RESO*3, RESO, MLV_COLOR_CYAN);
			MLV_draw_text((cible.col+1.2)*RESO, (cible.lig+0.3)*RESO, "<----", MLV_COLOR_BLACK);
			break;
		/**bouton ajout à droite**/
		case 'r' :
			MLV_draw_filled_rectangle(cible.col*RESO, cible.lig*RESO, RESO*3, RESO, MLV_COLOR_CYAN);
			MLV_draw_text((cible.col+1.2)*RESO, (cible.lig+0.3)*RESO, "---->", MLV_COLOR_BLACK);
			break;
			
	}
}

int button_add_check(Case cible) {
	
	/**ligne des boutons d'ajout**/
	if(cible.lig == 3) {
		
		/**bouton ajout à gauche**/
		if(cible.col > 1 && cible.col < 5)
			return 1;
		
		/**bouton ajout à droite**/
		if(cible.col > MAX_TOKENS - 6 && cible.col < MAX_TOKENS - 2)
			return 2;
	}
	return 0;
}

int token_select_check(int nb_tokens, Case cible, Liste lst_tokens) {
	
	int position;
	if(cible.lig == 5) {
		
		/**calcule de la position du token sélectionné**/
		if(cible.col > MAX_TOKENS/2 - nb_tokens/2 -1 && cible.col < MAX_TOKENS/2 + nb_tokens/2 +nb_tokens%2) {
			
			position = cible.col - MAX_TOKENS/2 + nb_tokens/2 +1;
			
			return position;
		}
	}
	
	return 0;
}

void token_select_draw(Case cible, Liste lst_tokens, int nb_tokens, int position) {
	
	/**si la position est nulle, aucun token n'est choisi**/
	if(position > 0) {
	
		MLV_draw_rectangle(cible.col*RESO, cible.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
		
		Liste tok = lst_tokens;
		if(position != nb_tokens) {
			int i;
			for(i=0; i<position; i++) {
				tok = tok->next;
			}
		}
		
		Token tokup = {tok->color, (tok->shape+1)%4}, tokdo = {(tok->color+1)%4, tok->shape};
		
		/**jeton démo pour décalage des jetons de couleurs communes**/
		cible.lig -= 1;
		token_draw(tokup, cible);
		
		/**jeton démo pour décalage des jetons de formes communes**/
		cible.lig += 2;
		token_draw(tokdo, cible);
	}
}

void score_cat(char* message, int score) {
	
	char scoremess[100];
	/**transformer l'int en chaîne de caractères**/
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
	
	/**symbole de secondes**/
	message[ind+8] = ' ';
	message[ind+9] = 's';
	message[ind+10] = letter;
}

float time_usec(struct timeval debut) {
	
	struct timeval step;
	gettimeofday(&step, NULL);
	
	float usec = step.tv_sec - debut.tv_sec + (step.tv_usec - debut.tv_usec)/1000000.0;
	
	return usec;
}

void refresh_screen(Game g, Case cible) {
	
	MLV_clear_window(MLV_COLOR_BLACK);
	
	Case origin = {2, 1}, caseg = {2, 3}, cased = {SIZEX/RESO - 5, 3};
	char message_s[100] = "Score = ", message_t[20] = "Timer = ";
	int timer_int = g.timer;
	
	/**dessin de la queue et du cadre de sélection de l'élément en attente**/
	MLV_draw_rectangle((origin.col+5)*RESO, origin.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
	token_draw_list(*(g.queue), 5, origin);

	/**boutons d'ajout gauche/droite**/
	if(g.nb_tokens < MAX_TOKENS) {
		button_add_draw(caseg, 'l');
		button_add_draw(cased, 'r');
	}
	
	/**dessin centré de la liste des jetons**/
	origin.lig = 5;
	origin.col = (SIZEX/2)/RESO - g.nb_tokens/2 -1;
	token_draw_list(*g.lst_tokens, g.nb_tokens, origin);
	int position = token_select_check(g.nb_tokens, cible, *g.lst_tokens);
	token_select_draw(cible, *g.lst_tokens, g.nb_tokens, position);
	
	/**dessin des informations de l'interface**/
	score_cat(message_s, g.score);
	MLV_draw_text(0, SIZEY - RESO, message_s, MLV_COLOR_CYAN);
	timer_cat(message_t, timer_int);
	MLV_draw_text(0, SIZEY - RESO*2, message_t, MLV_COLOR_CYAN);
	
	/**dessin de l'horloge pour timer visuel**/
	origin.lig = 1;
	origin.col = SIZEX/RESO-2;
	clock_draw(origin, g.timer);
	
	MLV_actualise_window();
}

void clock_draw(Case cible, float duree) {
	
	MLV_draw_circle((cible.col+0.5)*RESO, (cible.lig+0.5)*RESO, RESO/1.5, MLV_COLOR_CYAN);
	
	int i;
	/**traits rémanents pour portion de disque**/
	for(i=0; i<duree; i++) {
		MLV_draw_line((cible.col+0.5)*RESO, (cible.lig+0.5)*RESO, 
					(cible.col+0.5)*RESO + (RESO/2.5)*sin(i/(DUREE_MAX*1.0) * 2*PI), 
					(cible.lig+0.5)*RESO - (RESO/2.5)*cos(i/(DUREE_MAX*1.0) * 2*PI), 
						MLV_COLOR_CYAN);
	}
	/**dessin de l'aiguille de l'horloge**/
	MLV_draw_line((cible.col+0.5)*RESO, (cible.lig+0.5)*RESO, 
					(cible.col+0.5)*RESO + (RESO/1.75)*sin(duree/(DUREE_MAX*1.0) * 2*PI), 
					(cible.lig+0.5)*RESO - (RESO/1.75)*cos(duree/(DUREE_MAX*1.0) * 2*PI), 
						MLV_COLOR_CYAN);
}


