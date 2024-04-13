#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

int main(){
    double interval_start;
    double interval_end;
    double result;
    


    int input_pipe_start_fd = open("input_pipe_start.fifo", O_WRONLY);
    int input_pipe_end_fd = open("input_pipe_end.fifo", O_WRONLY);
    int output_pipe_fd = open("output_pipe.fifo", O_RDONLY);

    if(input_pipe_start_fd < 0){
        printf("Error opening input_pipe.fifo\n");
        return EXIT_FAILURE;
    }
    
    if(input_pipe_end_fd < 0){
        printf("Error opening input_pipe.fifo\n");
        return EXIT_FAILURE;
    }
    
    if(output_pipe_fd < 0){
        printf("Error opening output_pipe.fifo\n");
        return EXIT_FAILURE;
    }


    scanf("%lf", &interval_start);
    scanf("%lf", &interval_end);

    if(write(input_pipe_start_fd, &interval_start, sizeof(interval_start)) < 0) {
        printf("Failed to write to the pipe\n");
        return EXIT_FAILURE;
    }
    if(write(input_pipe_end_fd, &interval_end, sizeof(interval_start)) < 0) {
        printf("Failed to write to the pipe\n");
        return EXIT_FAILURE;
    }
        
    if(read(output_pipe_fd, &result, sizeof(result)) < 0) {
        printf("Failed to read from the pipe\n");
        return -1;
    }

    printf("Result %lf \n", result);

    close(input_pipe_start_fd);
    close(input_pipe_end_fd);
    close(output_pipe_fd);


    return 0;
}