#include "clients_queue.h"

void queue_print(struct Client *node) {
    while (node) {
        print_int(node->id);
        print_str(" ");
        node = node->next_client;
    }
}


struct Client *queue_add_client(struct Client **node, uint32_t id) {
    // Create new client
    struct Client *new_client = malloc(sizeof(*new_client));

    // Init id and next_client pointer
    new_client->id = id;
    new_client->next_client = NULL;

    // Init conditional variable for current client
    pthread_cond_init(&new_client->turn_for_cutting, NULL);

    // If queue is empty
    if (*node) {
        struct Client *temp_client = *node;

        // Add client to the end of queue
        while (temp_client->next_client)
            temp_client = temp_client->next_client;
        temp_client->next_client = new_client;
    } else
        *node = new_client;

    return new_client;
}


// Get client from waiting room to cut him
struct Client *queue_get_next_client(struct Client **node)
{
    // Get next client and save its pointer
    struct Client *next_client = *node;

    // Move to second client
    *node = (*node)->next_client;

    return next_client;
}