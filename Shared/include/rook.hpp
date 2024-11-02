#ifndef ROOK_H
#define ROOK_H
#include "figure.hpp"
#include "board.hpp"

class Rook : public Figure {
    public:
        Rook(string color);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;
};


#endif