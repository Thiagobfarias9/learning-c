#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // FAZER SEARCH COM TOLOWER()

typedef struct book{
    char *title;
    char *author;
    int year;
    struct book *next; 
}book;

book *insert_book(book *library);
void print_books(book *library);
void search_for_title(char *title, book *library);
void search_for_author(char *author, book *library);
book *remove_book(char *title, book *library);
void save_on_txt(char *file, book *library);
void exit_library(book *library);

int main(){    
    book *library = NULL;
    printf("Welcome to the library manager! What do you  wanna do?\n");

    start:
    unsigned int res = 0;
    printf("1. Insert book to library\n2. Show all the books\n3. Search for book by title\n4. Search for book by author\n5. Remove a book\n6. Save books on a txt\n7. Exit\n");
    scanf("%u", &res);
    
    if(res < 1 || res > 7){
        printf("Invalid number!\n");
        goto start;
    }

    system("clear"); 
    
    switch (res)
    {
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
            char *title = malloc(sizeof(char *));

            if(title == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }
            
            printf("What's the title you wanna search? ");
            scanf("%s", title);
            
            search_for_title(title,library);
            
            free(title);
            goto start;
        break;

        case 4:
            char *author = malloc(sizeof(char *));

            if(author == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }

            printf("What's the author you wanna search? ");
            scanf("%s", author);
            search_for_author(author, library);
            free(author);
            goto start;
        break;
        case 5:
            char *titleRemove = malloc(sizeof(char *));

            if(titleRemove == NULL){
                perror("Error trying to alloc memory");
                return 1;
            }


            printf("What's the title of the book that you wanna remove? ");
            scanf("%s", titleRemove);
            
            library = remove_book(titleRemove, library);
            free(titleRemove);
            goto start;
        break;
        case 6:
            char *file = malloc(sizeof(char *));
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

book *insert_book(book *library){
    book *book1 = malloc(sizeof(book));
    if(book1 == NULL){
        perror("Error trying to alloc memory\n");
    }

    book1->title = malloc(50 * sizeof(char));
    book1->author = malloc(50 * sizeof(char));

    printf("What's the title of the book? ");
    scanf("%49s", book1->title);

    printf("What's the name of the author? ");
    scanf("%49s", book1->author);
    
    printf("What's the release year of the book? ");
    scanf("%d", &(book1->year));

    book1->next = library;

    system("clear");
    return book1;
}

void print_books(book *library){
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
        if(strcmp(ptr->title, title) == 0){
            printf("{\n Title: %s\n Author: %s\n Year: %d\n}\n", ptr->title, ptr->author, ptr->year);
            break;
        }
        ptr = ptr->next;
    }
}

void search_for_author(char *author, book *library){
    book *ptr = library;

    while(ptr != NULL){
        if(strcmp(ptr->author, author) == 0){
            printf("{\n Title: %s\n Author: %s\n Year: %d\n}\n", ptr->title, ptr->author, ptr->year);
        }
        ptr = ptr->next;
    }
};

book *remove_book(char *title, book *library){ // REFAZER
    
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
    FILE *file = fopen(fileName,"w");

    book *ptr = library;

    while(ptr != NULL){
        fprintf(file, "{\n Title: %s\n Author: %s\n Year: %d\n}\n\n", ptr->title, ptr->author, ptr->year);
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