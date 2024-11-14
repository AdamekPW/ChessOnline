#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <locale>
#include <codecvt>

#include <iostream>
#include <string>
#include <unistd.h>
#include "board.hpp"
#include "figure.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"
#include "custom_structs.hpp"
using namespace std;

class Board {
    private:
        pair<int, int> _findKing(bool isWhite);
        bool _didWhiteKingMove = false;
        bool _didBlackKingMove = false;
        bool _didWhiteLongRookMove = false; 
        bool _didWhiteShortRookMove = false;
        bool _didBlackLongRookMove = false; 
        bool _didBlackShortRookMove = false;
        void _updateFlags(pair<int, int> &active_figure);
        
    public:
        Figure* board[8][8] = {nullptr};
        Board();
        ~Board();
        void Clear();
        void Reset();
        bool isWhiteCastlingPossible(bool isLong);
        bool isBlackCastlingPossible(bool isLong);
        void addCastlingMoves(vector<pmove> &possible_moves, int x, int y);
        void Castle(bool isWhite, bool isLong);
        bool IsEmpty(int x, int y);
        bool IsWhite(int x, int y);
        bool IsWhite(pair<int, int> &active_figure);
        bool IsBlack(int x, int y);
        int CheckMove(int old_x, int old_y, int new_x, int new_y);
        bool MakeMove(vector<pmove> &possible_moves, pair<int, int> &active_figure, pair<int, int> &move_cords);
        Figure* CreateFigure(int id, string color);
        bool IsPromotion(int x, int y);
        void Promote(pair<int, int> active_figure, int y);
        bool IsCheck(bool isWhiteKing);
        bool IsMate(bool isWhiteKing);
        void Print(bool asWhite);
        



};








#endif