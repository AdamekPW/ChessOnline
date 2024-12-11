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

    bool isWhiteToMove = true;
    string castling = "1111";
    int moveNumber = 0;         
    Board& board;              

    void Print();
    explicit DataPackage(Board& board)
        : board(board) {} 
};


ServerConfig loadConfig(const std::string& configPath);
void set_nonblocking(int socket);
void set_blocking(int socket); 
bool SendConfirmation(int socket);
int RecvConfirmation(int socket);
bool SendPromotion(int socket, int &figureId);
int RecvPromotion(int socket, int &figureId);
void getCastling(string &castling, Board &board);
string getCastlingString(Board &board);
int RecvDataPackage(int socket, DataPackage &dataPackage, bool isBlocking);
bool SendDataPackage(int socket, DataPackage &dataPackage);

#endif