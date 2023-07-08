//
// Created by linux on 08/07/23.
//
#include <pthread.h>
#include "buffer_t.h"
#include <stdlib.h>
buffer_t* buffer_init(buffer_t* buffer,int maxsize){
    buffer->maxSize = maxsize;
    queue_t *m=(queue_t*) malloc(sizeof(queue_t));
    buffer->messages=m;
    return buffer;
}
void buffer_destroy(buffer_t* buffer){
    deleteQueue(buffer->messages);
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->full);
    pthread_cond_destroy(&buffer->empty);

    // Dealloca la struttura del buffer
    free(buffer);
}
msg_t* put_bloccante(buffer_t* buffer, msg_t *msg){
    pthread_mutex_lock(&buffer->mutex);
    while(size(buffer->messages)==buffer->maxSize){
        pthread_cond_wait(&buffer->full, &buffer->mutex);
    }
    insert(buffer->messages,msg);
    pthread_cond_signal(&buffer->empty);
    pthread_mutex_unlock(&buffer->mutex);
    return msg;
}
msg_t* get_bloccante(buffer_t* buffer){
    pthread_mutex_lock(&buffer->mutex);
    while(size(buffer->messages)==0){
        pthread_cond_wait(&buffer->empty, &buffer->mutex);
    }
    //consumo
    msg_t *m=(msg_t*) malloc(sizeof(msg_t));
    m=dequeue(buffer->messages);
    pthread_cond_signal(&buffer->full);
    pthread_mutex_unlock(&buffer->mutex);
    return m;
}
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg){
    pthread_mutex_lock(&buffer->mutex);
    if(size(buffer->messages)==buffer->maxSize){
        pthread_cond_signal(&buffer->empty);
        pthread_mutex_unlock(&buffer->mutex);
        return BUFFER_ERROR;
    }
    else{
        pthread_cond_wait(&buffer->full, &buffer->mutex);
        insert(buffer->messages,msg);
        pthread_cond_signal(&buffer->empty);
        pthread_mutex_unlock(&buffer->mutex);
        return msg;
    }
}
msg_t* get_non_bloccante(buffer_t* buffer){
    pthread_mutex_lock(&buffer->mutex);
    if(size(buffer->messages)==0) {
        pthread_cond_signal(&buffer->full);
        pthread_mutex_unlock(&buffer->mutex);
        return BUFFER_ERROR;
    }
    else{
        pthread_cond_wait(&buffer->empty, &buffer->mutex);
        msg_t *m=(msg_t*) malloc(sizeof(msg_t));
        m= dequeue(buffer->messages);
        pthread_cond_signal(&buffer->full);
        pthread_mutex_unlock(&buffer->mutex);
        return m;
    }

}