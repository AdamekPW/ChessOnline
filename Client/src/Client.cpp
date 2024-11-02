#include "Client.hpp"

Client::Client(string serverAddress, int serverPort){
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_port = htons(serverPort);
    char* modifiableCstr = new char[serverAddress.size() + 1]; // +1 dla znaku '\0'
    std::strcpy(modifiableCstr, serverAddress.c_str());
    this->_serverAddr.sin_addr.s_addr = inet_addr(modifiableCstr);

    this->Socket = socket(AF_INET, SOCK_STREAM, 0);
    
    cout << "Client created!" << endl;
}


Client::~Client(){
    close(this->Socket);
}   



bool Client::Connect(){
    this->_addr_size = sizeof(this->_serverAddr);
    if (connect(this->Socket, (struct sockaddr *) &_serverAddr, this->_addr_size) == -1){
        printf("Cannot connect to the server!\n");
        close(this->Socket);
        return false;
    }
    return true;
}

bool Client::SendJson(json json_obj){

}