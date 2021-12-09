#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define SERVER_FIFO "aula"

typedef struct {
    pid_t pid;
    char texto[100];
} dataMSG;

int main(){
    int fd;
    dataMSG resposta;
    resposta.pid = getpid();

    printf("\nAntes de abrir o fifo");
    fd = open(SERVER_FIFO,O_WRONLY);

    if(fd == -1){
        printf("\nErro ao abrir FIFO");
        return 1;
    }

    printf("\nintroduza os sintomas");

   fgets(resposta.texto,strlen(resposta.texto),stdin);

   int size = write(fd,&resposta,sizeof(resposta));
    printf("\nResposta: %s \nTamanho: %d\n",resposta,size);
}