/**
 * @file
 * @brief Contient les fonctions audio du jeu
 */

#ifndef AUDIO_H
#define AUDIO_H

#include "MLV/MLV_audio.h"
#include "threetogo.h"

/**
 * Initialise les sons nécessaires au fonctionnement du jeu
 * @param sons tableau de sons
 * @return 1 si tout s'est bien passé, 0 sinon
 */
int sons_init(MLV_Sound *sons[]);

/**
 * Libère l'espace utilisé par les sons chargés pour le jeu
 * @param sons tableau des sons
 * @param taille taille du tableau des sons
 */
void sons_free(MLV_Sound *sons[], int taille);

/**
 * Joue un son adapté au contexte après la réalisation d'un coup pendant la partie
 * @param game partie en cours
 * @param point_gain points gagnés par le coup
 * @param sounds tableau des sons
 */
void play_sound_after_move(Game *game, int point_gain, MLV_Sound *sounds[]);

#endif