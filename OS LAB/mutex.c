#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>

#define f(n) for(int i=0;i<n;i++)

int value=0;
pthread_mutex_t mutex;
void *print(void *val) {
    int a  = *(int*)val;
    printf("%d ",a);
    free(val);
}



int main() {
    pthread_t p[20];
    for(int i=0;i<20;i++) {
        int *temp = malloc(4);
        *temp = i;
        if(pthread_create(&p[i],NULL,print,temp)!=0) {
            printf("Can't create thread\n");
        }
    }
    
    for(int i=0;i<2;i++) {
        if(pthread_join(p[i],NULL)!=0)  {
            printf("Can't join thread\n");
        }
    }
}