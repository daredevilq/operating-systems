#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#define PI 3.14159265358979323846

long INTERVALS = 1000;



double integral_func(double x){
    return (4/((x*x) +1));
}

double minimum(double x , double y){
    if (x <= y)
       return x;
    else
        return y;
    
    
}


int main(){
    double interval_start;
    double interval_end;


        
    if(mkfifo("input_pipe_start.fifo", S_IRWXU) != 0) {
        printf("Failed to create input pipe");
        return EXIT_FAILURE;
    }
    if(mkfifo("input_pipe_end.fifo", S_IRWXU) != 0) {
        printf("Failed to create input pipe");
        return EXIT_FAILURE;
    }
    if(mkfifo("output_pipe.fifo", S_IRWXU) != 0) {
        printf("Failed to create output pipe");
        return EXIT_FAILURE;
    }

    int input_pipe_start_fd = open("input_pipe_start.fifo", O_RDONLY);
    int input_pipe_end_fd = open("input_pipe_end.fifo", O_RDONLY);
    int output_pipe_fd = open("output_pipe.fifo", O_WRONLY);


    if(read(input_pipe_start_fd, &interval_start, sizeof(interval_start)) < 0) {
        printf("Failed to write to the pipe\n");
        return EXIT_FAILURE;
    }
    if(read(input_pipe_end_fd, &interval_end, sizeof(interval_start)) < 0) {
        printf("Failed to write to the pipe\n");
        return EXIT_FAILURE;
    }
    
    double result = 0.0;

    double intervals_width = (interval_end - interval_start) / INTERVALS;

    for (long i = 0; i < INTERVALS; i++)
    {
        result += integral_func(interval_start + i*intervals_width + intervals_width/2) * intervals_width;
    }

    if(write(output_pipe_fd, &result, sizeof(result)) < 0) {
        printf("Failed to write to the pipe\n");
        return EXIT_FAILURE;
    }

    

    return 0;
}