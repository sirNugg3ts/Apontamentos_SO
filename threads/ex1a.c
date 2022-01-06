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
    char letra;
    int stop;
}TDADOS;

void imprime(char simb,int nVezes){
    for (int i = 0; i < nVezes; i++)
    {
        printf("[%c]",simb);
        fflush(stdout);
        sleep(1);
    }
    
}

void *tarefaA(void *dados){
    TDADOS *pdados = (TDADOS *) dados;

    //imprimir a letra
    do{
        srand(time(0));
        int t = rand() % (1-5);
        //imprimir os .
        imprime('.',t);
        
        //imprimir as letras
         imprime(pdados->letra,3);

    }while (pdados->stop);
 
    
   
    pthread_exit(NULL);
}

void main(){
    char buffer[10];
    pthread_t t[2]; //a posição 0 e b posição 1
    TDADOS dados[2];

    //dados thread A
    dados[0].letra = 'A';
    dados[0].stop = 1;

    //dados thread B
    dados[1].letra = 'B';
    dados[1].stop = 1;



    //criar thread para imprimir A

    if(pthread_create(&t[0],NULL,&tarefaA,&dados[0]) != 0){
            printf("\nErro ao criar thread A");
            exit(-1);
    }


    //criar thread para imprimir B

    if(pthread_create(&t[0],NULL,&tarefaA,&dados[1]) != 0){
            printf("\nErro ao criar thread B");
            exit(-1);
    }


   do{
        printf("\nEscreve sair para terminar");
        scanf("%s",buffer);

        if (strcmp(buffer,"sair")==0)
        {
            //terminar a thread A
            dados[0].stop = 0;

            //terminar thread B
            dados[1].stop = 0;
        }else
            printf("\nComando invalido");
       
       
   }while(strcmp(buffer,"sair"));

   pthread_join(t[0],NULL);
   pthread_join(t[1],NULL);

    printf("\nAdeus");
}