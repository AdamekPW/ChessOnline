#ifndef CLIENT
#define CLIENT

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>
#include <string>
#include <iostream>
#include "Client.hpp"
#include <nlohmann/json.hpp>
#include <cstring>
#include "board.hpp"
#include "common.hpp"
using json = nlohmann::json;

using namespace std;

class Client {
    private:
        struct sockaddr_in _serverAddr;
        int _serverPort;
        socklen_t _addr_size;
    public:
        int Socket;
        Client(string serverAddresss, int serverPort);
        ~Client();
        bool Connect();
        bool SendMove(int x_from, int y_from, int x_to, int y_to);
        bool GetBoard(Board &board);

};


#endif