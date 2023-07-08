//
// Created by linux on 08/07/23.
//

#ifndef HOMEWORKESAME_BUFFER_T_H
#define HOMEWORKESAME_BUFFER_T_H

#include <bits/pthreadtypes.h>
#include "queueLinkedList.h"
#define BUFFER_ERROR (msg_t *) NULL
typedef struct{
    unsigned int maxSize;
    queue_t *messages; //cosa di messaggi di tipo msg_t;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
}buffer_t;
buffer_t* buffer_init(buffer_t* buffer,int maxsize);
void buffer_destroy(buffer_t* buffer);
msg_t* put_bloccante(buffer_t* buffer, msg_t *msg);
msg_t* get_bloccante(buffer_t* buffer);
msg_t* put_non_bloccante(buffer_t* buffer, msg_t* msg);
msg_t* get_non_bloccante(buffer_t* buffer);
#endif //HOMEWORKESAME_BUFFER_T_H
