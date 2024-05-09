#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]){
   pid_t p;
   switch (p=fork()) {
    case -1:{
      perror("fork");
      exit(1);}
    case 0:{  //proces potomny
      sleep(3);
      exit(3);}
    default: {  //proces macierzysty
      if  (argc>1) {
       if (atoi(argv[1])==2)
          // Wyślij do potomka sygnał SIGINT
          kill(p, SIGINT);
       else if (atoi(argv[1])==9)
          // Wyślij do potomka sygnał SIGKILL
          kill(p, SIGKILL);
       else 
          printf("Sygnał nieobsłużony\n");
      }
      else 
        printf("Zakończenie przez EXIT\n");
      
      int stat;
      wait(&stat);

      if (WIFEXITED(stat))
      {
        printf("Potomek o PID=%d zakończył się kodem %d\n", p, WEXITSTATUS(stat));
      }
      else if (WIFSIGNALED(stat))
      {
          printf("Potomek o PID=%d zakończył się sygnałem %d\n", p, WTERMSIG(stat));
      }
      
    }
   }
   return 0;
}
