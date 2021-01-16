#include "audio.h"

int sons_init(MLV_Sound *sons[]) {
	sons[0] = MLV_load_sound("assets/doublekill.wav");
	sons[1] = MLV_load_sound("assets/triplekill.wav");
	sons[2] = MLV_load_sound("assets/multikill.wav");
	sons[3] = MLV_load_sound("assets/megakill.wav");
	sons[4] = MLV_load_sound("assets/ultrakill.wav");
	sons[5] = MLV_load_sound("assets/monsterkill.wav");
	sons[6] = MLV_load_sound("assets/firstblood.wav");
	sons[7] = MLV_load_sound("assets/godlike.wav");

	/* Vérification du chargement des images */
	int i;
	for (i = 0 ; i < 8 ; i++) {
		if (sons[i] == NULL) {
			return 0;
		}
	}

	return 8;
}

void sons_free(MLV_Sound *sons[], int taille) {
	int i;
	for (i = 0 ; i < taille ; i++) {
		MLV_free_sound(sons[i]);
	}
}

void play_sound_after_move(Game *game, int point_gain, MLV_Sound *sounds[]) {
    if (point_gain == 0) {
        game->combo = 0;
    }
    else {
        game->combo += 1;
        switch (game->combo) {
            case 2:
                MLV_play_sound(sounds[0], 1.0);
                break;
            case 3:
                MLV_play_sound(sounds[1], 1.0);
                break;
            case 4:
                MLV_play_sound(sounds[2], 1.0);
                break;
            case 5:
                MLV_play_sound(sounds[3], 1.0);
                break;
            case 6:
                MLV_play_sound(sounds[4], 1.0);
                break;
            case 7:
                MLV_play_sound(sounds[5], 1.0);
                break;
        }
    }

    if (game->score == 0 && point_gain > 0) {
        MLV_play_sound(sounds[6], 1.0);
    }
    else if (game->combo < 2 && point_gain >= 1000) {
        MLV_play_sound(sounds[7], 1.0);
    }
}
