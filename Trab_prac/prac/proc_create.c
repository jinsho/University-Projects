#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid;
    if((pid = fork()) < 0){
        printf("Erro no fork\n");
        exit(1);
    }
    if(pid == 0)
        printf("Nasci!\n");
    else{
        printf("Sou pai!\n");
        sleep(20);
    }
    return 0;
}
