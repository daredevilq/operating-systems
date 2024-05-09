#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


int main(){
    
    DIR *test_dir = opendir("testdir");
    mkdir("te",S_IRWXU | S_IRWXG | S_IRWXO);
    rewinddir(test_dir);
    struct stat *buff_stat;
    struct dirent *dir_p = readdir(test_dir);

    while(dir_p != NULL)
    {
        // printf("d_info %ld\n", dir_p->d_ino);
        printf("\n");
        printf("%s\n", dir_p->d_name);
        // printf("\n");
        // printf("%ld\n", dir_p->d_off);
        // printf("\n");
        // printf("%d\n", dir_p->d_reclen);
        // printf("\n");
        // printf("%d\n", dir_p->d_type);

        dir_p = readdir(test_dir);
    }

    stat("testdir/file1.txt", buff_stat);

    printf("%ld\n", buff_stat->st_size);







    closedir(test_dir);
    

    return 0;
}