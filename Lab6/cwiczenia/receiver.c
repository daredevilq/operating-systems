#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


int main() {
    // mkfifo("pipe_in.fifo", S_IRWXU);
    // mkfifo("pip_out.fifo", S_IRWXU);

    int pipe_in_desc = open("pipe_in.fifo", O_RDONLY);

    char message[100]; 

    ssize_t bytes_write = read(pipe_in_desc, message, strlen(message));
    close(pipe_in_desc);
    if (bytes_write == -1)
    {
        return EXIT_FAILURE;
    }
    
    printf("%s\n", message);


    return 0;
}