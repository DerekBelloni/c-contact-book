#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

#define MAX_FIELD_LENGTH 256
struct contact_t {
    char name[MAX_FIELD_LENGTH];
    char email[MAX_FIELD_LENGTH];
    char phoneNbr[MAX_FIELD_LENGTH];
};

int add_contact(struct contact_t *, char *addstring, char *filepath, FILE **fp);

#endif