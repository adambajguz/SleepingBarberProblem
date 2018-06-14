cmake_minimum_required(VERSION 3.10)
project(PR2_mutexy_i_zmienne_warunkowe C)

set(CMAKE_C_STANDARD 11)

add_executable(PR2_mutexy_i_zmienne_warunkowe main.c clients_queue.c clients_queue.h utils.c utils.h barber.c barber.h)