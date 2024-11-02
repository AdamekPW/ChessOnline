#ifndef PAWN_H
#define PAWN_H

#include "figure.hpp"
#include "board.hpp"
class Pawn : public Figure {
    public:
        Pawn(string color, int x, int y);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;
} ;









#endif 