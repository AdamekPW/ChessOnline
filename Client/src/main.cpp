#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>
#include <signal.h>
#include "Client.hpp"
#include "config.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//cd /home/adam/Pulpit/ChessServer/Client/build
//make clean
//cmake .. && make && ./ChessClient

void handle_sigint(int sig){
    std::cout << "\nClosing program..." << std::endl;
    exit(0); 
}

int main(){
    signal(SIGINT, handle_sigint);
    ServerConfig config;
    try {
        config = loadConfig("../Shared/config.json");
    } catch (const std::exception& e) {
        cout << "Error while opening config.json file: " << e.what() << std::endl;
        return 1;
    }

    Client client = Client(config.ip, config.port);
    if (!client.Connect())
        return EXIT_FAILURE;
    
    cout << "Połączono z serwerem." << endl;


    char buffer[1024];
    int bytes_received = recv(client.Socket, buffer, 1024 - 1, 0);
    if (bytes_received < 0) {
        cerr << "Receive failed" << endl;
        close(client.Socket);
        return 1;
    }
    buffer[bytes_received] = '\0';  
    cout << "Received JSON: " << buffer << endl;
    while (true){

        // try {
        //     json json_obj = json::parse(buffer);

        //     cout << "Type: " << json_obj["type"].get<string>() << endl;
        //     cout << "Color: " << json_obj["color"].get<string>() << endl;
        //     cout << "Opponent_nick: " << json_obj["opponent_nick"].get<string>() << endl;
        // } catch (json::parse_error& e) {
        //     cerr << "JSON parsing error: " << e.what() << endl;
        // }

    }

  return 0;
}