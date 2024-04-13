#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

struct contact_t {
    char name[256];
    char email[256];
    char phoneNbr[20];
};

FILE* create_contact_file(char *filepath);
FILE* open_contact_file(char *filepath);

#endif