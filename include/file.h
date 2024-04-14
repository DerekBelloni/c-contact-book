#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "parse.h"

FILE* create_contact_file(char *filepath);
FILE* open_contact_file(char *filepath, struct contact_t **, FILE **fp);

#endif