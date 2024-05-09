#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* ps_output = popen("ps aux", "r"); // Uruchomienie polecenia "ps aux" i ustawienie trybu czytania
    FILE* wc_input = popen("wc -l", "w"); // Uruchomienie polecenia "wc -l" i ustawienie trybu zapisu

    char buffer[4096];
    size_t bytes_read;

    // Czytanie danych z ps_output i przekazywanie ich do wc_input
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), ps_output)) > 0) {
        fwrite(buffer, 1, bytes_read, wc_input);
    }

    // Zamknięcie potoków
    if (pclose(ps_output) == -1) {
        perror("pclose ps");
        exit(EXIT_FAILURE);
    }

    if (pclose(wc_input) == -1) {
        perror("pclose wc");
        exit(EXIT_FAILURE);
    }

    return 0;
}
