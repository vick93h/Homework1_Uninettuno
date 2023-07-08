//
// Created by linux on 08/07/23.
//

#include "queueLinkedList.h"
#include<stdlib.h>

void initQueue(queue_t* queue,unsigned int size){
    queue->frontp = NULL;
    queue->rearp = NULL;
    queue->size = size;
}
void insert(queue_t* queue, msg_t* element){
    if(queue->size==0){
        queue->rearp=(queue_node_t*) malloc(sizeof (queue_t));
        queue->frontp=queue->rearp;
        }
    else
        {
            queue->rearp->restp=(queue_node_t*) malloc(sizeof (queue_node_t));
            queue->rearp=queue->rearp->restp;
        }
    queue->rearp->element=element;
    queue->rearp->restp=NULL;
    ++(queue->size);
}
msg_t* dequeue(queue_t* queue){
        queue_node_t *to_freep; //puntatore al nodo da rimuovere;
        to_freep=queue->frontp;
        msg_t* ans=to_freep->element;
        queue->frontp=to_freep->restp;
        free(to_freep);
        --(queue->size);
        if(queue->size==0)
            queue->rearp=NULL;
        return ans;
}
unsigned int size(queue_t* queue)
    {
        return queue->size;
    }
void deleteQueue(queue_t* queue) {
    queue_node_t* currentNode = queue->frontp;

    while (currentNode != NULL) {
        queue_node_t* nodeToRemove = currentNode;
        currentNode = currentNode->restp;
        free(nodeToRemove);
    }

    queue->frontp = NULL;
    queue->rearp = NULL;
    queue->size = 0;
}
