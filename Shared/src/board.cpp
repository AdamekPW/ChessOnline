#include "board.hpp"
using namespace std;



Board::Board(){
    this->Reset();
    //cout << this->isWhiteCastlingPossible(true) << endl;

}
Board::~Board(){
    this->Clear();
}

void Board::Clear(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            delete this->board[i][j];
            board[i][j] = nullptr;
        }
    }
}

void Board::Reset(){
    this->Clear();
    this->board[0][4] = new King("White");
    this->board[0][0] = new Rook("White");
    this->board[0][7] = new Rook("White");
    this->board[6][1] = new Pawn("White");
    this->board[6][2] = new Pawn("White");
    this->board[7][4] = new King("Black");
    this->board[7][0] = new Rook("Black");
    this->board[7][7] = new Rook("Black");
    // this->board[6][6] = new Pawn("White");
    // this->board[6][7] = new Pawn("White");
    // this->board[6][0] = new Pawn("White");
    // this->board[6][1] = new Pawn("White");
    // this->board[1][6] = new Pawn("Black");
    // this->board[1][7] = new Pawn("Black");
    // this->board[1][0] = new Pawn("Black");
    // this->board[1][1] = new Pawn("Black");
    // this->board[0][0] = new Rook("White");
    // this->board[0][1] = new Knight("White");
    // this->board[0][2] = new Bishop("White");
    // this->board[0][3] = new Queen("White");
    // this->board[0][4] = new King("White");
    // this->board[0][5] = new Bishop("White");
    // this->board[0][6] = new Knight("White");
    // this->board[0][7] = new Rook("White");
    // for (int i = 0; i < 8; i++){
    //     this->board[1][i] = new Pawn("White");
    // }

    // this->board[7][0] = new Rook("Black");
    // this->board[7][1] = new Knight("Black");
    // this->board[7][2] = new Bishop("Black");
    // this->board[7][3] = new Queen("Black");
    // this->board[7][4] = new King("Black");
    // this->board[7][5] = new Bishop("Black");
    // this->board[7][6] = new Knight("Black");
    // this->board[7][7] = new Rook("Black");
    // for (int i = 0; i < 8; i++){
    //     this->board[6][i] = new Pawn("Black");
    // }


}

void Board::_updateFlags(pair<int, int> &active_figure){
    int id = this->board[active_figure.first][active_figure.second]->getId();
    
    if (id != 2 && id != 6)
        return;

    switch (active_figure.first*10 + active_figure.second)
    {
    case 0:
        this->isLongWhiteCastlePossible = false;
        break;
    case 7:
        this->isShortWhiteCastlePossible = false;
        break;
    case 70:
        this->isLongBlackCastlePossible = false;
        break;
    case 77:
        this->isShortBlackCastlePossible = false;
        break;
    case 4:
        this->isLongWhiteCastlePossible = false;
        this->isShortWhiteCastlePossible = false;
        break;
    case 74:
        this->isLongBlackCastlePossible = false;
        this->isShortBlackCastlePossible = false;
        break;
    
    }

    
  
}

bool Board::isWhiteCastlingPossible(bool isLong){
    //there are no checks
    if (this->IsCheck(true)) return false;

    if (isLong){
        //long castling
        if (!this->isLongWhiteCastlePossible) 
            return false;

        //there is nothing between them
        if (!this->IsEmpty(0, 1) || !this->IsEmpty(0, 2) || !this->IsEmpty(0, 3))
            return false;

        //fields between are safe
        Figure* tempKing = this->board[0][4];
        this->board[0][4] = nullptr;
        for (int i = 1; i <= 3; i++){
            this->board[0][i] = tempKing;
            if (this->IsCheck(true)){
                this->board[0][i] = nullptr;
                this->board[0][4] = tempKing;
                tempKing = nullptr;
                return false;
            }
            this->board[0][i] = nullptr;
        }
        this->board[0][4] = tempKing;
        tempKing = nullptr;


    } else {
        //short castling
        if (!this->isShortWhiteCastlePossible) 
            return false;

        //there is nothing between them
        if (!this->IsEmpty(0, 5) || !this->IsEmpty(0, 6))
            return false;

        //fields between are safe
        Figure* tempKing = this->board[0][4];
        this->board[0][4] = nullptr;
        for (int i = 5; i <= 6; i++){
            this->board[0][i] = tempKing;
            if (this->IsCheck(true)){
                this->board[0][i] = nullptr;
                this->board[0][4] = tempKing;
                tempKing = nullptr;
                return false;
            }
            this->board[0][i] = nullptr;
        }
        this->board[0][4] = tempKing;
        tempKing = nullptr;

    }
    return true;
}

