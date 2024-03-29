#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>

// int main() {
//    printf("This is main process: %d\n", getpid());
//    for (int i = 0; i < 5; i++){
//       pid_t child_process = fork();
//       if (child_process == 0){
//          printf("%d %d %d\n",i, getpid(),getppid());
//          exit(0);
//          sleep(1);
//       }
//    }
   
//       return 0;
// }


int main(){

   printf("This is main process %d\n", getpid());


   pid_t child_pid;
   child_pid = fork();
   if(child_pid!=0) {
      printf("Ten napis zostal wyswietlony w programie 'main'!\n");
   } else {
      //execvp("./hello_world", NULL);
      execl("./hello_world","tenargumentjestniepotrzebny",NULL);
   }

      return 0;




   return 0;
}