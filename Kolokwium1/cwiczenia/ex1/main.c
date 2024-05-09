#include <stdio.h>
#include <stdlib.h>

#define BUFFER 100

int main(){
    
    FILE *output;
    char buffer[BUFFER];

    output = popen("ps aux | wc -l", "r");
    
    if (fgets(buffer, BUFFER, output) != NULL)
    {
        printf("%s\n", buffer);
    }
    
    pclose(output);


    return 0;
}