bool Board::isBlackCastlingPossible(bool isLong){
    //there are no checks
    if (this->IsCheck(false)) return false;

    if (isLong){
        //long castling
        //rook didn't move
        if (!this->isLongBlackCastlePossible) 
            return false;

        //there is nothing between them
        if (!this->IsEmpty(7, 1) || !this->IsEmpty(7, 2) || !this->IsEmpty(7, 3))
            return false;

        //fields between are safe
        Figure* tempKing = this->board[7][4];
        this->board[7][4] = nullptr;
        for (int i = 1; i <= 3; i++){
            this->board[7][i] = tempKing;
            if (this->IsCheck(false)){
                this->board[7][i] = nullptr;
                this->board[7][4] = tempKing;
                tempKing = nullptr;
                return false;
            }
            this->board[7][i] = nullptr;
        }
        this->board[7][4] = tempKing;
        tempKing = nullptr;


    } else {
        //short castling
        //rook didn't move
        if (!this->isShortBlackCastlePossible) 
            return false;

        //there is nothing between them
        if (!this->IsEmpty(7, 5) || !this->IsEmpty(7, 6))
            return false;

        //fields between are safe
        Figure* tempKing = this->board[7][4];
        this->board[7][4] = nullptr;
        for (int i = 5; i <= 6; i++){
            this->board[7][i] = tempKing;
            if (this->IsCheck(false)){
                this->board[7][i] = nullptr;
                this->board[7][4] = tempKing;
                tempKing = nullptr;
                return false;
            }
            this->board[7][i] = nullptr;
        }
        this->board[7][4] = tempKing;
        tempKing = nullptr;

    }
    return true;
}

void Board::addCastlingMoves(vector<pmove> &possible_moves, int x, int y){
    if (this->IsEmpty(x, y))
        return;

    if (this->board[x][y]->getId() != 6)
        return;


    if (this->IsWhite(x, y)){
        if (this->isWhiteCastlingPossible(true))
            possible_moves.push_back({0, 2, 2});

        if (this->isWhiteCastlingPossible(false))
            possible_moves.push_back({0, 6, 3});
        
    } else {
        if (this->isBlackCastlingPossible(true))
            possible_moves.push_back({7, 2, 2});

        if (this->isBlackCastlingPossible(false))
            possible_moves.push_back({7, 6, 3});
    }               
    
}

void Board::Castle(bool isWhite, bool isLong){
    if (isWhite){
        this->isLongWhiteCastlePossible = false;
        this->isShortWhiteCastlePossible = false;
        if (isLong){
            this->board[0][2] = this->board[0][4]; //move king
            this->board[0][4] = nullptr;
            this->board[0][3] = this->board[0][0]; //move rook
            this->board[0][0] = nullptr;
        } else {
            this->board[0][6] = this->board[0][4]; //move king
            this->board[0][4] = nullptr;
            this->board[0][5] = this->board[0][7]; //move rook
            this->board[0][7] = nullptr;
        }
    } else {
        this->isLongBlackCastlePossible = false;
        this->isShortBlackCastlePossible = false;
        if (isLong){
            this->board[7][2] = this->board[7][4]; //move king
            this->board[7][4] = nullptr;
            this->board[7][3] = this->board[7][0]; //move rook
            this->board[7][0] = nullptr;
        } else {
            this->board[7][6] = this->board[7][4]; //move king
            this->board[7][4] = nullptr;
            this->board[7][5] = this->board[7][7]; //move rook
            this->board[7][7] = nullptr;
        }

    }

}

