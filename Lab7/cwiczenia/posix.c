#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#define QUEUE_NAME "/moja_kolejka"
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 10)

int main() {

    mq_unlink(QUEUE_NAME);
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MSG_BUFFER_SIZE];
    char buffer_2[MSG_BUFFER_SIZE];
    char buffer_3[MSG_BUFFER_SIZE];
    int msg_prio = 1; 

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MAX_MSG_SIZE;
    
    mq = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, 0644, &attr);
    
    strcpy(buffer, "Wiadomosc 1\0");
    if (mq_send(mq, buffer, strlen(buffer) + 1, msg_prio) == -1) {
        perror("mq_send");
        exit(1);
    }


    strcpy(buffer, "Wiadomosc 2\0");

    if (mq_send(mq, buffer, strlen(buffer) + 1, msg_prio ) == -1)
    {
        perror("error");
        exit(1);
    }
    
    //mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);

    ssize_t bytes_read = mq_receive(mq, buffer_2, MSG_BUFFER_SIZE, &msg_prio);

    printf("Odebrano wiadomosc: %s\n", buffer_2);


    bytes_read = mq_receive(mq, buffer_3, MSG_BUFFER_SIZE, &msg_prio);


    printf("Odebrano wiadomosc: %s\n", buffer_3);

    
    return 0;
}
