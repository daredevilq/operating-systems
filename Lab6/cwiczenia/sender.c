#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//ps aux | wc -l popen i pclose

int main() {
    int flag = mkfifo("pipe_in.fifo", S_IRWXU);
    //mkfifo("pip_out.fifo", S_IRWXU);
    printf("tutaj\n");

    int pipe_in_desc = open("pipe_in.fifo", O_WRONLY);
    char message[] = "I am sending it to you!\0"; 
    ssize_t bytes_write = write(pipe_in_desc, message, strlen(message));
    close(pipe_in_desc);

    if (bytes_write == -1)
    {
        return EXIT_FAILURE;
    }
    
    return 0;
}