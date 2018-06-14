#ifndef CLIENTS_QUEUE_H
#define CLIENTS_QUEUE_H

#include <stdlib.h>
#include <inttypes.h>
#include <semaphore.h>

#include "utils.h"

struct Client;

void queue_print(struct Client *start);

struct Client *queue_add_client(struct Client **start, uint32_t id);

struct Client *queue_get_next_client(struct Client **node);

struct Client {
    uint32_t id;
    pthread_cond_t turn_for_cutting;
    struct Client *next_client;
};

#endif //CLIENTS_QUEUE_H
