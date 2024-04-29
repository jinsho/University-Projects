#include <errno.h>
#include <stdio.h>
#include <string.h>
main()
{
   int pid;

   if (( pid = fork()) < 0)
   {
     printf("erro no fork\n");
     exit(1);
   }
   if (pid == 0)
   {
     if (execl("prfilho1", "prfilho1", "parametro 1", "Parm 2", (char *) 0) < 0)
       printf("erro no execl = %d\n", errno);
   }
   else
     printf("sou o processo pai\n");
}
     
