#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"

#define MAX_FIELD_LENGTH 256

int add_contact(struct contact_t **contacts, char *addstring, char *filepath, FILE **fp, int *count) {
    
    char *name, *email, *phoneNbr;
    char *input = strdup(addstring);
    char *token;

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        name = strdup(token);
    }

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        email = strdup(token);
    }

    token = strsep(&input, ",");
    if (token != NULL && token[0] != '\0') {
        phoneNbr = strdup(token);
    }

    (*count)++;
    struct contact_t *temp = realloc(*contacts, *count * sizeof(struct contact_t));
    if (temp == NULL) {
        perror("Memory reallocation failed");
        if (*contacts != NULL) {
            free(*contacts);
        }
        free(name);
        free(email);
        free(phoneNbr);
        free(input);
        return -1;
    }

    *contacts = temp;

    strncpy((*contacts)[*count -1].name, name, MAX_FIELD_LENGTH - 1);
    strncpy((*contacts)[*count -1].email, email, MAX_FIELD_LENGTH - 1);
    strncpy((*contacts)[*count -1].phoneNbr, phoneNbr, MAX_FIELD_LENGTH - 1);


    fprintf(*fp, "%s,%s,%s\n", (*contacts)[*count - 1].name, (*contacts)[*count - 1].email, (*contacts)[*count - 1].phoneNbr);

    free(input);
    return 1;
}