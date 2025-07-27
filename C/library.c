#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// AS FUNÇÕES QUE LEEM O ARQUIVO ESTÃO INSEGURAS AINDA
// ADICIONAR MÉTODOS DE PREVINIR SEGMENTATION FAULT

typedef struct book{
    char *title;
    char *author;
    int year;
    struct book *next; 
}book;


void clear_buffer();
void readString(char *string);
char *lowerString(char *string);
book *insert_book(book *library);
void print_books(book *library);
void search_for_title(char *title, book *library);
void search_for_author(char *author, book *library);
book *remove_book(char *title, book *library);
void save_on_txt(char *file, book *library);
void exit_library(book *library);
char *slinding_window(int start, int end, char *string);
void read_data(char *target, char *fileName, char **dest);
book *insert_data_file(book *library, char *filePath);

int main(){    
    book *library = NULL;
    printf("Welcome to the library manager! What do you  wanna do?\n");

    start:
    unsigned int res = 0;
    printf("0. Read data from a file\n1. Insert book to library\n2. Show all the books\n3. Search for book by title\n4. Search for book by author\n5. Remove a book\n6. Save books on a txt\n7. Exit\n");
    scanf("%u", &res);
    
    if(res < 0 || res > 7){
        printf("Invalid number!\n");
        goto start;
    }

    system("clear"); 
    
    switch (res)
    {
        case 0:
            char *filePath = malloc(51*sizeof(char));
            if(filePath == NULL){
                return 1;
            }
            printf("What's the path to the file that you want to read? ");
            scanf("%s", filePath);
            library = insert_data_file(library, filePath);
            printf("Success!\n");
            goto start;
        break;

        case 1:
            library = insert_book(library);
            printf("Book saved!\n");
            goto start;
        break;
    
        case 2:
            print_books(library);
            goto start;
        break;
        case 3:
            char *title = malloc(51*sizeof(char));

            if(title == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }
            
            printf("What's the title you wanna search? ");
            clear_buffer();
            readString(title);
            
            search_for_title(title,library);
            
            free(title);
            goto start;
        break;

        case 4:
            char *author = malloc(51*sizeof(char));

            if(author == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }

            printf("What's the author you wanna search? ");
            clear_buffer();
            readString(author);

            search_for_author(author, library);
            free(author);
            goto start;

        break;
        case 5:
            char *titleRemove = malloc(51*sizeof(char));

            if(titleRemove == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }


            printf("What's the title of the book that you wanna remove? ");
            clear_buffer();
            readString(titleRemove);
            
            library = remove_book(titleRemove, library);
            free(titleRemove);
            goto start;
        break;
        case 6:

            char *file = malloc(51*sizeof(char));
            printf("What's the name of the file that you wanna save the books? ");
            scanf("%s",file);
            save_on_txt(file, library);
            free(file);
            goto start;
        
        break;
        case 7:
            exit_library(library);
            return 0;
        break;
        default:
            printf("Número inválido\n");
            goto start;    
        break;
    }
}

void readString(char *string){
    int i = 0;
    int c;
    while((c = getchar()) != '\n' && i < 50){
        string[i] = c;
        i++;
    }
    string[i] = '\0';
}

char *lowerString(char *string){
    char *newString = malloc(strlen(string)+1);
    int i =0;
    while(string[i] != '\0'){
        newString[i] = tolower(string[i]);
        i++;
    }
    newString[i] = '\0';
    return newString;
}

void clear_buffer(){
    int c;
    while((c = getchar()) != '\n' && (c = getchar()) != EOF);
}

book *insert_book(book *library){
    book *book1 = malloc(sizeof(book));
    if(book1 == NULL){
        perror("Error trying to alloc memory\n");
    }

    book1->title = malloc(50 * sizeof(char));
    book1->author = malloc(50 * sizeof(char));

    printf("What's the title of the book? ");
    clear_buffer();
    readString(book1->title);

    printf("What's the name of the author? ");
    readString(book1->author);
    
    printf("What's the release year of the book? ");
    scanf("%d", &(book1->year));

    book1->next = library;

    system("clear");
    return book1;
}

void print_books(book *library){
    if(library == NULL){
        printf("Biblioteca Vazia\n");
        return;
    }
    book *pl = library;
    while(pl != NULL){
        printf("{\n Title: %s\n", pl->title);
        printf(" Author: %s\n", pl->author);
        printf(" Year:  %d\n}\n", pl->year);
        pl = pl->next;
    }
    printf("\n");
}

