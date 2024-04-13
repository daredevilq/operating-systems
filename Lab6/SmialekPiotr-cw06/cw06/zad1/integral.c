#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846

const double START_INTERVAL = 0.0;
const double END_INTERVAL = 1.0;


double integral_func(double x){
    return (4/((x*x) +1));
}

double minimum(double x , double y){
    if (x <= y)
       return x;
    else
        return y;
    
    
}
double calculate_accuracy(double result){
    return fabs(result -PI);
}


int main(int argc, char** argv){
    if (argc != 3)
    {
        printf("Wrong parameters!\n");
        return EXIT_FAILURE;
    }
    
    
    double interval_width = strtod(argv[1], NULL);
    long no_processes = strtol(argv[2], NULL, 10);
    
    clock_t start, end;
    double cpu_time_used;

    if ((END_INTERVAL - START_INTERVAL)/interval_width < no_processes)
    {
        printf("You entered too many processes\n");
        return EXIT_FAILURE;
    }

    start = clock();
    int fd[no_processes][2];
    long intervals_total = ceil((END_INTERVAL - START_INTERVAL)/interval_width);
    long intervals_per_process = intervals_total/ no_processes;

    // printf("no_processes: %ld\n",no_processes);
    // printf("intervals_total: %ld\n", intervals_total);
    // printf("intervals_per_process: %ld\n", intervals_per_process);
    // printf("interval_width: %f \n", interval_width);


    for (long i = 0; i < no_processes; i++) {
        if (pipe(fd[i]) < 0) {
            printf("Failed to create pipe\n");
            return EXIT_FAILURE;
        }

        pid_t child_pid = fork();

        if (child_pid == 0) {
            close(fd[i][0]);
            double process_result = 0.0;
            double current_interval_start = START_INTERVAL + i*intervals_per_process * interval_width;
            //printf("------------\n");
            for (long j = 0; j < intervals_per_process; j++) {
                //printf("current_interval_start %f \n",current_interval_start);

                process_result += integral_func(current_interval_start + interval_width / 2) * interval_width;
                current_interval_start = minimum(current_interval_start + interval_width, END_INTERVAL);
            }
            
            //printf("process_result %f \n",process_result);
            if (write(fd[i][1], &process_result, sizeof(process_result)) < 0) {
                printf("Error during writing to pipe\n");
                return EXIT_FAILURE;
            }

            exit(0);
        }
    
    close(fd[i][1]);
    }
    
    double result = 0.0;

    for (long i = 0; i < no_processes; i++){
        double partial_result;

        if(read(fd[i][0], &partial_result, sizeof(partial_result))<0){
            //printf("Error during reading from pipe\n");                
            return EXIT_FAILURE;
        }
        
        result += partial_result;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    double accuracy = calculate_accuracy(result);
    printf("Result: %.16lf\n", result);
    printf("Accuracy: %.16lf\n", accuracy);
    printf("Time: %.6lf seconds\n", cpu_time_used);
}