#include <stdio.h>
#include "fileio.h"

int read_high_scores(int scores[]) {
    FILE *f = fopen("highscores", "r");
    int i;

    /* Si le fichier n'existe pas */
    if (f == NULL) {
        f = fopen("highscores", "w");
        if (f == NULL) {
            return 0;
        }
        fprintf(f, "0\n0\n0\n0\n0\n");
        fclose(f);

        for (i = 0 ; i < 5 ; i++) {
            scores[i] = 0;
        }
        return 1;
    }
    /* Si le fichier existe bien */
    else {
        for (i = 0 ; i < 5 ; i++) {
            if (fscanf(f, "%d", scores + i) != 1) {
                fclose(f);
                return 0;
            }
        }
        fclose(f);
        return 1;
    }
}

int write_high_scores(int scores[]) {
    FILE *f = fopen("highscores", "w");
    int i;

    if (f == NULL) {
        return 0;
    }

    for (i = 0 ; i < 5 ; i++) {
        fprintf(f, "%d\n", scores[i]);
    }
    
    fclose(f);
    return 1;
}