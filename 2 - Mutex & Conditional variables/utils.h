#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include "clients_queue.h"
#include "barber.h"

struct Client;
struct BarberData;


void print_str(char *str);

void print_int(uint32_t i);

void print_info(struct BarberData *data);


#endif //UTILS_H
