#ifndef PARSE_H
#define PARSE_H

struct contact_t {
    char name[256];
    char email[256];
    char phoneNbr[256];
};

int add_contact(struct contact_t *, char *addstring);

#endif