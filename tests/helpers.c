#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int txt_files_are_equal(char *path1, char *path2, int *line, int *col) {
    FILE *fp1;
    FILE *fp2;
    char ch1, ch2;

    fp1 = fopen(path1, "r");
    if (fp1 == NULL) {
        printf("\nUnable to open file %s.\n", path1);
        return 0;
    }

    fp2 = fopen(path2, "r");
    if (fp2 == NULL) {
        printf("\nUnable to open file %s.\n", path2);
        fclose(fp1);
        return 0;
    }

    // Initialize error position
    *line = 1;
    *col = 0;

    do {
        // Get one character from both files
        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);

        // Increment line
        if (ch1 == '\n') {
            *line += 1;
            *col = 0;
        }

        // If characters are not same then files are not equal
        if (ch1 != ch2) {
            fclose(fp1);
            fclose(fp2);
            return 0;
        }

        *col += 1;

    } while (ch1 != EOF && ch2 != EOF);

    // If both files have reached end
    if (ch1 == EOF && ch2 == EOF) {
        fclose(fp1);
        fclose(fp2);
        return 1;
    } else {
        fclose(fp1);
        fclose(fp2);
        return 0;
    }
}