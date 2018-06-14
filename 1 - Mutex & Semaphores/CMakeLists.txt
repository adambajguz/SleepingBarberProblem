cmake_minimum_required(VERSION 3.10)
project(PR1_mutexy_i_semafory C)

set(CMAKE_C_STANDARD 11)

add_executable(PR1_mutexy_i_semafory main.c clients_queue.c clients_queue.h utils.c utils.h barber.c barber.h)