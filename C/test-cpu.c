#include <stdio.h>
#include <time.h>

int main(){
    long int limit = 1000000000;
    long int c = 0;
    clock_t start = clock();
    while(c <= limit){
        c++;
    }
    clock_t end = clock();

    printf("Execution time: %.5fs\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}