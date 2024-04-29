#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    int pid, status;
    int fd[2];
    char buf[30];

    if((pipe(fd)) < 0){
        printf("Erro ao criar um pipe.\n");
        exit(1);
    }

    if((pid = fork()) < 0){
        printf("Erro ao chamar fork.\n");
        exit(1);
    }

    if(pid == 0){
        strcpy(buf, "Eu sou filho.");
        write(fd[1], buf, sizeof(buf));
        exit(0);
    }
    read(fd[0], buf, sizeof(buf));
    printf("Sou pai. Recebi a mensagem: %s\n", buf);
    wait(&status);
    exit(0);
    return 0;
}   
