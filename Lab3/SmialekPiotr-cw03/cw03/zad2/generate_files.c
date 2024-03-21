#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_WORDS 10
#define MAX_WORDS 10000

char generate_random_char() {
    return 'A' + rand() % 26; // Generuje losowy znak z zakresu od 'A' do 'Z'
}




int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Functions takes only one argument: <number of files to generate> and it must be int\n");
    }


    char *endptr; // wskaźnik do znaku końca
    long number_of_files = strtol(argv[1], &endptr, 10);

    // Sprawdzenie błędów konwersji
    if (*endptr != '\0') {
        printf("Invalid input: %s\n", argv[1]);
        return 1;
    }

    // Sprawdzenie, czy liczba plików jest większa niż zero
    if (number_of_files <= 0) {
        printf("Invalid input: %ld\n", number_of_files);
        return 1;
    }
    char folder_name[] = "test-directory";
    char file_name[50]; //buffer 
    int random_words_number;
    srand(time(NULL));
    for (int i = 0; i < number_of_files; i++){
        sprintf(file_name, "%s/file%d.txt",folder_name, i + 1); 
        FILE *gen_file = fopen(file_name, "w");

        if (gen_file == NULL){
            
            printf("Error opening file!");
            return 1;
        }
        random_words_number = rand() % (MAX_WORDS - MIN_WORDS) + MIN_WORDS;

        for (long i = 0; i < random_words_number; i++) {
            char random_char = generate_random_char();
            fprintf(gen_file, "%c", random_char);
        }
        
        fclose(gen_file);
    }
    


    return 0;
}