#ifndef QUEEN_H
#define QUEEN_H
#include "figure.hpp"
#include "board.hpp"
class Queen : public Figure {
    public:
        Queen(string color);
        vector<pmove> PossibleMoves(Board &board, int x, int y) override;

};
#endif