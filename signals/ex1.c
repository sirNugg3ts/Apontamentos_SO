#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int contador = 0;

void handler_funcSinal(int signum, siginfo_t *info,void *secret){
    printf("\n ai");
    contador++;
    if (contador == 5)
    {
        printf("\n ok pronto");
        exit(1);
    }
    
}

int main(){
    char nome[50];
    struct sigaction sa;
    sa.sa_sigaction = handler_funcSinal;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT,&sa,NULL);

    while(1){
        printf("\nWhats your name: ");
        scanf("%s",&nome);
        if (strcmp("sair",nome)==0)
        {
            break;
        }
        
        printf("\nHello %s",nome);
    }
}