#ifndef COMMON
#define COMMON


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
#include "board.hpp"

using json = nlohmann::json;

struct ServerConfig {
    std::string ip;
    int port;
};

struct DataPackage {
    string type = "";     
    bool amIWhite = false;     
    string opponentNick = ""; 

    bool isWhiteToMove = false; 
    int moveNumber = 0;         
    Board& board;              

    void Print();
    // Konstruktor inicjalizujący tylko Board
    explicit DataPackage(Board& board)
        : board(board) {} 
};


ServerConfig loadConfig(const std::string& configPath);
void set_nonblocking(int socket);
void set_blocking(int socket); 
bool SendConfirmation(int socket);
int RecvConfirmation(int socket);
bool RecvDataPackage(int socket, DataPackage &dataPackage, bool isBlocking);
bool SendDataPackage(int socket, DataPackage &dataPackage);

#endif