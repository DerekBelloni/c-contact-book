#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "parse.h"
#include "common.h"

#define MAX_FIELD_LENGTH 256
#define MAX_LINE_LENGTH 771 

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
    fflush(*fp);
    free(input);
    return STATUS_SUCCESS;
}

int remove_contact(struct contact_t **contacts, char *removeString, char *filepath, FILE **fp, int *count) {
    int i, j, removed;

    for (i = 0; i < (*count); i++) {
        if (strcmp((*contacts)[i].name, removeString) == 0) {
            if ((*count) == 1) {
                (*count) = 0;
                free(*contacts);
                *contacts = NULL;
                removed = 1;
            } else {
                for (j = i; j < (*count) - 1; j++) {
                    (*contacts)[j] = (*contacts)[j + 1];
                    printf("Contacts at j after shift: %s,%s,%s\n", (*contacts)[j].name, (*contacts)[j].email, (*contacts)[j].phoneNbr);
                }
                (*count)--; 
                removed = 1;
                break;
            }
        }
    }

    if (removed) {
        *contacts = realloc(*contacts, (*count) * sizeof(struct contact_t));
        if (*contacts == NULL) {
            printf("Memory reallocation failed.\n");
            return STATUS_ERROR;
        }

        fclose(*fp);
        *fp = fopen(filepath, "w");
        if (*fp == NULL) {
            printf("Failed to open file for writing.\n");
            return STATUS_ERROR;
        }

        if ((*count) > 0) {
            for (i = 0; i < (*count); i++) {
                fprintf(*fp, "%s,%s,%s\n", (*contacts)[i].name, (*contacts)[i].email, (*contacts)[i].phoneNbr);
            }
        } 
        fflush(*fp);
        rewind(*fp);
        fclose(*fp);
        return STATUS_SUCCESS;
    }
    return STATUS_ERROR;
}

int list_contacts(struct contact_t **contacts, FILE **fp, int *count)
{
    int i = 0;
    printf("Here are your contacts: \n\n");
    for (i = 0; i < *count; i++) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", (*contacts)[i].name);
        printf("Email: %s\n", (*contacts)[i].email);
        printf("Phone Number: %s\n\n", (*contacts)[i].phoneNbr);
    }

    fclose(*fp);
    return STATUS_SUCCESS;
}