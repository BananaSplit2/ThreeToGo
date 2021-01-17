/**
 * @file
 * @brief Contient les fonctions de lecture et écriture de fichier
 */

#ifndef FILEIO_H
#define FILEIO_H

/**
 * Lis le fichier des highscores et charge son contenu dans le tableau des scores
 * Si le fichier n'existe pas, il est créé et initialisé avec des scores de 0
 * @param scores tableau d'entiers représentant les 5 meilleurs scores
 * @return 1 si tout s'est bien passé, 0 en cas d'erreur de lecture/écriture
 */
int read_high_scores(int scores[]);

/**
 * Ecris le tableau des scores dans le fichier des high scores.
 * @param scores tableau d'entiers représentant les 5 meilleurs scores
 * @return 1 si tout s'est bien passé, 0 en cas d'erreur d'écriture
 */
int write_high_scores(int scores[]);

#endif