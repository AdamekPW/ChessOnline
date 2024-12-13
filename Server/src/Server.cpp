#include "Server.hpp"


Server::Server(int port){
    this->_port = port;
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1){
        perror("Creating server socket error");
        return;
    }
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1){
        perror("Binding error");
        close(serverSocket);
        serverSocket = -1;
        return;
    }
    cout << "Server created!" << endl;
}   

Server::~Server(){
    //to do: close every connection
}

bool Server::Listen(){
    if(listen(serverSocket,10) != 0){
        cout << "Error occurs while starting a server!" << endl;
        return false;
    }
    cout << "Server running on port " << this->_port << endl;
    cout << "Listening..." << endl;
  
    return true;
}



void* Server::_gameThread(void* arg){
    struct players p = *((players *)arg);
    cout << "Game for: " << p.player_1_socket << " | " << p.player_2_socket << endl;

    Game game = Game(p.player_1_socket, p.player_2_socket);
    if (!game.Prepare()){
        cout << "Preparing error" << endl;
        pthread_exit(0);
    } else {
        cout << "Preparing complete" << endl;
    }
    int gameStatus = game.Loop();
    cout << "Game ended with status: " << gameStatus << endl;

    pthread_exit(0);
}

bool Server::Accept(){
    int newSocket = accept(this->serverSocket, (struct sockaddr *) &_serverStorage, &_addr_size);
    if (newSocket == -1) return false;
    cout << "New client connected!" << endl;


    /*char buffer[1024];
    int bytes_received = read(newSocket, buffer, 1024 - 1);
    if (bytes_received < 0) {
        cerr << "Receive failed" << endl;
        close(newSocket);
        return 1;
    }
    buffer[bytes_received] = '\0';  // Zakończenie stringa
    cout << "Received JSON: " << buffer << endl;

    try {
        json json_obj = json::parse(buffer);

        // Wypisywanie wartości z JSON-a
        cout << "Type: " << json_obj["typ"].get<string>() << endl;
        cout << "Content: " << json_obj["zawartość"].get<string>() << endl;
        cout << "Number: " << json_obj["liczba"].get<int>() << endl;
    } catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }

    close(newSocket);*/
    playerQueue.push(newSocket); 

    if (StartGame()){
        cout << "Starting a game!" << endl;
    }
    
    
    return true;
}

int Server::_takeFristConnected(){
    while (playerQueue.size() > 0){
        int socket = playerQueue.front();
        playerQueue.pop();
        if (!IsConnected(socket)){
            cout << "Client " << socket << " closed connection" << endl;
            close(socket);
            continue;
        }
        return socket;
    }

    return -1;
}

struct players p;
bool Server::StartGame(){
    cout << "Queue size: " << playerQueue.size() << endl;
    if (this->playerQueue.size() <= 1) 
        return false;
    int socket1 = this->_takeFristConnected();
    int socket2 = this->_takeFristConnected();
    cout << "Found: " << socket1 << " | " << socket2 << endl;

    if (socket1 == -1 && socket2 == -1){
        cout << "All clients connections are closed by them" << endl;
        return false;
    }

    if (socket1 == -1 || socket2 == -1){
        int activeSocket = socket1 == -1 ? socket2 : socket1;
        cout << "Only one player ("<< activeSocket <<") is connected, pushing him on the queue"<< endl;
        this->playerQueue.push(activeSocket);
        return false;
    }

    // both clients are connected, start a game
    p.player_1_socket = socket1;
    p.player_2_socket = socket2;
    pthread_t thread_id;

    if( pthread_create(&thread_id, NULL, _gameThread, (void*)&p)  != 0 ){
        cout << "Error while creating a game thread!"<< endl;
        playerQueue.push(p.player_1_socket);
        playerQueue.push(p.player_2_socket);
        return false;

    }    
    this->activeGameThreads.push_back(thread_id);
    return true;
}





