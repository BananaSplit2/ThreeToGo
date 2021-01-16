#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "threetogo.h"
#include "graphique.h"


int images_init(MLV_Image *images[]) {
	images[0] = MLV_load_image("assets/button_left.png");
	images[1] = MLV_load_image("assets/button_right.png");
	images[2] = MLV_load_image("assets/bg.jpg");
	images[3] = MLV_load_image("assets/sq_re.png");
	images[4] = MLV_load_image("assets/sq_bl.png");
	images[5] = MLV_load_image("assets/sq_gr.png");
	images[6] = MLV_load_image("assets/sq_ye.png");
	images[7] = MLV_load_image("assets/ci_re.png");
	images[8] = MLV_load_image("assets/ci_bl.png");
	images[9] = MLV_load_image("assets/ci_gr.png");
	images[10] = MLV_load_image("assets/ci_ye.png");
	images[11] = MLV_load_image("assets/tr_re.png");
	images[12] = MLV_load_image("assets/tr_bl.png");
	images[13] = MLV_load_image("assets/tr_gr.png");
	images[14] = MLV_load_image("assets/tr_ye.png");
	images[15] = MLV_load_image("assets/di_re.png");
	images[16] = MLV_load_image("assets/di_bl.png");
	images[17] = MLV_load_image("assets/di_gr.png");
	images[18] = MLV_load_image("assets/di_ye.png");
	images[19] = MLV_load_image("assets/score.png");
	images[20] = MLV_load_image("assets/clock.png");
	images[21] = MLV_load_image("assets/combo.png");

	/* Vérification du chargement des images */
	int i;
	for (i = 0 ; i < 22 ; i++) {
		if (images[i] == NULL) {
			return 0;
		}
	}

	/* Redimensionnage des images */
	MLV_resize_image_with_proportions(images[0], RESO*3, RESO);
	MLV_resize_image_with_proportions(images[1], RESO*3, RESO);
	MLV_resize_image(images[2], SIZEX, SIZEY);
	MLV_resize_image_with_proportions(images[19], RESO*8, RESO);
	MLV_resize_image_with_proportions(images[20], RESO*2, RESO*3);
	MLV_resize_image_with_proportions(images[21], RESO*8, RESO);

	for (i = 3 ; i < 19 ; i++) {
		MLV_resize_image(images[i], RESO, RESO);
	}

	return 22;
}

void images_free(MLV_Image *images[], int taille) {
	int i;
	for (i = 0 ; i < taille ; i++) {
		MLV_free_image(images[i]);
	}
}

Case mouse_to_square(int mousex, int mousey) {
	
	Case cible = {mousex/RESO, mousey/RESO};
	
	return cible;
}

void window_open(int larg, int haut) {
	
	MLV_create_window("three-to-Go", "three-to-Go", larg, haut);
	MLV_clear_window(MLV_COLOR_BLACK);
}

void token_draw(Token t, Case c, MLV_Image *images[]) {
	switch (t.shape) {
		case SQUARE : 
			switch (t.color) {
				case RED:
					MLV_draw_image(images[3], c.col*RESO, c.lig*RESO);
					break;
				case BLUE:
					MLV_draw_image(images[4], c.col*RESO, c.lig*RESO);
					break;
				case GREEN:
					MLV_draw_image(images[5], c.col*RESO, c.lig*RESO);
					break;
				case YELLOW:
					MLV_draw_image(images[6], c.col*RESO, c.lig*RESO);
					break;
			}
			break;

		case CIRCLE :
			switch (t.color) {
				case RED:
					MLV_draw_image(images[7], c.col*RESO, c.lig*RESO);
					break;
				case BLUE:
					MLV_draw_image(images[8], c.col*RESO, c.lig*RESO);
					break;
				case GREEN:
					MLV_draw_image(images[9], c.col*RESO, c.lig*RESO);
					break;
				case YELLOW:
					MLV_draw_image(images[10], c.col*RESO, c.lig*RESO);
					break;
			}
			break;
		
		case TRIANGLE : {
			switch (t.color) {
				case RED:
					MLV_draw_image(images[11], c.col*RESO, c.lig*RESO);
					break;
				case BLUE:
					MLV_draw_image(images[12], c.col*RESO, c.lig*RESO);
					break;
				case GREEN:
					MLV_draw_image(images[13], c.col*RESO, c.lig*RESO);
					break;
				case YELLOW:
					MLV_draw_image(images[14], c.col*RESO, c.lig*RESO);
					break;
			}
			break;
		}
		
		case DIAMOND : {
			switch (t.color) {
				case RED:
					MLV_draw_image(images[15], c.col*RESO, c.lig*RESO);
					break;
				case BLUE:
					MLV_draw_image(images[16], c.col*RESO, c.lig*RESO);
					break;
				case GREEN:
					MLV_draw_image(images[17], c.col*RESO, c.lig*RESO);
					break;
				case YELLOW:
					MLV_draw_image(images[18], c.col*RESO, c.lig*RESO);
					break;
			}
			break;
		}
		
	}
}

void token_draw_list(Liste lst_tokens, int nb_tokens, Case cible, MLV_Image *images[]) {
	
	/** vérification pour exclure les listes vides **/
	if(lst_tokens != NULL && nb_tokens != 0) {
		
		Liste tok = lst_tokens;
		
		int i;
		for(i=1; i < nb_tokens; i++) {
			tok = tok->next;
			cible.col += 1;
			token_draw(*tok, cible, images);
		}
		cible.col += 1;
		token_draw(*lst_tokens, cible, images);
	}
}

