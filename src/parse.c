#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parse.h"

int add_contact(struct contact_t *contacts, char *addstring) {
    char *name, *email, *phoneNbr;
    char *input = strdup(addstring);
    char *token;
    printf("input copy: %s\n", input);

    token = strsep(&input, ",");
    printf("token: %s\n", token);

    free(input);
    return 1;
}