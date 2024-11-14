#include "pawn.hpp"


Pawn::Pawn(string color){
    this->_value = 1.0f;
    this->_id = 1;
    this->_setColor(color);
    if (this->_isWhite)
        this->_symbol = "♟";
    else
        this->_symbol = "♙";
}

vector<pmove> Pawn::PossibleMoves(Board &board, int x, int y){
    vector<pmove> Result;
    if (board.IsEmpty(x, y)) 
        return Result;
    if (board.board[x][y]->isWhite()){
        //move by 2
        if (x == 1 && board.IsEmpty(x+1, y) && board.IsEmpty(x+2, y)){
            Result.push_back({x+2, y, 0});
        }
        //move by one
        if (x < 7 && board.IsEmpty(x+1, y)){
            Result.push_back({x+1, y, 0});
        }
        //takes left
        if (x < 7 && y >= 1 && board.IsBlack(x+1, y-1)){
            Result.push_back({x+1, y-1, 1});
        }
        //takes right
        if (x < 7 && y <= 6 && board.IsBlack(x+1, y+1)){
            Result.push_back({x+1, y+1, 1});
        }

    } else {
        //move by 2
        if (x == 6 && board.IsEmpty(x-1, y) && board.IsEmpty(x-2, y)){
            Result.push_back({x-2, y, 0});
        }
        //move by one
        if (x > 0 && board.IsEmpty(x-1, y)){
            Result.push_back({x-1, y, 0});
        }
        //takes right
        if (x > 0 && y >= 1 && board.IsWhite(x-1, y-1)){
            Result.push_back({x-1, y-1, 1});
        }
        //takes left
        if (x > 0 && y <= 6 && board.IsWhite(x-1, y+1)){
            Result.push_back({x-1, y+1, 1});
        }
    }


    return Result;
}


