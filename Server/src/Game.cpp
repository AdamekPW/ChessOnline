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
    
    //send starting information to both players
    if (!this->SendStartInfo()){
        cout << "Error while sending starting information!" << endl;
        return;
    }
    RecvConfirmation(player_1_socket);
    RecvConfirmation(player_2_socket);
    
    //send board to both players
    if (!this->SendBoard()){
        cout << "Error while sending starting board! "<< endl;
        return;
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
    cout << "Entering game loop!" << endl;
    bool isWhiteToMove = true;
    while (true){
        Player movingPlayer = _getPlayer(isWhiteToMove);
        char buff[MESSAGE_LENGTH];
        bzero(buff, MESSAGE_LENGTH);

        cout << "Oczekiwanie na ruch gracza " << movingPlayer.socket << endl;
        int bytes = read(movingPlayer.socket, buff, MESSAGE_LENGTH);
        printf("Otrzymano: %s\n", buff);
        
        vector<int> moves;
        if (bytes != -1){
            moves = this->GetMove(buff);
            for (auto &move : moves){
                cout << move << " ";
            }
            cout << endl;
            //analize if move is correct
            if (board.CheckMove(moves[0], moves[1], moves[2], moves[3]) != 0){
                //move isn't correct send feedback
                
                continue;
            }
        }
        cout << "Move is possible to make"<< endl;
        //move is correct, do it
        vector<pmove> possible_moves = board.board[moves[0]][moves[1]]->PossibleMoves(board, moves[0], moves[1]);
        pair<int, int> active_figure = make_pair(moves[0], moves[1]);
        pair<int, int> move_cords = make_pair(moves[2], moves[3]);
        board.MakeMove(possible_moves, active_figure, move_cords),  
        
        SendBoard();
        
        isWhiteToMove = !isWhiteToMove;
    }


    return 0;
}


bool validateMove(vector<int>& moves){
    for (auto &move : moves){
        if (move < 0 || move > 7) 
            return false;
    }
    return true;
}

vector<int> Game::GetMove(char move[MESSAGE_LENGTH]){
    //move format: x_from|y_from|x_to|y_to
    vector<int> result;
    string move_string= string(move);
    stringstream ss(move_string);
    string token;

    while (getline(ss, token, '|')) {
        result.push_back(std::stoi(token));
    }
    
    return result;
}




bool Game::SendBoard(){
    stringstream ss;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            int id = 0;
            char colorSymbol = 'N';
            if (!board.IsEmpty(i, j)){
                id = board.board[i][j]->getId();
                colorSymbol = board.board[i][j]->isWhite() ? 'W' : 'B';
            }
            ss << id << colorSymbol;  
            if (j == 7) ss <<"\n";
            else ss << "|";
        }
    }
    string message = ss.str();
    if (send(player_1.socket, message.c_str(), message.size(), 0) < 0) {
        return false;
    }
    if (send(player_2.socket, message.c_str(), message.size(), 0) < 0) {
        return false;
    }

    return true;
}