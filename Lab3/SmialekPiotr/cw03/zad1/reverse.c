#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#ifdef BLOCK
#define BLOCK_SIZE 1024

void reverse(FILE *input_file, FILE *output_file){
    
    fseek(input_file, 0, SEEK_END);

    long long bytes_left = ftell(input_file);
    long long bytes_to_read;
    char *buffer = malloc(BLOCK_SIZE * sizeof(char));
    char c;

    while(bytes_left > 0){
        
        if(bytes_left > BLOCK_SIZE){
            bytes_to_read = BLOCK_SIZE;
        }
        else{
            bytes_to_read = bytes_left;
        }
        
        fseek(input_file, -bytes_to_read, SEEK_CUR);

        size_t bytes_read = fread(buffer, sizeof(char), bytes_to_read, input_file);

        for(int i = 0; i < bytes_read/2; i++){
            c = buffer[i];
            buffer[i] = buffer[bytes_read - 1 - i];
            buffer[bytes_read - 1 - i] = c;
        }
        
        fwrite(buffer, sizeof(char), bytes_read, output_file);
        fseek(input_file, -BLOCK_SIZE, SEEK_CUR);
        bytes_left -= bytes_read;

    }


    free(buffer);
}
#endif //BLOCK

#ifndef BLOCK

void reverse(FILE* input_file, FILE* output_file){
    char one_byte;
    fseek(input_file, 0, SEEK_END); // Ustawienie wskaźnika na koniec pliku

    long long file_size= ftell(input_file);
    long long position = 1; // Początkowa wartość dla cofania się o 1 bajt od końca pliku

    while (position <= file_size) {
        fseek(input_file, -position, SEEK_END); // Ustawienie wskaźnika na odpowiednią pozycję w pliku
        fread(&one_byte, sizeof(char), 1, input_file); // Odczytanie 1 bajtu
        fwrite(&one_byte, sizeof(char), 1, output_file); // Zapisanie bajtu do pliku wynikowego
        position++; // Przesunięcie na kolejny bajt
    }
}
#endif //BLOCK



 

int main(void) {
    FILE *input_file;
    input_file = fopen("input_file.txt", "rb");
    if (input_file == NULL) {
        printf("Error during file opening!\n");
        return 1;
    }

    FILE *output_file;
    output_file = fopen("output_file.txt", "wb");

    if (output_file == NULL) {
        printf("Error during file opening!\n");
        return 1;
    }


    clock_t start = clock();
    reverse(input_file, output_file);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;


    fclose(output_file);

    FILE *output_file_2;
    output_file_2 = fopen("output_file.txt", "rb");

    if (output_file_2 == NULL) {
        printf("Error during file opening!\n");
        return 1;
    }

    FILE *temp_file;
    
    temp_file = fopen("temp_file.txt","wb");
    
    if(temp_file == NULL){
        printf("Error opening temp_file.txt\n");
        return 1;
    }

    reverse(output_file_2, temp_file);

    FILE *stats_file;
    stats_file = fopen("_zad1.txt","a+");

    fseek(input_file, 0, SEEK_END);
    long long file_size = ftell(input_file);

    #ifndef BLOCK
        fprintf(stats_file,"\n");
        fprintf(stats_file,"Wiekosc pliku wejsciowego: ");
        fprintf(stats_file,"%lld\n",file_size);
        fprintf(stats_file, "Czas wykonania w sekundach funkcji reverse [czytanie po 1 znaku]: ");
        fprintf(stats_file, "%f\n", time_spent);
    #endif //BLOCK

    #ifdef BLOCK
        fprintf(stats_file,"\n");
        fprintf(stats_file,"Wiekosc pliku wejsciowego: ");
        fprintf(stats_file,"%lld\n",file_size);
        fprintf(stats_file, "Czas wykonania w sekundach funkcji reverse [czytanie blokow po 1024 znaki]: ");
        fprintf(stats_file, "%f\n", time_spent);
    #endif //BLOCK

    
    fclose(input_file);
    fclose(output_file_2);
    fclose(temp_file);
    
    return 0;
}