void button_add_draw(Case cible, char dir, MLV_Image *images[]) {
	
	switch(dir) {
		/**bouton ajout à gauche**/
		case 'l' :
			MLV_draw_image(images[0], cible.col*RESO, cible.lig*RESO);
			break;
		/**bouton ajout à droite**/
		case 'r' :
			MLV_draw_image(images[1], cible.col*RESO, cible.lig*RESO);
			break;
			
	}
}

int button_add_check(Case cible) {
	
	/**ligne des boutons d'ajout**/
	if(cible.lig == 3) {
		
		/**bouton ajout à gauche**/
		if(cible.col > 2 && cible.col < 6)
			return 1;
		
		/**bouton ajout à droite**/
		if(cible.col > MAX_TOKENS - 7 && cible.col < MAX_TOKENS - 3)
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

void token_select_draw(Case cible, Liste lst_tokens, int nb_tokens, int position, MLV_Image *images[]) {
	
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
		token_draw(tokup, cible, images);
		
		/**jeton démo pour décalage des jetons de formes communes**/
		cible.lig += 2;
		token_draw(tokdo, cible, images);
	}
}

void score_to_str(char* message, int score) {
	sprintf(message, "%d", score);
}

void combo_to_str(char *dest, int combo) {
	sprintf(dest, "x%d", combo);
}

void timer_to_str(char* message, int timer) {
	/* Reinitialisation de message */
	message[0] = '\0';

	timer = DUREE_MAX - timer;

	char minutes[5];
	char secondes[5];

	if (timer / 60 < 10) {
		sprintf(minutes, "0%d", timer/60);
	}
	else {
		sprintf(minutes, "%d", timer/60);
	}
	
	if (timer % 60 < 10) {
		sprintf(secondes, "0%d", timer%60);
	}
	else {
		sprintf(secondes, "%d", timer%60);
	}
	

	strcat(message, minutes);
	strcat(message, ":");
	strcat(message, secondes);
}

float time_usec(struct timeval debut) {
	
	struct timeval step;
	gettimeofday(&step, NULL);
	
	float usec = step.tv_sec - debut.tv_sec + (step.tv_usec - debut.tv_usec)/1000000.0;
	
	return usec;
}

void refresh_screen(Game g, Case cible, MLV_Image *images[], MLV_Font *police) {
	
	/* Réinitialisation de l'écran */
	MLV_clear_window(MLV_COLOR_BLACK);

	/* Affichage du fond */
	MLV_draw_image(images[2], 0, 0);

	Case origin = {2, 1}, caseg = {3, 3}, cased = {10, 3};
	char message_s[100] = "", message_t[20] = "", message_c[20] = "";
	int timer_int = g.timer;
	
	/**dessin de la queue et du cadre de sélection de l'élément en attente**/
	MLV_draw_rectangle((origin.col+5)*RESO, origin.lig*RESO, RESO, RESO, MLV_COLOR_GRAY);
	token_draw_list(*(g.queue), 5, origin, images);

	/**boutons d'ajout gauche/droite**/
	if(g.nb_tokens < MAX_TOKENS) {
		button_add_draw(caseg, 'l', images);
		button_add_draw(cased, 'r', images);
	}
	
	/**dessin centré de la liste des jetons**/
	origin.lig = 5;
	origin.col = (SIZEX/2)/RESO - g.nb_tokens/2 -1;
	token_draw_list(*g.lst_tokens, g.nb_tokens, origin, images);
	int position = token_select_check(g.nb_tokens, cible, *g.lst_tokens);
	token_select_draw(cible, *g.lst_tokens, g.nb_tokens, position, images);
	
	/**dessin du score et du combo**/
	MLV_draw_image(images[19], RESO*4, RESO*7);
	score_to_str(message_s, g.score);
	MLV_draw_text_box_with_font(RESO*7, RESO*7, RESO*5, RESO, message_s, police, 1,
								MLV_COLOR_CLEAR, MLV_COLOR_WHITE, MLV_COLOR_CLEAR,
								MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	MLV_draw_image(images[21], RESO*4, RESO*8);
	combo_to_str(message_c, g.combo);
	MLV_draw_text_box_with_font(RESO*7, RESO*8, RESO*5, RESO, message_c, police, 1,
								MLV_COLOR_CLEAR, MLV_COLOR_WHITE, MLV_COLOR_CLEAR,
								MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	
	
	/**dessin de l'horloge pour timer visuel**/
	
	MLV_draw_image(images[20], RESO*14, 0);
	clock_draw(g.timer);
	timer_to_str(message_t, timer_int);
	MLV_draw_text_box_with_font(RESO*14, RESO*2, RESO*2, RESO, message_t, police, 1,
								MLV_COLOR_CLEAR, MLV_COLOR_WHITE, MLV_COLOR_CLEAR,
								MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void clock_draw(float duree) {
	
	/**traits rémanents pour portion de disque**/
	/*
	int i;
	for(i=0; i<duree; i++) {
		MLV_draw_line((cible.col+0.5)*RESO, (cible.lig+0.5)*RESO, 
					(cible.col+0.5)*RESO + (RESO/3)*sin(i/(DUREE_MAX*1.0) * 2*PI), 
					(cible.lig+0.5)*RESO - (RESO/3)*cos(i/(DUREE_MAX*1.0) * 2*PI), 
						MLV_COLOR_CYAN);
	}
	*/
	/**dessin de l'aiguille de l'horloge**/
	MLV_draw_line(15*RESO, RESO, 
					15*RESO + (RESO/2.0)*sin(duree/(DUREE_MAX*1.0) * 2*PI), 
					RESO - (RESO/2.0)*cos(duree/(DUREE_MAX*1.0) * 2*PI), 
						MLV_COLOR_RED);
}
