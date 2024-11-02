#include "king.hpp"
King::King(string color){
    this->_value = 0.0f;
    this->_id = 6;
    this->_setColor(color);
    if (this->_isWhite)
        this->_symbol = "♚";
    else
        this->_symbol = "♔";
}

vector<pmove>King::PossibleMoves(Board &board, int x, int y){
    vector<pmove> Result;
    bool am_i_white = board.IsWhite(x, y);
    struct side {
        int dir_x;
        int dir_y;
    };

    vector<side> sides = {
        {1, 0}, //up
        {-1, 0}, //down
        {0, 1}, //right
        {0, -1}, //left
        {1, -1}, //up-left
        {1, 1}, //up-right
        {-1, 1}, //down-right
        {-1, -1} //down-left
    };
    for (auto &side : sides){
        int new_x = x + side.dir_x;
        int new_y = y + side.dir_y;
        if (!this->checkLimits(new_x, new_y))
            continue;
        
        //simple move
        if (board.IsEmpty(new_x, new_y))
            Result.push_back({new_x, new_y, 0});
        //takes
        else if (am_i_white != board.IsWhite(new_x, new_y))
            Result.push_back({new_x, new_y, 1});
    }

    return Result;
}
