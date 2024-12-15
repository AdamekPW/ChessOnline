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
    SendConfirmation(player_1.socket);
    SendConfirmation(player_2.socket);
    if (RecvNick(player_1.socket, player_1.nick) <= 0){
        player_1.nick = genereteNick(player_1.socket);
    }
    if (RecvNick(player_2.socket, player_2.nick) <= 0){
        player_2.nick = genereteNick(player_2.socket);
    }

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


bool Game::SendCustomizedPackage(Player &player){
    dataPackage.amIWhite = player.isWhite;
    dataPackage.opponentNick = (player.socket == player_1.socket) ? player_2.nick : player_1.nick;
    if (!SendDataPackage(player.socket, dataPackage))
        return false;
    return true;
}


int Game::Loop(){
    cout << "Entering game loop!" << endl;
    Player loser;
    bool isDraw = false;
    while (true){
        dataPackage.type = "GameMove";
        Player movingPlayer = _getPlayer(dataPackage.isWhiteToMove);
        cout << "Waiting for player " << movingPlayer.nick << " to move" << endl;
        
        vector<int> moves; 
        int RecvMoveStatus = RecvMove(movingPlayer, moves);
        if (RecvMoveStatus == 0){
            cout << "Player "<< movingPlayer.nick << " disconnected (0)" << endl;
            loser = movingPlayer;
            break;
        } else if (RecvMoveStatus < 0){
            cout << "Receiving move error" << endl;
            continue;
        }
         
        if (board.CheckMove(moves[0], moves[1], moves[2], moves[3]) != 0){
            //move isn't correct, skip
            continue;
        }
        
        cout << "Move is possible to make"<< endl;
        board.MakeMove(moves);
        board.Print(true);

        if (board.IsPromotion(moves[2], moves[3])){
            cout << "Promotion time!" << endl;
            dataPackage.type = "Promotion";

            if (!IsConnected(movingPlayer.socket)){
                cout << "Player "<< movingPlayer.nick << " disconnected" << endl;
                loser = movingPlayer;
                break;
            }
            if (!SendCustomizedPackage(movingPlayer)){
                cout << "Sending promotion information failed, skipping" << endl;
                continue;
            }

            int figureId;
            int RecvPromotionStatus = RecvPromotion(movingPlayer.socket, figureId);
            if (RecvPromotionStatus == -1){
                cout << "Receiving promotion failed, skipping" << endl;
                continue;
            } else if (RecvPromotionStatus == 0){
                cout << "Player "<< movingPlayer.nick << " disconnected" << endl;
                loser = movingPlayer;
                break;
            }

            string color = movingPlayer.isWhite ? "White" : "Black";
            delete board.board[moves[2]][moves[3]];
            board.board[moves[2]][moves[3]] = Board::CreateFigure(figureId, color);
            board.Print(true);
        }

        dataPackage.type = "GameMove";
        dataPackage.isWhiteToMove = !dataPackage.isWhiteToMove;
        dataPackage.moveNumber++;

        if (!IsConnected(player_1.socket)){
            cout << "Player "<< player_1.nick << " disconnected (1)" << endl;
            loser = player_1;
            break;
        }
        if (!IsConnected(player_2.socket)){
            cout << "Player "<< player_2.nick << " disconnected (1)" << endl;
            loser = player_2;
            break;
        }
        if (!SendCustomizedPackage(player_1) || !SendCustomizedPackage(player_2)){
            cout << "Sending updated dataPackage failed, exiting" << endl;
            return -1;
        }
        
     
        if (RecvConfirmation(player_1.socket) == 0){
            cout << "Player "<< player_1.nick << " disconnected (didn't send move confirmation)" << endl;
            loser = player_1;
            break;
        }
        if (RecvConfirmation(player_2.socket) == 0){
            cout << "Player "<< player_2.nick << " disconnected (didn't send move confirmation)" << endl;
            loser = player_2;
            break;
        }

        if (board.IsMate(dataPackage.isWhiteToMove)){
            loser = player_1.isWhite == dataPackage.isWhiteToMove ? player_1 : player_2;
            break;
        }

        if (board.IsDraw(dataPackage.isWhiteToMove)){
            isDraw = true;
            dataPackage.winner = "none";
            break;
        } else {
            cout << "its not a draw"<<endl;
        }
    }

    if (!isDraw){
        Player winner = player_1.socket == loser.socket ? player_2 : player_1;
        dataPackage.winner = dataPackage.isWhiteToMove ? "Black" : "White";
        cout << "Winner: " << winner.nick << " (" << (winner.isWhite ? "White":"Black") <<")"<< endl;
        cout << "Loser: " << loser.nick << " (" << (loser.isWhite ? "White":"Black") <<")"<< endl;
    } else {
        cout << "Draw!" << endl;
    }

    dataPackage.type = "GameEnd";
    SendCustomizedPackage(player_1);
    SendCustomizedPackage(player_2);


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