#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define f(n) for(int i=0;i<n;i++)

int value=0;

void* rollDice() {
    srand(getpid());
    int *result = malloc(4);
    int val = rand()%6+1;
    *result = val;
    return (void*)result; 
}

int main() {
    pthread_t p;
    pthread_create(&p,NULL,rollDice,NULL);
    int *result;
    pthread_join(p,(void**)&result);
    printf("Result: %d", *result);
}