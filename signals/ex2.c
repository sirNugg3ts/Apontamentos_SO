#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int n=20;
int pontuacao=0;
int perdeu=0;

void jogo(){
    alarm(n);
    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int soma = num1 + num2,somaUser;
    printf("Introduza o valor da conta: [%d] + [%d]\n",num1,num2);
    if (scanf("%d",&somaUser) != 1)
    {
        perror("Nao introduziu nada - Perdeu");
    }
    if (soma == somaUser)
    {
        pontuacao++;
        printf("Acertou, tem [%d] pontos\n",pontuacao);
        n--;
    }else{n--;
    printf("n00b\n");
    if (++perdeu=="")
    {
        exit(1);
    }else
        printf("Tenta outra vez\n");
    }
    
    
}


void temp(int s, siginfo_t *i, void *v){
    printf("Acabou o tempo - Perdeu\n");
    exit(1);
}

int main(){
    char nome[100];
    int i=0;
    struct sigaction sa;
    sa.sa_sigaction = temp;
    sa.sa_flags = SA_RESTART|SA_SIGINFO;
    sigaction(SIGALRM,&sa,NULL);

    while(1){
        if(i==5){
            exit(1);
        }
        else{
            jogo();
        }
        i++;
    }
   
}