void search_for_title(char *title, book *library){
    book *ptr = library;
    while(ptr != NULL){
        char *lowerPtrTitle = lowerString(ptr->title);
        char *lowerTitle = lowerString(title);

        if(strcmp(lowerPtrTitle, lowerTitle) == 0){
            printf("{\n Title: %s\n Author: %s\n Year: %d\n}\n", ptr->title, ptr->author, ptr->year);
            free(lowerPtrTitle);
            free(lowerTitle);
            break;
        }

        free(lowerPtrTitle);
        free(lowerTitle);
        ptr = ptr->next;
    }

}

void search_for_author(char *author, book *library){
    book *ptr = library;

    while(ptr != NULL){
        char *lowerPtrAuthor = lowerString(ptr->author);
        char *lowerAuthor = lowerString(author);

        if(strcmp(lowerPtrAuthor, lowerAuthor) == 0){
            printf("{\n Title: %s\n Author: %s\n Year: %d\n}\n", ptr->title, ptr->author, ptr->year);
        }
        
        free(lowerPtrAuthor);
        free(lowerAuthor);
        ptr = ptr->next;
    }
};

book *remove_book(char *title, book *library){
    
    if(library == NULL){
        printf("Biblioteca Vazia\n");
        return 0;
    }
    
    book *root = library;
    book *ptr = library;

        if(strcmp(library->title, title) == 0){
            book *removeRoot = library;
            root = library->next;
            free(removeRoot);
            printf("Livro removido!\n");   
        }
        else{
            while(ptr->next != NULL){
                if(strcmp(ptr->next->title, title) == 0){
                    book *toRemove = ptr->next;
                    ptr->next = ptr->next->next; 
                    free(toRemove);
                    printf("Livro removido!\n");   
                    break;
                }
                ptr = ptr->next;
            }
        }
    return root;
}

void save_on_txt(char *fileName, book *library){
    if(library == NULL){
        printf("Biblioteca Vazia\n");
        return;
    }

    FILE *file = fopen(fileName,"w");

    book *ptr = library;

    while(ptr != NULL){
        fprintf(file, "{\n Title: %s;\n Author: %s;\n Year: %d;\n}\n", ptr->title, ptr->author, ptr->year);
        ptr = ptr->next;
    }

    fclose(file);
}

void exit_library(book *library){    
    while(library != NULL){
        book *next = library->next;
        free(library);
        library = next;
    }
    system("clear");
    printf("Goodbye :)\n");
}

char *slinding_window(int start, int end, char *string){
    
    char *newString = malloc((end-start+2) * sizeof(char));
    if(newString == NULL){
        printf("Error trying to alloc memory");
        return " ";
    }

    int i = 0;
    while(start <= end){
        newString[i] = string[start];
        i++;
        start++;
    }
    newString[i] = '\0';
    return newString;
}

void read_data(char *target, char *fileName, char **dest){
    
    char *string = malloc(1000*sizeof(char));
    if(string == NULL){
        printf("Error trying to alloc memory\n");
        return;
    }
    
    int c;
    
    int i = 0;

    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Error trying to open file\n");
        return;
    }
    
    while((c = getc(file)) != EOF){
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    int start = 0;
    int end = strlen(target)-1;
    int k = 0;
    int l = 0;
    
    
    while(end < strlen(string)){
        char *res = slinding_window(start, end, string);
        if(strcmp(res, target) == 0){
            for(int j = end + 1; string[j] != ';'; j++){
                dest[k][l] = string[j];
                l++;
            }
            k++;
            l = 0;
        }
        start++;
        end++;
    }
    
    fclose(file);
}

book *insert_data_file(book *library, char *filePath){
    char **authors = malloc(1000*sizeof(char *));
    char **titles = malloc(1000*sizeof(char *));

    if(authors == NULL || titles == NULL ){
        printf("Error trying to alloc memory");
        return NULL;
    }
    
    for(int i = 0; i < 1000; i++){
        authors[i] = malloc(51*sizeof(char)); 
        if(authors[i] == NULL){
            printf("Error trying to alloc memory");
            return NULL;
        }
    }

    for(int i = 0; i < 1000; i++){
        titles[i] = malloc(51*sizeof(char));
        if(authors[i] == NULL){
            printf("Error trying to alloc memory");
            return NULL;
        }
    }

   read_data("Author: ", filePath, authors);
   read_data("Title: ", filePath, titles);


   for(int m = 0; (strlen(authors[m]) > 0) || (strlen(titles[m]) > 0); m++){
        book *book1 = malloc(sizeof(book));
        if(book1 == NULL){
            perror("Error trying to alloc memory\n");
        }

        book1->title = titles[m];
        book1->author = authors[m];
        book1->year = 2000;

        book1->next = library;
        library = book1;
   }
   return library;
}