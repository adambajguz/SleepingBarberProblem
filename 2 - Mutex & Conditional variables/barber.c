#include "barber.h"

void barber_thread(struct BarberData *data) {
    while (1) {
        // Fryzjer oczekuje na klienta. Jeśli nie ma żadnego klienta to śpi.
        pthread_mutex_lock(&data->chair_access_lock);
        while (data->clients_waiting_num == 0) {
            data->clients_in_barber_num = 0;
            pthread_cond_wait(&data->client_is_ready, &data->chair_access_lock);
        }

        // Gdy wyjdziemy z pętli, oznacza to że przyszedł klient na strzyżenie
        data->clients_waiting_num--;

        // Pobieramy klienta z poczekalni
        struct Client *client = queue_get_next_client(&data->clients_to_barber_queue);
        data->clients_in_barber_num = client->id;

        printf("Next client for hair cut!\n");
        print_info(data);

        // Odblokowujemy możliwość zmianu stanu poczekalni
        pthread_mutex_unlock(&data->chair_access_lock);

        // Ustawiamy w kliencie, że teraz jest jego kolej na strzyżenie.
        pthread_cond_signal(&client->turn_for_cutting);

        // Blokujemy dostęp do zmiany stanu strzyżenia, bo fryzjer już strzyże naszego klienta.
        pthread_mutex_lock(&data->cutting_state_lock);

        // Ustawiamy zmienną warunkową że strzyżemy
        data->cutting = 1;

        // Sygnalizujemy że strzyżemy klienta
        pthread_cond_signal(&data->barber_is_cutting);

        sleep(rand() % 5);

        // Kończymy strzyżenie
        data->cutting = 0;

        // Sygnalizujemy że fryzjer skończył strzyżenie klienta
        pthread_mutex_unlock(&data->cutting_state_lock);
    }
}

void customer_thread(struct BarberData *data) {
    /* Blokada dostępu do zmiany stanu poczekalni (liczbę wolnych krzeseł), poniewąż bedziemy zmieniać stan krzeseł
        i nie chcemy aby inny wątek zmienił ich stan.

        Zmiana stanu krzeseł jest spowodowana przyjściem nowego klienta na strzyżenie.
    */
    pthread_mutex_lock(&data->chair_access_lock);

    ++data->total_clients_num;

    // Jeśli jest miejsce w poczekalni
    if (data->clients_waiting_num < data->chairs_num) {
        data->clients_waiting_num++;

        struct Client *client = queue_add_client(&data->clients_to_barber_queue, data->total_clients_num);
        printf("New client in waiting room!\n");
        print_info(data);

        // Informujemy fryzjera że klient jest gotowy na strzyżenie
        pthread_cond_signal(&data->client_is_ready);

        // Odblokowujemy dostęp do zmiany stanu poczekalni bo klient już przyszedł i zgłosił że jest gotów na strzyżenie.
        pthread_mutex_unlock(&data->chair_access_lock);

        // Klient oczekuje aż nastąpi jego kolej na strzyżenie, blokujemy dostęp do fryzjera
        pthread_mutex_lock(&data->barber_access_lock);
        while (data->clients_in_barber_num != data->total_clients_num)
            pthread_cond_wait(&client->turn_for_cutting, &data->barber_access_lock);

        // Klient dostał się do fryzjera więc zdejmujemy blokadę
        pthread_mutex_unlock(&data->barber_access_lock);

        // Klient oczekuje aż skończy się jego strzyżenie, blokujemy stan strzyżenia
        pthread_mutex_lock(&data->cutting_state_lock);
        while (data->cutting)
            pthread_cond_wait(&data->barber_is_cutting, &data->cutting_state_lock);

        // Klient został ostrzyżony zdejmujemy blokadę
        pthread_mutex_unlock(&data->cutting_state_lock);
    } else {
        // Wpisujemy że klient zrezygnował ze strzyżenia
        queue_add_client(&data->resigned_clients_queue, data->total_clients_num);
        data->resigned_clients_num++;

        printf("New client resigned!\n");

        print_info(data);

        // Odblokowujemy dostęp do zmiany stanu poczekalni bo klient już przyszedł ale nie został w poczekalni.
        pthread_mutex_unlock(&data->chair_access_lock);
    }
}

