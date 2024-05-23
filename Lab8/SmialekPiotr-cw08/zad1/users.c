#define _XOPEN_SOURCE 700
#include "specs.h"
#include <time.h>


void generate_string(char buffer[], int string_size){
    for (int i = 0; i < string_size; i++)
    {
        int rand_num = rand() % (sizeof(CHAR_SET) - 1);
        buffer[i] = CHAR_SET[rand_num];
    }
    buffer[string_size] = '\0';
}




int main(int argc, char *argv[]){
    srand(time(NULL)); 

    if(argc < 2){
        perror("Specify user numbers! \n");
        return EXIT_FAILURE;
    }

    long user_number = strtol(argv[1], NULL, 10);

    // we dont use O_CREAT flag because we are creating it in printer.c
    int shared_memory_desciptor = shm_open(SHARED_MEMORY_NAME,  O_RDWR,  S_IRUSR | S_IWUSR);
    memory_map_t* memory_map = mmap(NULL, sizeof(memory_map_t), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_desciptor, 0);

    char buffer[STRING_LENGHT];

    for (int i = 0; i < user_number; i++)
    {
        pid_t pid = fork();

        if(pid == 0){
            generate_string(buffer, STRING_LENGHT);


            //finding free printer
            int free_printer_index = -1;
            for (int j = 0; j < memory_map->printers_number; j++)
            {
                int printer_value;
                sem_getvalue(&memory_map->printers[j].printer_semaphore, &printer_value);
                if(printer_value > 0){
                    free_printer_index = j;
                    break;
                }
            }

            if(free_printer_index == -1){
                perror("waiting for free printer!\n");
            }
            
            //decreasing printer semaphore value 
            sem_wait(&memory_map->printers[free_printer_index].printer_semaphore);

            memcpy(memory_map->printers[free_printer_index].buffer, buffer, STRING_LENGHT);
            memory_map->printers[free_printer_index].state = 1; //printer state 1 means that printer is busy
        
            printf("Writing to printer %d -> user %d\n", free_printer_index, i);
            
            sleep(rand() % 2);

        }
        exit(0);
    }
    
    while (wait(NULL) > 0);
    

    return 0;
}