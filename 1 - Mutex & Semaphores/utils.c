#include "utils.h"


void print_str(char *str) {
    if (write(STDOUT_FILENO, str, strlen(str)) < 0) {
        perror("write");
        exit(1);
    }
}

void print_int(uint32_t i) {
    char int_buffer[8];

    uint32_t len = sprintf(int_buffer, "%d", i);
    int_buffer[len] = '\0';

    if (write(STDOUT_FILENO, int_buffer, strlen(int_buffer)) < 0) {
        perror("write");
        exit(1);
    }
}

void print_info(struct BarberData *data) {
    print_str("Res: ");
    print_int(data->resigned_clients_num);

    print_str(" WRoom: ");
    print_int(data->clients_waiting_num);
    print_str("/");
    print_int(data->chairs_num);

    print_str(" [in: ");
    print_int(data->clients_in_barber_num);
    print_str("]\n");

    if (data->debug) {
        print_str("Clients waiting: ");
        queue_print(data->clients_to_barber_queue);
        print_str("\n");

        print_str("Resigned clients: ");
        queue_print(data->resigned_clients_queue);
        print_str("\n");
    }
    print_str("\n");
}

