#include <iostream>
#include "httplib/httplib.h"
#include <stdlib.h>

struct RequestInfo {
    std::string url;
    int times;
};


void    *run_http_request(void* arg) {
    RequestInfo* info = static_cast<RequestInfo*>(arg);
    httplib::Client client(info->url);

    httplib::Headers headers = {
        {"Connection", "keep-alive"}
        // Puedes agregar otros encabezados aquí si es necesario
    };
    int times = info->times;
    while (times--)
    {
        auto res = client.Get("/" /*, headers*/);
        
        if (res) {
            if (res->status == 200) {
                
            } else {
                std::cerr << "Error en la respuesta: " << res->status << std::endl;
            }
        } else {
            std::cerr << "Error en la solicitud." << std::endl;
        }
    }

    return NULL;
}

int main(int argc, char **argv) {

    if(argc != 3 && argc != 4) {
        std::cerr << "Bad args; {url} {times} [threads]";
        exit(1);
     }
        

    char *endPtr;

    char *url = argv[1];
    int times = strtol(argv[2], &endPtr, 10);

    if(0 > times) {
        std::cerr << "Times cannot be less than 0";
        exit(1);
    }

    int num_threads = 1;
    if(argc == 4)
        num_threads = strtol(argv[3], &endPtr, 10);
    if(0 > num_threads) {
        std::cerr << "Threads cannot be less than 0";
        exit(1);
    }

    pthread_t threads[num_threads];
    RequestInfo info;

    info.url = std::string(url);
    info.times = times;

    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, run_http_request, &info) != 0) {
            std::cerr << "Error al crear el thread " << i << std::endl;
            return 1;
        }
    }

    // Esperar a que todos los threads terminen
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            std::cerr << "Error al esperar al thread " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Se realizaron un total de " << (info.times * num_threads) << " peticiones" << std::endl;

    return 0;
}


/*int main(int argc, char **argv) {


    if(argc != 2)
        std::cerr << "Bad args; {url} {times}"

    char *url = argv[1];
    int times = strtol(argv[2]);



}*/