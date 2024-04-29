#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int pid, idqueue, fd[2], state;
    struct msg{
        long pid;
        char msg[30];
    };
    struct msg msg_sent, msg_received;

    if ((idqueue = msgget(0x1223, IPC_CREAT | 0777)) < 0){
        printf("Queue não criada! Erro!\n");
        exit(1);
    }

    pid = fork();

    if (pid == 0){
        msg_sent.pid = getpid();
        strcpy(msg_sent.msg, "This is a message test\n");
        msgsnd(idqueue, &msg_sent, sizeof(msg_sent)-sizeof(long), 0);
        exit(0);
    }

    msgrcv(idqueue, &msg_received, sizeof(msg_received)-sizeof(long), 0, 0);
    printf("This is what I\'ve received:\nPID: %ld\nMSG: %s", msg_received.pid, msg_received.msg);
    wait(&state);
    if ((msgctl(idqueue, IPC_RMID, NULL) < 0)){
        printf("Error removing queue.");
    }else{
        printf("Queue successfully removed.\n");
    }
    exit(0);
}   
