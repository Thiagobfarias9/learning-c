#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc == 1){
        printf("The command write was not written correctly, type --help to show the correct way to use it\n");
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "--help") == 0){
        printf("Options: \n write <file> <text>: Write a text in a file\n write --help: Show all the options of write command\n");
        return 0;
    }
    if(argc > 3){
        printf("Invalid parameters. Type write --help");
        return 0;
    }

    FILE *ptr = fopen(argv[1],"a");

    if(ptr == NULL){
        printf("Error trying to open/create file\n");
        return 1;
    }


    size_t result = fwrite(argv[2], sizeof(char), strlen(argv[2]), ptr);
    size_t result2 = fwrite(" ", sizeof(char), sizeof(char),ptr);
    if(result > 0 && result2 > 0){
        printf("Text wrote in %s\n", argv[1]);
        return 0;
    }
    printf("Error trying to write in %s", argv[1]);
    return 1;
}