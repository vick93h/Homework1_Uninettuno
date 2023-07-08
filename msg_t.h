//
// Created by linux on 08/07/23.
//

#ifndef HOMEWORKESAME_MSG_T_H
#define HOMEWORKESAME_MSG_T_H
typedef struct {
    void* content;
}msg_t;

msg_t* msg_init(void* content);
void msg_destroy(msg_t* msg);
msg_t* msg_copy(const msg_t* msg);

#endif //HOMEWORKESAME_MSG_T_H
