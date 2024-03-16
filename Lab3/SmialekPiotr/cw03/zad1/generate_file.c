#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h> 

char generate_random_char() {
    return 'A' + rand() % 26; // Generuje losowy znak z zakresu od 'A' do 'Z'
}

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Functions takes only one argument: <bytes> and it must be long > 0\n");
    }
    

    char *endptr; // NULL
    long number_of_bytes = strtol(argv[1], &endptr, 10);

    // Sprawdzenie błędów konwersji
    if (number_of_bytes == 0){
        printf("Invalid input: %s\n", argv[1]);
        return 1;
    }

    if (number_of_bytes <= 0) {
        printf("Number of bytes must be a positive long!\n");
        return 1;
    }

    FILE *input_file;
    input_file = fopen("input_file.txt","w");

    if(input_file == NULL){
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    
    for (long i = 0; i < number_of_bytes; i++) {
        char random_char = generate_random_char();
        fprintf(input_file, "%c", random_char);
    }

    FILE *stats_file; 
    stats_file = fopen("_zad1.txt","a+");
    fprintf(stats_file,"Zadanie 1 statystyki:\n");

    return 0;
}
