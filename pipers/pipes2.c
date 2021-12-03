#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//not complete

int main(){
    int fd_env[2];
    int fd_rec[2];
    pipe(fd_env);
    pipe(fd_rec);

    switch(fork()){
        case 0:{//child
            char resposta[100];
            close(fd_env[1]);
            close(fd_rec[0]);
            close(STDIN_FILENO);
            dup(fd_env[0]);
            read(fd_env[0],resposta,99);
            printf("\nchild recebeu -> %s",resposta);
            write(fd_rec[1],"hello from child",strlen("hello from child"));
            break;
        }
        case -1: //error
            fprintf(stderr,"Erro ao criar pipe \n");
            exit(EXIT_FAILURE);
            break;
        default:{//parent
            char resposta[100];
            close(fd_env[0]);
            close(fd_rec[1]);
            write(fd_env[1],"Ando constipado :)",strlen("Ando constipado :)"));
            read(fd_rec[0],resposta,99);
            printf("\n pai recebeu -> %s",resposta);
            break;
        } 
          
    }        

    return 0;
}