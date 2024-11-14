#include "Server.hpp"


Server::Server(int port){
    this->_port = port;
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
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
    cout << "Obsluga gry dla: " << p.player_1_socket << " | " << p.player_2_socket << endl;

    Game game = Game(p.player_1_socket, p.player_2_socket);

    int gameStatus = game.Loop();
    cout << "Gra  zakonczona ze statusem: " << gameStatus << endl;

    pthread_exit(NULL);
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
        if (!this->IsConnected(socket)){
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
    cout << "Wielkosc kolejki: " << playerQueue.size() << endl;
    if (this->playerQueue.size() <= 1) 
        return false;
    int socket1 = this->_takeFristConnected();
    int socket2 = this->_takeFristConnected();
    cout << "Znaleziono: " << socket1 << " | " << socket2 << endl;

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



bool Server::IsConnected(int clientSocket){
    set_nonblocking(clientSocket);
    char buffer;
    int result = recv(clientSocket, &buffer, 1, MSG_PEEK);
    set_blocking(clientSocket);
    if (result == 0) {
        // Client closed a connection
        return false;
    } else if (result < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            // no data to read, but still connected
            return true;
        } else {
            // Error 
            std::cerr << "Error on recv: " << strerror(errno) << std::endl;
            return false;
        }
    }
    //Client is connected
    return true;
}

