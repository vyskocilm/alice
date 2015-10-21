#include <czmq.h>
#include <malamute.h>
#include <stdlib.h>

int max(int a, int b ) { return a > b ? a : b; }
int min(int a, int b ) { return a > b ? b : a; }

int main(int argc, char** argv) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s address ups_name\n", argv[0]);
        exit(1);
    }

    char *addr = argv[1];
    char *name = argv[2];

    mlm_client_t *client = mlm_client_new();
    mlm_client_connect(client, addr, 5000, name);
    mlm_client_set_producer(client, "METRICS");

    bool state = random()%2;
    int timeout = 0;
    int power = 100;
    char topic[256];
    char value[256];
    while(!zsys_interrupted) {
        if(timeout == 0) {
            state = !state;
            timeout = 5 + random()%20;
        }
        timeout--;
        if(state) {
            power = min(100, power + 2);
        } else {
            power = max(0, power - 1);
        }
        sprintf(topic,"power.%s", name);
        sprintf(value,"%d", power);
        mlm_client_sendx(client, topic, name, "power", value, NULL);
        printf("%s = %s\n", topic, value);
        sprintf(topic,"state.%s", name);
        sprintf(value,"%d", state);
        mlm_client_sendx(client, topic, name, "state", value, NULL);
        printf("%s = %s\n", topic, value);
        sleep(1);
    }
    mlm_client_destroy(&client);
}
