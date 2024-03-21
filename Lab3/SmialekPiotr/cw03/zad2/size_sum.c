#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(){

    DIR *dir;
    long long total_size;
    struct dirent *entry;
    struct stat bufor_stat;
    
    
    dir = opendir("test-directory");

    if (dir == NULL)
    {
        printf("Failed to open directory\n");
        return 1;
    }

    FILE *stats_file;
    stats_file = fopen("_zad2.txt","a+");
    
    if (stats_file == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    
    
    rewinddir(dir);
    entry = readdir(dir);    
    while (entry != NULL){
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            
            char path[1024];
            sprintf(path, "%s/%s", "test-directory", entry->d_name);
            if (stat(path, &bufor_stat) == -1) {
                perror("Getting file info went wrong!");
                closedir(dir);
                return 1;
            }

            if(!S_ISDIR(bufor_stat.st_mode)){
                fprintf(stats_file, "\n");
                fprintf(stats_file, "%s ",entry->d_name);
                fprintf(stats_file, "%lld ", (long long) bufor_stat.st_size);
                fprintf(stats_file, "bytes");

                // printf("%-20s %lld bytes\n", entry->d_name, (long long) bufor_stat.st_size);
                total_size += bufor_stat.st_size;
            }

        }
        entry = readdir(dir);        
    }
    
    fprintf(stats_file, "\n");
    fprintf(stats_file, "Total size of all files in directory %s: %lld bytes\n", "test-directory", total_size);
    // printf("Total size of all files in directory %s: %lld bytes\n","test-directory", total_size);
    

    fclose(stats_file);
    closedir(dir);
    return 0;
}