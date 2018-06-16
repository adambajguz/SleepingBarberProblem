#include "barber.h"

void barber_thread(struct BarberData *data) {
    while (1) {
        /* Fryzjer oczekuje na klienta. Jeśli nie ma żadnego klienta to śpi.
           Wykorzystano zasadę działania semafora.
        */
        sem_wait(&data->client_is_ready);

        /* Blokada dostępu do zmiany stanu poczekalni, ponieważ będziemy zmieniać stan krzeseł
           i nie chcemy aby inny wątek zmienił ich stan.

           Zmiana stanu krzeseł jest spowodowana wezwaniem kolejnego klienta na strzyżenie.
        */
        pthread_mutex_lock(&data->chair_access_lock);

        data->clients_waiting_num--;
        struct Client *new_client = queue_get_next_client(&data->clients_to_barber_queue);
        data->clients_in_barber_num = new_client->id;

        print_str("Next client for hair cut!\n");
        print_info(data);

        // Odblokowujemy dostęp do zmiany stanu poczekalni bo już wzieliśmy klienta.
        pthread_mutex_unlock(&data->chair_access_lock);

        // Ustawiamy w kliencie, że teraz jest jego kolej na strzyżenie.
        sem_post(&new_client->turn_for_cutting);

        // Blokujemy dostęp do zmiany stanu strzyżenia, bo fryzjer już strzyże naszego klienta.
        pthread_mutex_lock(&data->cutting_state_lock);

        sleep(rand() % 5);

        // Ustawiamy w kliencie że już został ostrzyżony oraz odblokowujemy dostęp do zmiany stanu strzyżenia.
        sem_post(&new_client->was_already_cut);
        pthread_mutex_unlock(&data->cutting_state_lock);

        data->clients_in_barber_num = 0;
    }
}

void customer_thread(struct BarberData *data) {
    /* Blokada dostępu do zmiany stanu poczekalni (liczbę wolnych krzeseł), ponieważ będziemy zmieniać stan krzeseł
      i nie chcemy aby inny wątek zmienił ich stan.

      Zmiana stanu krzeseł jest spowodowana przyjściem nowego klienta na strzyżenie.
    */
    pthread_mutex_lock(&data->chair_access_lock);

    data->total_clients_num++;

    // Jeśli nie ma miejsca w poczekalni
    if (data->clients_waiting_num >= data->chairs_num) {
        // Wpisujemy że klient zrezygnował ze strzyżenia
        queue_add_client(&(data->resigned_clients_queue), data->total_clients_num);
        data->resigned_clients_num++;

        print_str("New client resigned!\n");

        print_info(data);

        // Odblokowujemy dostęp do zmiany stanu poczekalni bo klient już przyszedł ale nie został w poczekalni.
        pthread_mutex_unlock(&data->chair_access_lock);
    } else {
        data->clients_waiting_num++;

        struct Client *newClient = queue_add_client(&(data->clients_to_barber_queue), data->total_clients_num);
        print_str("New client in waiting room!\n");
        print_info(data);

        // Informujemy fryzjera że klient jest gotowy na strzyżenie
        sem_post(&data->client_is_ready);

        // Odblokowujemy dostęp do zmiany stanu poczekalni bo klient już przyszedł i zgłosił że jest gotów na strzyżenie.
        pthread_mutex_unlock(&data->chair_access_lock);

        // Klient oczekuje aż nastąpi jego kolej na strzyżenie
        sem_wait(&newClient->turn_for_cutting);

        // Klient oczekuje aż skończy się jego strzyżenie
        sem_wait(&newClient->was_already_cut);
    }
}

