//
// Created by linux on 08/07/23.
//

#include "msg_t.h"
#include <stdlib.h>
msg_t* msg_init(void* content){
    msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
    if (msg != NULL) {
        msg->content = content;
    }
    return msg;
}
void msg_destroy(msg_t* msg){
    if (msg != NULL) {
        free(msg);
    }
}
msg_t* msg_copy(const msg_t* msg){
    if (msg == NULL) {
        return NULL;
    }

    msg_t* copy = (msg_t*)malloc(sizeof(msg_t));
    if (copy != NULL) {
        copy->content = msg->content;
    }
    return copy;
}