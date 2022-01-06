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
    int value;
    int stop;
} tdados;


void acorda(int s,siginfo_t *info,void *c){}

//objetivo é imprimir no ecrã 2x a funcção imprime

void *imprime(void *dados){
    tdados *pdados = (tdados *) dados;
    do{
        printf("\n ola isto e uma thread %d",pdados->value);
        sleep(2);
        fflush(stdout);
    }while(pdados->stop);
   
    pthread_exit(NULL);
}

void main(){

    pthread_t t; //a , b
    char buffer[10];
    tdados v;
    v.value = 12;
    v.stop = 1;

    struct sigaction sa;
    sa.sa_sigaction = acorda;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1,&sa,NULL);


    if(pthread_create(&t,NULL,&imprime,&v) != 0){
        printf("\nErro thread 0");
        exit(-1);
    }

   //  if(pthread_create(&t[1],NULL,&imprime,NULL) != 0){
   //     printf("\nErro thread 1");
   //     exit(-1);
  //  }


    printf("\nola do main");
    do{
        printf("\nQuando quiser terminar escreva sair");
        scanf("%s",buffer);
        if (strcmp(buffer,"sair")==0)
        {
           //sair
           //pthread_kill(t,SIGUSR1);
           v.stop = 0;

        }else
            printf("\nComando invalido");
        
    }while(strcmp(buffer,"sair")!=0);
    pthread_join(t,NULL);
   // pthread_join(t[1],NULL);
    printf("\nterminou");

}