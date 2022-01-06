#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>
#include <signal.h>

typedef struct{
    int numThread;
    pthread_mutex_t *m;
} tdados;




//objetivo é imprimir no ecrã 2x a funcção imprime

void *imprime(void *dados){
    tdados *pdados = (tdados *)dados;
    pthread_mutex_lock(pdados->m);
   for (int i = 0; i < 11; i++)
   {
       printf("\nThread %d -[%d]",pdados->numThread,i);
       fflush(stdout);
    
   }
   pthread_mutex_unlock(pdados->m);
   pthread_exit(NULL);
   
}

void main(){

    pthread_t t[2];
    tdados v[2];

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);

    
    v[0].m = &mutex;
    v[0].numThread = 1;
    v[1].m = &mutex;
    v[1].numThread = 2;


    if (pthread_create(&t[0],NULL,&imprime,&v[0]) !=0){
        printf("erro");
        exit(-1);
    }if (pthread_create(&t[0],NULL,&imprime,&v[1]) !=0)
    {
        printf("erro");
        exit(-1);
    }
    
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 11; i++)
    {
        printf("\nMAIN: [%d]",i);
        fflush(stdout);
    }
     pthread_mutex_unlock(&mutex);

     pthread_join(t[0],NULL);
     pthread_join(t[1],NULL);
     pthread_mutex_destroy(&mutex);
    

}