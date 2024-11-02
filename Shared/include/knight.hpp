#ifndef KNIGHT_H
#define KNIGHT_H
#include "figure.hpp"
#include "board.hpp"

class Knight : public Figure {
    public:
        Knight(string color);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;
};


#endif