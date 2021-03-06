#ifndef BARBER_H
#define BARBER_H

#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>

#include "utils.h"
#include "clients_queue.h"

struct Client;
struct BarberData;

void barber_thread(struct BarberData *data);
void customer_thread(struct BarberData *data);

struct BarberData {
    pthread_cond_t client_is_ready, barber_is_cutting;
    pthread_mutex_t chair_access_lock, barber_access_lock, cutting_state_lock;

    uint32_t clients_waiting_num, total_clients_num;
    uint32_t chairs_num;

    uint32_t resigned_clients_num, clients_in_barber_num;
    uint32_t cutting;

    bool debug;

    struct Client *clients_to_barber_queue, *resigned_clients_queue;

};

#endif //BARBER_H
