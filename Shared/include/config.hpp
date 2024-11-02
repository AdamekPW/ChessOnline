#ifndef CONFIG
#define CONFIG


#include <fstream>
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
#include <nlohmann/json.hpp>
#include <cstring>

using json = nlohmann::json;

struct ServerConfig {
    std::string ip;
    int port;
};

ServerConfig loadConfig(const std::string& configPath);
void set_nonblocking(int socket);
void set_blocking(int socket); 

#endif