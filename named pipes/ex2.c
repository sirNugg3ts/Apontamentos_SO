#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define SERVER_FIFO "aula"

void handler(int s, siginfo_t *i,void *v){
    unlink(SERVER_FIFO);
    printf("\ngoodbye");
    exit(1);
}

typedef struct {
    pid_t pid;
    char texto[100];
} dataMSG;

int main(){
    
    struct sigaction sa;
    sa.sa_sigaction = &handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT,&sa,NULL);

    int fd;
    dataMSG resposta;
    printf("\nAntes de criar o fifo");

     //criar fifo aula
    if (mkfifo(SERVER_FIFO,0666) == -1)
    {
        if (errno == EEXIST)
        {
            printf("\n FIFO ja existe");
        }
        printf("\nErro ao abrir FIFO");
        return 1;
    }
    

    printf("\nAntes de abrir o fifo");
    fd = open(SERVER_FIFO,O_RDONLY);
    if(fd == -1){
        printf("\nErro ao abrir FIFO");
    }
    printf("\nDepois de abrir o fifo");

    int size = read (fd,&resposta,sizeof(resposta));
    printf("\nResposta: %s \nPID: %s\nTamanho: %d\n",resposta.texto,resposta.pid,size);

    unlink(SERVER_FIFO);

}