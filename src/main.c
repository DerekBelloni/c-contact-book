#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "common.h"
#include "file.h"

int print_usage(char *argv[]) {
    printf("Usage: %s -p <filepath> -f <filename>\n", argv[0]);
    return 1;
}

int main(int argc, char *argv[]) {
    int c;
    FILE *fp;
    char *filepath = NULL;
    char *filename = NULL;
    char *updateString = NULL;
    char *addString = NULL;
    char *removeString = NULL;
    bool newFile = false;

    struct contact_t *contacts = NULL;

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
        print_usage(argv);
        return 0;
    }

    if (newFile) {
        fp = create_contact_file(filepath);
        if (fp == NULL) {
            printf("Unable to create new file.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    } else {
        fp = open_contact_file(filepath);
        if (fp == NULL) {
            printf("Unable to open file.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    }

    return 0;
}