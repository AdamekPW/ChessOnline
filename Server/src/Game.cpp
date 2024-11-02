#include "Game.hpp"


string genereteNick(int socket){
    stringstream ss;
    ss << "Gracz_" << socket;
    return ss.str(); 
}

Game::Game(int player_1_socket, int player_2_socket){
    this->player_1.socket = player_1_socket;
    this->player_2.socket = player_2_socket;

    this->player_1.nick = genereteNick(player_1_socket);
    this->player_2.nick = genereteNick(player_2_socket);

    random_device rd;   
    mt19937 gen(rd());   
    bernoulli_distribution dis(0.5);
    if (dis(gen) == 0){
        this->player_1.isWhite = true;
        this->player_2.isWhite = false;
    } else {
        this->player_1.isWhite = false;
        this->player_2.isWhite = true;
    }
    
    if (this->SendStartInfo()){
        cout << "Sending success!" << endl;
    }


}
Game::~Game(){
    close(this->player_1.socket);
    close(this->player_2.socket);
}

bool Game::SendStartInfo(){
    json json_obj;
    json_obj["type"] = "StartingGame";
    json_obj["color"] = player_1.isWhite ? "White" : "Black";
    json_obj["opponent_nick"] = player_2.nick;
    string json_str = json_obj.dump();

    if (send(player_1.socket, json_str.c_str(), json_str.size(), 0) < 0) {
        cout << "Error while sending StartingGame to " << player_1.socket << endl;
        return false;
    }

    json_obj["type"] = "StartingGame";
    json_obj["color"] = player_2.isWhite ? "White" : "Black";
    json_obj["opponent_nick"] = player_1.nick;
    json_str = json_obj.dump();

    if (send(player_2.socket, json_str.c_str(), json_str.size(), 0) < 0) {
        cout << "Error while sending StartingGame to " << player_2.socket << endl;
        return false;
    }
    
    return true;
}



Player Game::_getPlayer(bool isWhite){
    return player_1.isWhite == isWhite ? player_1 : player_2;
}

int Game::Loop(){
    bool isWhiteToMove = true;
    while (true){
        Player movingPlayer = _getPlayer(isWhiteToMove);
        char buff[20];
        bzero(buff, 20);
        cout << "Oczekiwanie na ruch gracza " << movingPlayer.socket << endl;
        int bytes = read(movingPlayer.socket, buff, 20);
        printf("Otrzymano: %s\n", buff);
        isWhiteToMove = !isWhiteToMove;
    }


    return 0;
}