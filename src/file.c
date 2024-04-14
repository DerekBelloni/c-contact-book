#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parse.h"
#include "common.h"

#define MAX_LINE_LENGTH 771 

FILE* create_contact_file(char *filepath) {
    FILE *fp = NULL;
    fp = fopen(filepath, "r");

    if (fp != NULL) {
        printf("A file already exists at the given path.\n");
        fclose(fp);
        return NULL;
    }

    fp = fopen(filepath, "w");
    if (fp == NULL) {
        perror("open");
        fclose(fp);
        return NULL;
    }

    return fp;
}

FILE* open_contact_file(char *filepath, struct contact_t **contacts, FILE **fp) {
    char line[MAX_LINE_LENGTH];
    int count = 0;
    int i = 0;
    *fp = fopen(filepath, "r+");

    if (*fp == NULL) {
        perror("open");
        fclose(*fp);
        return NULL;
    }

    // iterate over the lines of the file to a count of the number of contacts
    while(fgets(line, sizeof(line), *fp) != NULL) {
        count++;
    }

    *contacts = malloc(count * sizeof(struct contact_t));
    if (*contacts == NULL) {
        perror("malloc");
        fclose(*fp);
    }

    // need to reset the file pointer to the beginning of the file
    rewind(*fp);

    //
    while((fgets(line, sizeof(line), *fp)) != NULL) {
        char *name, *email, *phoneNbr = NULL;
        char *token;
        char *line_copy = strdup(line);

        // replace trailing character from the new line if present with a null terminating character
        char *newline = strchr(line, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        token = strsep(&line_copy, ",");
        if (token != NULL && token[0] != '\0') {
            name = strdup(token);
        }

        token = strsep(&line_copy, ",");
        if (token != NULL && token[0] != '\0') {
            email = strdup(token);
        }

        token = strsep(&line_copy, ",");
        if (token != NULL && token[0] != '\0') {
            phoneNbr = strdup(token);
        }

        if (name != NULL) {
            strncpy(contacts[i]->name, name, MAX_FIELD_LENGTH);
            free(name);
        }

        if (email != NULL) {
            strncpy(contacts[i]->email, email, MAX_FIELD_LENGTH);
            free(email);
        }

        if (phoneNbr != NULL) {
            strncpy(contacts[i]->phoneNbr, phoneNbr, MAX_FIELD_LENGTH);
            free(phoneNbr);
        }

        i++;
    }


    printf("Contact name at index 0: %s\n", contacts[0]->name);
    return *fp;
}

