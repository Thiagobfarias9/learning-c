#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}node;

void print_linked_list(node *list);

int main(){
    unsigned int qtNodes;
    printf("How many values do you want to allocate? ");
    scanf("%d", &qtNodes);

    node *list = NULL;

    for(int i = 0; i < qtNodes; i++){
        node *n = malloc(sizeof(node));
        if(n == NULL){
        return 1;
        }

        int number;
        printf("What is the number that you want to alocate? ");
        scanf("%d", &number);

        n->value = number;
        n->next == NULL;

        if(list == NULL){
            list = n;
        }
        else{
            for(node *ptr = list; ptr != NULL; ptr = ptr->next){
                if(ptr->next == NULL){
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    print_linked_list(list);
    node *ptr = list;
    while(ptr != NULL){
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0;
}

void print_linked_list(node *list){
    for(node *ptr = list; ptr != NULL; ptr = ptr->next){
        if(ptr->next != NULL)
        {
            printf(" ______________________\n/                      \\ \n|value: %d              |\n|adress: %p|\n|next: %p  |\n\\______________________/\n           |\n           |\n           |\n           v\n", ptr->value, &(ptr->value),&(ptr->next->value));
        }
        else{
            printf(" ______________________\n/                      \\ \n|value: %d              |\n|adress: %p|\n|next: NULL            |\n\\______________________/\n", ptr->value, &(ptr->value));
            break;
        }
        
    }
}