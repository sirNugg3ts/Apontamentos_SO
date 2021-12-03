#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(){

    int fd_env[2],fd_rec[2];
    pipe(fd_env);pipe(fd_rec);

    switch (fork())
    {
    case -1://error
        fprintf(stderr,"Erro a dar fork");
        exit(1);
        break;
    case 0:{ // child

        // 0 -> read
        // 1 -> write

        
        close(STDIN_FILENO);
        dup(fd_env[0]);
        close(fd_env[1]); //nao vou escrever de pai -> child
        close(fd_env[0]); //fechar o duplicado

        
        close(STDOUT_FILENO);
        dup(fd_rec[1]);
        close(fd_rec[0]); //nao vou ler de child -> pai
        close(fd_rec[1]); //fechar o duplicado
        
        execl("rdfran","rdfran",NULL);
        break;
    }

    default:{

        char palavra[50];
        char resposta[50];

        close(fd_env[0]); // nao vou ler de pai -> child
        close(fd_rec[1]); // nao vou escrever no child -> pai

        printf("\nIndique a palavra: ");
        //scanf("%s",palavra);
        fgets(palavra,49,stdin);

        write(fd_env[1],palavra,strlen(palavra));
        read(fd_rec[0],resposta,49);
        printf("resposta: %s",resposta);
        break;

    }
    }


    return 0;
}