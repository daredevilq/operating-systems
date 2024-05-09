#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){


    
    // int fd1 = creat("text.txt", O_RDWR);
    
    // printf("%d\n",fd1);
    
    // int fd = open("test.txt", O_RDWR);
    
    // char buff[100];

    // while (read(fd, buff, sizeof(buff)))
    // {
    //     printf("%s\n", buff);
    // }
    // sleep(1);
    // char *string = "TO TRZEBA WPISAC!\n";
    // char *start = "TO NA POCZATEK\n";

    // printf("%ld\n",sizeof(string));
    // printf("%ld\n",strlen(string));
    

    // write(fd, string, strlen(string));
    

    // printf("\n\n\n");
    // long pos = lseek(fd, 0, SEEK_SET);
    
    // write(fd, start, strlen(start));

    // close(fd);
    
//     char blok[5];
//     int we, wy;
//     int liczyt;
//     we=open("test.txt", O_RDONLY);
//     wy=open("wy.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
//     while((liczyt=read(we,blok,sizeof(blok)))>0)
//       write(wy,blok,liczyt);


//   close(we);

//   close(wy);
    FILE *test = fopen("test.txt", "r+");

    char buff[1024];
    size_t bytes_read;

    while((bytes_read = fread(buff, sizeof(char), 1024, test))>0){
        printf("%ld\n",bytes_read);
        printf("%s\n",buff);
        printf("%d\n", fgetpos())
    };
    sleep(1);

    char *to_add = "ALA MA KOTA\n ";

    fwrite(to_add, sizeof(char), strlen(to_add), test);
    
    fseek(test, 0, SEEK_SET);

    fwrite(to_add, sizeof(char), strlen(to_add), test);

    char *at_end = "MATKO JEDYNA";

    fseek(test, 0,SEEK_END);

    fwrite(at_end, sizeof(char), strlen(at_end), test);

    return 0;
}