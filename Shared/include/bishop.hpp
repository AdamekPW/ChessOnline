#ifndef BISHOP_H
#define BISHOP_H
#include "figure.hpp"
#include "board.hpp"

class Bishop : public Figure {
    public:
        Bishop(string color);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;
};


#endif