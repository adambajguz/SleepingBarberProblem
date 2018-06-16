#include <semaphore.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>

#include "utils.h"

// Mutex/semaphore version

void parse_args(int argc, char *argv[], struct BarberData *data);

void print_error();

void init_thread(pthread_t *thread, void *(*__start_routine)(void *), struct BarberData *data);

int main(int argc, char *argv[]) {
    // Barber data / Main program structure init
    struct BarberData data = {0, .chair_access_lock = PTHREAD_MUTEX_INITIALIZER,
                                 .cutting_state_lock = PTHREAD_MUTEX_INITIALIZER};

    // Init pseudorandom generator with seed based on current time
    srand(time(NULL));

    // Parser args
    parse_args(argc, argv, &data);

    // Semaphores init
    sem_init(&data.client_is_ready, 0, 0);
    sem_init(&data.cutting, 0, 0);

    // Init threads & main loop
    pthread_t barbers_thread, customers_thread;

    init_thread(&barbers_thread, (void *) barber_thread, &data);

    while (1) {
        sleep(rand() % 3);

        init_thread(&customers_thread, (void *) customer_thread, &data);
    }

    // Wait for termination ob barbers_thread
    pthread_join(barbers_thread, NULL);

    return 0;
}

void parse_args(int argc, char *argv[], struct BarberData *data) {
    if (argc < 2) {
        print_error();

        exit(-1);
    } else {
        data->chairs_num = atoi(argv[1]);

        if ( data->chairs_num == 0) {
            print_error();
            exit(-1);
        }
        else if (argc >= 3 && strncmp(argv[2], "-debug", 6) == 0)
            data->debug = true;
    }
}

void print_error() {
    print_str("No or invalid number of chairs given!\n=====\n\n");
    print_str("main [N] [-debug]\n\tN - nuber of chairs\n\t-debug - show debug info\n");
}

void init_thread(pthread_t *thread, void *(*function)(void *), struct BarberData *data) {
    int error = pthread_create(thread, NULL, function, data);

    if (error) {
        perror("pthread_create error!\n");
        exit(error);
    }
}
