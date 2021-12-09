#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define SERVER_FIFO "servidor"
#define CLIENT_FIFO "cliente_%d"
char CLIENT_FIFO_FINAL[100];

typedef struct {
    pid_t pid;
    int n1,n2;
    char operacao;

} calculoMSG;

typedef struct{
    float res;
} dataRPL;


int main(){
    int fd,fd_envio;
    calculoMSG pedido;
    dataRPL resposta;

    sprintf(CLIENT_FIFO_FINAL,CLIENT_FIFO,getpid());

       //criar fifo para obter resposta

    if (mkfifo(CLIENT_FIFO + getpid(),0666))
    {
        if (errno = EEXIST)
        {
            printf("\nFIFO já existe");
        }
        printf("\nErro ao criar FIFO");
        return 1;
        
    }

    do{
        fprintf(stdout,"Introduza o 1o numero: ");
        fscanf(stdin,"%d",&pedido.n1);

        fprintf(stdout,"Introduza o 2o numero: ");
        fscanf(stdin,"%d",&pedido.n2);

        fprintf(stdout,"Introduza a operacao: ");
        fscanf(stdin," %c",&pedido.operacao);

        if (pedido.operacao=='.')
        {
            fd_envio = open(SERVER_FIFO,O_WRONLY);
            int size = write(fd_envio,&pedido,sizeof(pedido));
            close(fd_envio);unlink(CLIENT_FIFO_FINAL);exit(1);
        }

        fd_envio = open(SERVER_FIFO,O_WRONLY);
            int size = write(fd_envio,&pedido,sizeof(pedido));
            close(fd_envio);
        int fd_resposta = open(CLIENT_FIFO_FINAL,O_RDONLY);
        int size2 = read(fd_resposta,&resposta,sizeof(resposta));
        close(fd_resposta);
        printf("\nResultado do calculo: %f",resposta.res);
        
            
    }while (1);
}