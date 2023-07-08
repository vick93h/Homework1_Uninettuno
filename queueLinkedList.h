//
// Created by linux on 08/07/23.
//

#ifndef HOMEWORKESAME_QUEUELINKEDLIST_H
#define HOMEWORKESAME_QUEUELINKEDLIST_H

#include "msg_t.h"

typedef struct queue_node_s{
    msg_t *element;
    struct queue_node_s *restp; //puntatore al successivo

}queue_node_t;
typedef struct{
    queue_node_t  *frontp; //puntatore alla testa
    queue_node_t  *rearp;  //puntatore alla coda
    unsigned int size;
}queue_t;

void initQueue(queue_t* queue,unsigned int size);
void insert(queue_t* queue, msg_t *element);
msg_t* dequeue(queue_t* queue);
unsigned int size(queue_t* queue);
void deleteQueue(queue_t* queue);
#endif //HOMEWORKESAME_QUEUELINKEDLIST_H
