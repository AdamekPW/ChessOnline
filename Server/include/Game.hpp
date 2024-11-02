#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>
#include <random>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;



struct Player {
    int socket;
    bool isWhite;
    string nick;
};

class Game {
    private:
        Player _getPlayer(bool isWhite);
    public:
        Player player_1, player_2;

        Game(int player_1_socket, int player_2_socket);
        ~Game();
        bool SendStartInfo();
        int Loop();
};

#endif