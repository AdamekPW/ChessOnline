#ifndef KING_H
#define KING_H
#include "figure.hpp"
#include "board.hpp"
class King : public Figure {
    public:
        King(string color);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;
};


#endif