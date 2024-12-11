#include "Game.hpp"


string genereteNick(int socket){
    stringstream ss;
    ss << "Gracz_" << socket;
    return ss.str(); 
}

Game::Game(int player_1_socket, int player_2_socket): board(),                // Inicjalizacja Board
      dataPackage(board){
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
    
}


Game::~Game(){
    close(this->player_1.socket);
    close(this->player_2.socket);
}

bool Game::Prepare(){
    //prepare dataPackage
    dataPackage.moveNumber = 0;
    dataPackage.type = "GameStart";
    dataPackage.board = this->board;
    dataPackage.isWhiteToMove = true;

    //send starting information to both players
    if (!SendStartInfo()){
        cout << "Error while sending starting informations" << endl;
        return false;
    }

    RecvConfirmation(player_1.socket);
    RecvConfirmation(player_2.socket);
    
    return true;
}

bool Game::SendStartInfo(){
    dataPackage.opponentNick = player_2.nick;
    dataPackage.amIWhite = player_1.isWhite;
    if (!SendDataPackage(player_1.socket, dataPackage)) 
        return false;
    

    dataPackage.opponentNick = player_1.nick;
    dataPackage.amIWhite = player_2.isWhite;
    if (!SendDataPackage(player_2.socket, dataPackage))
        return false;
    
    return true;
}



Player Game::_getPlayer(bool isWhite){
    return player_1.isWhite == isWhite ? player_1 : player_2;
}

int Game::RecvMove(Player movingPlayer, vector<int> &moves){
    char buff[MESSAGE_LENGTH];
    bzero(buff, MESSAGE_LENGTH);
    int bytes = recv(movingPlayer.socket, buff, sizeof(buff), 0);
    //analize if move is correct
    if (bytes > 0){
        moves = this->GetMove(buff);
        for (auto &move : moves){
            cout << move << " ";
        }
    }
    cout << endl;
    return bytes;
}

int Game::Loop(){
    cout << "Entering game loop!" << endl;

    dataPackage.type = "GameMove";
    dataPackage.opponentNick = "";
    dataPackage.amIWhite = false;

    int status = 0;
    while (status == 0){
        Player movingPlayer = _getPlayer(dataPackage.isWhiteToMove);
        

        cout << "Oczekiwanie na ruch gracza " << movingPlayer.socket << endl;
        vector<int> moves;
        int n = RecvMove(movingPlayer, moves);
        if (n == 0){
            cout << "Player disconnected" << endl;
            status = 1;
            break;
        } else if (n < 0){
            cout << "Receiving move error" << endl;
            continue;
        }
         
        if (board.CheckMove(moves[0], moves[1], moves[2], moves[3]) != 0){
            //move isn't correct send feedback
            continue;
        }
        
        cout << "Move is possible to make"<< endl;
        board.MakeMove(moves);

        
        dataPackage.isWhiteToMove = !dataPackage.isWhiteToMove;
        dataPackage.moveNumber++;
        if(!SendDataPackage(player_1.socket, dataPackage)
        || !SendDataPackage(player_2.socket, dataPackage)){
            cout << "Sending data package error" << endl;
            return -1;
        }

        board.Print(true);
        if (board.IsMate(dataPackage.isWhiteToMove)){
            if (dataPackage.isWhiteToMove){
                cout << "Black wins!" << endl;
                status = 1;
            } else {
                cout << "White wins!" << endl;
                status = 1;
            }
        }
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




// bool Game::SendBoard(){
//     stringstream ss;
//     for (int i = 0; i < 8; i++){
//         for (int j = 0; j < 8; j++){
//             int id = 0;
//             char colorSymbol = 'N';
//             if (!board.IsEmpty(i, j)){
//                 id = board.board[i][j]->getId();
//                 colorSymbol = board.board[i][j]->isWhite() ? 'W' : 'B';
//             }
//             ss << id << colorSymbol;  
//             if (j == 7) ss <<"\n";
//             else ss << "|";
//         }
//     }
//     string message = ss.str();
//     if (send(player_1.socket, message.c_str(), message.size(), 0) < 0) {
//         return false;
//     }
//     if (send(player_2.socket, message.c_str(), message.size(), 0) < 0) {
//         return false;
//     }

//     return true;
// }