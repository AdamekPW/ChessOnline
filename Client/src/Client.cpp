#include "Client.hpp"

Client::Client(string serverAddress, int serverPort){
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_port = htons(serverPort);

    this->_serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());

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

bool Client::SendMove(int x_from, int y_from, int x_to, int y_to){
    stringstream ss;
    ss << x_from << "|" << y_from << "|" << x_to << "|" << y_to; 
    string message = ss.str();
    if (send(this->Socket, message.c_str(), 20, 0) == -1){
        cout << "Error while sending a move!" << endl;
        return false;
    }

    return true;
}

bool Client::SendJson(json json_obj){

}


bool Client::GetBoard(Board &board){

    char buffer[1024];
    int bytes_received = recv(Socket, buffer, 1024 - 1, 0);
    if (bytes_received < 0) {
        return false;
    }

    cout << buffer;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            delete board.board[i][j];
            board.board[i][j] = nullptr;
            int index = i*24 + j*3;
            char colorSymbol = buffer[index + 1];
            
            if (colorSymbol == 'N') 
                continue;
            int id = buffer[index] - '0';

            string color = colorSymbol == 'W' ? "White" : "Black";
            board.board[i][j] = board.CreateFigure(id, color);
        }
    }

    return true;
}