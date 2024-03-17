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
                printf("%-20s %lld bytes\n", entry->d_name, (long long) bufor_stat.st_size);
                total_size += bufor_stat.st_size;
            }

        }
        entry = readdir(dir);        
    }
    
    printf("Total size of all files: %lld bytes\n", total_size);



    closedir(dir);
    return 0;
}