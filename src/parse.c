#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"

#define MAX_FIELD_LENGTH 256

int add_contact(struct contact_t *contacts, char *addstring, char *filepath, FILE *fp) {
    char name[MAX_FIELD_LENGTH], email[MAX_FIELD_LENGTH], phoneNbr[MAX_FIELD_LENGTH];
    char *input = strdup(addstring);
    char *token;

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        strcpy(name, token);
    }

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        strcpy(email, token);
    }

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        strcpy(phoneNbr, token);
    }

    strncpy(contacts->name, name, sizeof(contacts->name));
    strncpy(contacts->email, email, sizeof(contacts->email));
    strncpy(contacts->phoneNbr, phoneNbr, sizeof(contacts->phoneNbr));

    if (fp == NULL) {
        perror("open");
        fclose(fp);
        return -1;
    }

    fprintf(fp, "%s,%s,%s\n", contacts->name, contacts->email, contacts->phoneNbr);

    fclose(fp);
    free(input);
    return 1;
}