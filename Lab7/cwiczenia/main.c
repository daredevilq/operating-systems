#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>


int main(){

    // key_t key = ftok(".", "a");
    // int id;



    char *word = "Wiadomosc wyslana do kolejki\n\0";
    
    char mess[100];

    unsigned int prio;

    struct mq_attr attributes = {
        .mq_flags = 0,
        .mq_msgsize = strlen(word),
        .mq_maxmsg = 10
    };


    mqd_t q_desc = mq_open("/queue", O_CREAT | O_RDWR |S_IRUSR | S_IWUSR, &attributes );  


    mq_send(q_desc, word, strlen(word) + 1, prio);


    sleep(3);
    mq_receive(q_desc, mess, strlen(word) + 1, &prio);
    

    printf("%s\n", mess);
    //while(1) sleep(1);


    return 0;
}