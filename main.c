#include <stdio.h>
#include "buffer_t.h"
#include <stdlib.h>
#include "msg_t.h"
#include <pthread.h>
#define NumMessage 10
void* producer(void *arg);
void* consumer(void *arg);
int main() {
    buffer_t *buffer=(buffer_t*) malloc(sizeof (buffer_t));
    buffer_init(buffer,10);
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->full, NULL);
    pthread_cond_init(&buffer->empty, NULL);
    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL,  producer, (void*)buffer);
    pthread_create(&consumerThread, NULL, consumer, (void*) buffer);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    buffer_destroy(buffer);
    return 0;
}
void* producer(void *arg) {
buffer_t *buffer=(buffer_t *) arg;
for(int i=0;i<NumMessage;i++){
    int *ptr=(int*) malloc(sizeof(int));
    *ptr=i;
    msg_t* message=(msg_t*) malloc(sizeof(msg_t));
    message->content=ptr;
    put_bloccante(buffer,message);
    int* contentPtr = (int*)(message->content);
    printf("\nIl produttore produce il messaggio : %d",*contentPtr);
    }
pthread_exit(NULL);
}

void*  consumer(void *arg) {
    buffer_t *buffer=(buffer_t *) arg;
    for(int i=0;i<NumMessage;i++){
        msg_t* message=(msg_t*)malloc(sizeof(msg_t));
        message=get_bloccante(buffer);
        int* contentPtr = (int*)message->content;
        int contentValue = *contentPtr;
        printf("\nIl consumatore  consuma il messaggio : %d",contentValue);
    }
    pthread_exit(NULL);
}