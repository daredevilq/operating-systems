#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <semaphore.h>


#define SHARED_MEMORY_NAME "shared_memory"
#define STRING_LENGHT 10
#define CHAR_SET "abcdefghijklmnopqrstuvwxyz"


typedef struct 
{
    char buffer[100];
    sem_t printer_semaphore;
    int state; // 0 means waiting ; 1 means writing
} printer_t;


typedef struct {
    printer_t printers[100];
    int printers_number;
} memory_map_t;






