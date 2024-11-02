#include "figure.hpp"
#include "board.hpp"
using namespace std;


void Figure::_setColor(string color){
    if (color == "White")
        this->_isWhite = true;
    else
        this->_isWhite = false;

}

float Figure::getValue(){
    return this->_value;
}

int Figure::getId(){
    return this->_id;
}

bool Figure::isWhite(){
    return this->_isWhite;
}

string Figure::getSymbol(){
    return this->_symbol;
}

bool Figure::checkLimits(int x, int y){
    return (x >= 0 && x <= 7) && (y >= 0 && y <= 7);
}

void Figure::Move(Board &board, int new_x, int new_y){
    if (!board.IsEmpty(new_x, new_y))
        delete board.board[new_x][new_y];
        
    board.board[new_x][new_y] = board.board[this->x][this->y];
    board.board[this->x][this->y] = nullptr;
    this->x = new_x;
    this->y = new_y;
}