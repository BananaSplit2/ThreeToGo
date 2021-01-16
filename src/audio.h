/**
 * @file
 * @brief Contient les fonctions audio du jeu
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "MLV/MLV_audio.h"
#include "threetogo.h"

int sons_init(MLV_Sound *sons[]);

void sons_free(MLV_Sound *sons[], int taille);

void play_sound_after_move(Game *game, int point_gain, MLV_Sound *sounds[]);

#endif