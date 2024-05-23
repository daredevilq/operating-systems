#define _XOPEN_SOURCE 700
#include "specs.h"



int main(int argc, char *argv[]){

    if(argc < 2){
        perror("Specify number of printers!\n");
        return EXIT_FAILURE;
    }

    
    long printer_number_arg = strtol(argv[1], NULL, 10);

    int shared_memory_desciptor = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR,  S_IRUSR | S_IWUSR);

    ftruncate(shared_memory_desciptor, sizeof(memory_map_t));

    // maping shared memory
    memory_map_t *map_memory = mmap(NULL, sizeof(sizeof(memory_map_t)), PROT_WRITE | PROT_READ, MAP_SHARED, shared_memory_desciptor, 0); 
    memset(map_memory, 0, sizeof(memory_map_t));

    map_memory->printers_number = printer_number_arg;

    for (int i = 0; i < printer_number_arg; i++)
    {
        sem_init(&map_memory->printers[i].printer_semaphore, 1 , 1);

        pid_t pid = fork();

        if (pid == 0)
        {
            while (true)
            {
                if (map_memory->printers[i].state == 1)
                {
                    for (int j = 0; i < STRING_LENGHT; j++)
                    {
                        printf("%c", map_memory->printers[i].buffer[j]);
                        sleep(1);
                    }
                    
                }
                
                printf("\n");

                
            }
            

        }
        

    }
    
    


    return 0;
}

