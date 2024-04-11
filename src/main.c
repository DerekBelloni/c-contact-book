#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

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
                printf("Filepath: %s\n", filepath);
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

    return 0;
}