bool Board::IsEmpty(int x, int y){
    if (this->board[x][y] == nullptr) 
        return true;
    return false;
}

bool Board::IsWhite(int x, int y){
    //cout << "AF: " << x << " " << y << endl;
    if (this->IsEmpty(x, y)) 
        return false;

    if (!this->board[x][y]->isWhite())
        return false;
   
    return true;
}

bool Board::IsWhite(pair<int, int> &active_figure){
    int x = active_figure.first;
    int y = active_figure.second;
    return this->IsWhite(x, y);
}

bool Board::IsBlack(int x, int y){
    if (!this->IsEmpty(x, y) && !this->board[x][y]->isWhite()){
        return true;
    }
    return false;
}


int Board::CheckMove(int old_x, int old_y, int new_x, int new_y){
    if (this->IsEmpty(old_x, old_y)){
        return -1;
    }
    vector<pmove> possible_moves = this->board[old_x][old_y]->PossibleMoves(*this, old_x, old_y);
    this->addCastlingMoves(possible_moves, old_x, old_y);
    bool my_color = this->board[old_x][old_y] -> isWhite();
 
    for (auto &move : possible_moves){
        if (move.x == new_x && move.y == new_y){
            //save position before moving
            Figure *temp_new = this->board[new_x][new_y];
            Figure *temp_old = this->board[old_x][old_y];
            //make a move
            this->board[new_x][new_y] = this->board[old_x][old_y];
            this->board[old_x][old_y] = nullptr;
   
            //check if this move will expose your king
            if (this->IsCheck(my_color)){
                //this move exposes your king, it can't be made, undo
                this->board[new_x][new_y] = temp_new;
                this->board[old_x][old_y] = temp_old;
                return 1;
            }

            this->board[new_x][new_y] = temp_new;
            this->board[old_x][old_y] = temp_old;

            return 0;

        }
    }
    return 2;
}


bool Board::MakeMove(vector<int> &moves){
    vector<pmove> possible_moves = board[moves[0]][moves[1]]->PossibleMoves(*this, moves[0], moves[1]);
    addCastlingMoves(possible_moves, moves[0], moves[1]);
    pair<int, int> active_figure = make_pair(moves[0], moves[1]);
    pair<int, int> move_cords = make_pair(moves[2], moves[3]);

    return MakeMove(possible_moves, active_figure, move_cords);  
}
bool Board::MakeMove(vector<pmove> &possible_moves, pair<int, int> &active_figure, pair<int, int> &move_cords){
    if (possible_moves.size() == 0 || active_figure.first == -1) 
        return false;
    

    //check if move cords are in possible_moves
    bool found = false;
    int type=-1;
    for (auto &move : possible_moves){
        if (move.x == move_cords.first && move.y == move_cords.second){
            found = true;
            type = move.type;
            break;
        }
    }
    if (!found) 
        return false;

     
    //move has been found and it's castling (so global possibilites are already checked)
    
    if (type == 2){
        this->Castle(this->IsWhite(active_figure), true);
        active_figure.first = move_cords.first;
        active_figure.second = move_cords.second;
        return true;
    }
    if (type == 3){
        this->Castle(this->IsWhite(active_figure), false);
        active_figure.first = move_cords.first;
        active_figure.second = move_cords.second;
        return true;
    }

    //move has been found, now check global possibility to make 
    int is_possible = this->CheckMove(active_figure.first, active_figure.second, move_cords.first, move_cords.second);
    if (is_possible != 0)
        return false;


    //move is possible to make, make it
    if (this->board[move_cords.first][move_cords.second] != nullptr)
        delete board[move_cords.first][move_cords.second];

    //if rook or king is moving, change flags
    this->_updateFlags(active_figure);

    board[move_cords.first][move_cords.second] = board[active_figure.first][active_figure.second];
    board[active_figure.first][active_figure.second] = nullptr;

    active_figure.first = move_cords.first;
    active_figure.second = move_cords.second;
    return true;
    

}

