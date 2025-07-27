#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1],"r");
    if(file == NULL){
        perror("Error trying to open the file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char string[length+1];

    char c;
    int i = 0;

    while((c = fgetc(file)) != EOF){
        string[i] = c;
        i++;
    }
    string[length+1] = '\0';
    int j = 0;
    while(j <= length){
        printf("%c", string[j]);
        j++;
    }
    printf("\n");
    return 0;
}