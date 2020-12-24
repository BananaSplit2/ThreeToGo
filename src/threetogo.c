#include "threetogo.h"
#include "graphique.h"

/*---------------------A METTRE DANS moteur.c !!!---------------------*/

#include <time.h>

int token_create_list(Token* lst_tokens, int nb_tokens) {
	
	srand(time(NULL));
	
	if(nb_tokens < 1)
		return 0;
	
	if(((*lst_tokens).suivant=(struct token *)malloc((nb_tokens-1)*sizeof(struct token)))==NULL) {
		printf("plus de place memoire\n");
		return 0;
	}
	
	(*lst_tokens).couleur = rand()%4;
	(*lst_tokens).forme = rand()%4;
	int i;
	for(i=0; i< nb_tokens-1; i++) {
		(*lst_tokens).suivant[i].couleur = rand()%4;
		(*lst_tokens).suivant[i].forme = rand()%4;
	}
	
	return 1;
}
/*--------------------------------------------------------------------*/

int main(void) {
	
	int nb_tokens = 5;
	int mousex, mousey;
	Case cible = {1, 1};
	
	Token lst_tokens;
	token_create_list(&lst_tokens, nb_tokens);
	
	nb_tokens = 0;
	window_open(1000, 500);
	token_draw_list(lst_tokens, 5, cible);
	do {
		
		MLV_wait_mouse(&mousex, &mousey);
		cible = mouse_to_square(mousex, mousey);
		token_create_list(&lst_tokens, 5);
		token_draw_list(lst_tokens, 5, cible);
		
		nb_tokens += 1;
	}
	while(nb_tokens < 16);
	
	MLV_wait_mouse(&mousex, &mousey);

    return 0;
}
