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
#include <vector>
#include "board.hpp"
#include "common.hpp"

#define MESSAGE_LENGTH 20

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
        Board board;
        
        Game(int player_1_socket, int player_2_socket);
        ~Game();
        bool SendStartInfo();
        int Loop();

        vector<int> GetMove(char move[MESSAGE_LENGTH]);
        bool SendBoard();
};

#endif