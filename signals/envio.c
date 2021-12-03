#include <stdio.h>
#include <unistd.h>
#include <signal.h>



int main(){
    int pid;
    printf("\n qual o pid ");
    scanf("%d",&pid);
    union sigval val;
    val.sival_int = 123;
    sigqueue(pid,SIGUSR1,val);
}