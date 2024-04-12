#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common.h"

int main(int argc, char *argv[]) {
    int c;
    char *filepath = NULL;
    char *updateString = NULL;
    char *addString = NULL;
    char *removeString = NULL;
    bool newFile = false;

    while ((c = getopt(argc, argv, "nf:a:u:r:")) != -1) {
        switch(c) {
            case 'n':
                newFile = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addString = optarg;
                break;
            case 'u':
                updateString = optarg;
                break;
            case 'r':
                removeString = optarg;
            case '?':
                printf("Uknown option -%c\n", c);
                break;
            default:
                return -1;
        }
    }

    if (filepath == NULL) {
        printf("Filepath is a required argument\n");
        // call print usage here
        return 0;
    }

    if (newFile) {
        // call function in file.c for creating a new file
    }

    return 0;
}