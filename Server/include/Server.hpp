#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>
#include <string>
#include <iostream>
#include <queue>
#include "Game.hpp"
#include "ServerStructs.h"
#include "common.hpp"
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;
using namespace std;

class Server{
    private:
        int _port;
        string _address;
        struct sockaddr_storage _serverStorage;
        socklen_t _addr_size;

        queue<int> playerQueue;
        int _takeFristConnected();
        static void* _gameThread(void *arg);
    public:
        vector<pthread_t> activeGameThreads;
        int serverSocket;
        struct sockaddr_in serverAddr;
        Server(int port);
        ~Server();
        bool Listen();
        bool Accept();
        bool StartGame();
       

};

#endif