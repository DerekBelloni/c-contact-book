#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE* create_contact_file(char *filepath) {
    FILE *fp = NULL;
    fp = fopen(filepath, "r");

    if (fp != NULL) {
        printf("A file already exists at the given path.\n");
        fclose(fp);
        return NULL;
    }

    fp = fopen(filepath, "a");
    if (fp == NULL) {
        perror("open");
        fclose(fp);
        return NULL;
    }

    return fp;
}

FILE* open_contact_file(char *filepath) {
    printf("file path in open contact file: %s\n", filepath);
}

