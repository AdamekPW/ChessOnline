#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string>
#include <vector>
#include "custom_structs.hpp"

using namespace std;

class Board;

class Figure {
    protected:
        bool _isWhite;
        float _value;
        int _id;
        string _symbol;
        int x, y;
        void _setColor(string color);

    public:
        bool isWhite();
        float getValue();
        int getId();
        string getSymbol();
        virtual vector<pmove> PossibleMoves(Board &board, int x, int y) = 0;
        bool checkLimits(int x, int y);
        void Move(Board &board, int x, int y);



};

#endif