cmake_minimum_required(VERSION 3.25)
project(HomeworkEsame C)

set(CMAKE_C_STANDARD 11)

add_executable(HomeworkEsame main.c msg_t.c msg_t.h buffer_t.c buffer_t.h queueLinkedList.c queueLinkedList.h)