pair<int, int> Board::_findKing(bool isWhite){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (this->board[i][j] != nullptr 
                && this->board[i][j]->isWhite() == isWhite
                && this->board[i][j]->getId() == 6)
                {
                    return make_pair(i, j);
                }
        }
    }
    return make_pair(-1, -1);
}

bool Board::IsPromotion(int x, int y){
    //it's not a pawn
    if (this->board[x][y] -> getId() != 1) return false;
    
    //it's white pawn on rank 7
    if (this->IsWhite(x, y) && x == 7)
        return true;
    
    //it's black pawn on rank 6
    if (this->IsBlack(x, y) && x == 0)
        return true;

    return false;
}


Figure* Board::CreateFigure(int id, string color){
    Figure * new_figure;
    switch (id){
        case 1:
            new_figure = new Pawn(color);
            break;
        case 2:
            new_figure = new Rook(color);
            break;
        case 3:
            new_figure = new Knight(color);
            break;
        case 4:
            new_figure = new Bishop(color);
            break;
        case 5:
            new_figure = new Queen(color);
            break;
        case 6:
            new_figure = new King(color);
            break;
        default:
            cout << "Error while creating new_figure" << endl;
            new_figure = nullptr;
    }
    return new_figure;
}

void Board::Promote(pair<int, int> active_figure, int y){
    string color = this->IsWhite(active_figure.first, active_figure.second) ? "White" : "Black";
    int term = 0;
    if (color == "White"){
        int corretion = active_figure.second > 4 ? 4 : active_figure.second;
        term = y - corretion;
    } else {
        int corretion = active_figure.second < 3 ? 3 : active_figure.second;
        term = y - corretion;
    }
    term = term < 0 ? -term : term;
    cout << term << endl;
    Figure* new_figure = nullptr;
    switch (term){
        case 0:
            new_figure = new Rook(color);
            break;
        case 1:
            new_figure = new Knight(color);
            break;
        case 2:
            new_figure = new Bishop(color);
            break;
        case 3:
            new_figure = new Queen(color);
            break;
        default:
            cout << "Error while creating new_figure" << endl;
            return;
    }
    
    delete this->board[active_figure.first][active_figure.second];
    this->board[active_figure.first][active_figure.second] = new_figure;
}

bool Board::IsCheck(bool isWhiteKing){
    pair<int, int> king_cords = this->_findKing(isWhiteKing);
    int king_x = king_cords.first;
    int king_y = king_cords.second;
    
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (this->board[i][j] != nullptr 
                && this->board[i][j]->isWhite() != isWhiteKing)
                {
                    vector<pmove> possible_moves = this->board[i][j]->PossibleMoves(*this, i, j);
                    for (auto &move : possible_moves){
                        if (move.type == 1 && move.x == king_x && move.y == king_y)
                            return true;
                    }

                }
        }
    }
    return false;

}


bool Board::IsMate(bool isWhiteKing){
    if (!this->IsCheck(isWhiteKing)) return false;
    
    pair<int, int> king_cords = this->_findKing(isWhiteKing);
    int king_x = king_cords.first;
    int king_y = king_cords.second;
    vector<pmove> possible_king_moves = this->board[king_x][king_y]->PossibleMoves(*this, king_x, king_y);
    //for each move, check whether it is possible to make
    for (auto &move : possible_king_moves){
        if (this->CheckMove(king_x, king_y, move.x, move.y) == 0)
            return false;
    }

    return true;
}

void Board::Print(bool asWhite){
    cout << "---------------" << endl;
    if (asWhite){
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                if (this->board[i][j] != nullptr)
                    cout << this->board[i][j]->getSymbol() << " ";
                else
                    cout << "  ";
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 7; j >= 0; j--) {
                if (this->board[i][j] != nullptr)
                    cout << this->board[i][j]->getSymbol() << " ";
                else
                    cout << "  ";
            }
            cout << endl;
        }
    }
}
