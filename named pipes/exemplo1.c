#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define SERVER_FIFO "SERVIDOR"
#define another_fifo "SERVIDOR2"

int max(int a,int b){
    if (a>b)
    {
        return a;
    }
    else return b;
    
}

int main(){
    int nfd;
    fd_set read_fds;
    struct timeval tv;

    int fdRecebe = open(SERVER_FIFO,O_RDWR);
    int fdRecebe2 = open(another_fifo,O_RDWR);

    do{
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_ZERO(&read_fds);
        FD_SET(0,&read_fds);
        FD_SET(fdRecebe,&read_fds);

        nfd = select(max(fdRecebe,fdRecebe2)+1,&read_fds,NULL,NULL,&tv);
        if (FD_ISSET(0,&read_fds))
        {
            /*Do something*/
        }
         if (FD_ISSET(fdRecebe,&read_fds))
        {
            /*Do something*/
        }
         if (FD_ISSET(fdRecebe2,&read_fds))
        {
            /*Do something*/
        }
        
    }
}