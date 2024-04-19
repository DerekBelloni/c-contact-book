#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "common.h"
#include "file.h"
#include "parse.h"

int print_usage(char *argv[]) {
    printf("Usage: %s -p <filepath> -f <filename>\n", argv[0]);
    return 1;
}

int main(int argc, char *argv[]) {
    int c;
    int count = 0;
    FILE *fp;
    char *filepath = NULL;
    char *filename = NULL;
    char *updateString = NULL;
    char *addString = NULL;
    char *removeString = NULL;
    char *file_mode = NULL;
    bool listContacts = false;
    bool newFile = false;

    struct contact_t *contacts = NULL;

    while ((c = getopt(argc, argv, "nlf:a:u:r:")) != -1) {
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
                break;
            case 'l':
                listContacts = true;
                break; 
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
        create_contact_file(filepath, &fp);
        if (fp == NULL) {
            printf("Unable to create new file.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    } else {
        file_mode = strdup("r+");
        open_contact_file(filepath, &contacts, &fp, &count, file_mode);
        if (fp == NULL) {
            printf("Unable to open file.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    }

    if (addString) {
       if (add_contact(&contacts, addString, filepath, &fp, &count) != STATUS_SUCCESS) {
            printf("Error adding new contact.\n");
            fclose(fp);
            return STATUS_ERROR;
       }
    }

    if (removeString) {
        if (remove_contact(&contacts, removeString, filepath, &fp, &count) != STATUS_SUCCESS) {
            printf("Error removing contact.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    }

    if (listContacts) {
        if (list_contacts(&contacts, &fp, &count) != STATUS_SUCCESS) {
            printf("Error listing contacts.\n");
            fclose(fp);
            return STATUS_ERROR;
        }
    }
 
    return 0;
}