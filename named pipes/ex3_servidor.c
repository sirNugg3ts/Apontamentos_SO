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




void sigint_handler(int s, siginfo_t *i, void *v){
    unlink(SERVER_FIFO);
    printf("\nA terminar servidor...");
    exit(1);
}

int main(int argc, char **argv){

    calculoMSG pedidoCliente;
    dataRPL resposta;

    struct sigaction sa;
        sa.sa_sigaction = &sigint_handler;
        sa.sa_flags = SA_RESTART|SA_SIGINFO;
    sigaction(SIGINT,&sa,NULL);

    int fdRecebe,fdResultado;
    float resultado;


//criar fifo
    if(mkfifo(SERVER_FIFO,0666) == -1){
        if (errno == EEXIST)
            printf("\nFIFO ja existe");
        printf("\nErro ao abrir FIFO");
        exit(1);
    }

    fdRecebe = open(SERVER_FIFO,O_RDONLY);

    if (fdRecebe == -1)
       printf("\nErro ao abrir FIFO");
    

    do{
          int size = read(fdRecebe,&pedidoCliente,sizeof(pedidoCliente));
          if (size>0)
          {
              switch (pedidoCliente.operacao)
                {
                case '+':
                resposta.res = pedidoCliente.n1 + pedidoCliente.n2;
                    break;
                case '-':
                resposta.res = pedidoCliente.n1 - pedidoCliente.n2;

                    break;
                case '*':
                resposta.res = pedidoCliente.n1 * pedidoCliente.n2;
                    break;
                case '/':
                resposta.res = pedidoCliente.n1 / pedidoCliente.n2;
                    break;

                case '.':
                    kill(getpid(),SIGINT);
                    break;
                

                default:
                    printf("\nPedido Invalido");
                    break;
                }
          }
        sprintf(CLIENT_FIFO_FINAL,CLIENT_FIFO,pedidoCliente.pid);

        int fdEnvio = open(CLIENT_FIFO_FINAL,O_WRONLY);
        int size2 = write(fdEnvio,&resposta,sizeof(resposta));
        close(fdEnvio);
          
        
    }while(1);
    unlink(SERVER_FIFO);
}