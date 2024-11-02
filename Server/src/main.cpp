#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>

#include "ServerStructs.h"
#include "Server.hpp"
#include <iostream>
#include "common.hpp"
//g++ server.c -lpthread -ServerStructs && ./a.out



using namespace std;


int main(){
    ServerConfig config;
    try {
        config = loadConfig("../Shared/config.json");
    } catch (const std::exception& e) {
        cout << "Error while opening config.json file: " << e.what() << std::endl;
        return 1;
    }


    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    Server server = Server(config.port);
    
    if (!server.Listen()) 
        return EXIT_FAILURE;


    while(1)
    {
        server.Accept();

        //pthread_detach(thread_id);
        //pthread_join(thread_id, NULL);
    }
    return EXIT_SUCCESS;
}
