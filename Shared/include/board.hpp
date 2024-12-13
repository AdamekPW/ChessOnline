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
        //zamien na is...CastlePossible, waliduj po stronie serwera
        pair<int, int> _findKing(bool isWhite);
        void _updateFlags(pair<int, int> &active_figure);
        
    public:
        bool isLongWhiteCastlePossible = true;
        bool isShortWhiteCastlePossible = true;
        bool isLongBlackCastlePossible = true;
        bool isShortBlackCastlePossible = true;
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
        bool MakeMove(vector<int> &move);
        bool MakeMove(vector<pmove> &possible_moves, pair<int, int> &active_figure, pair<int, int> &move_cords);
        static Figure* CreateFigure(int id, string color);
        bool IsPromotion(int x, int y);
        int GetPromotingFigureId(int y);
        
        bool IsCheck(bool isWhiteKing);
        bool IsMate(bool isWhiteKing);
        bool IsDraw(bool isWhite);
        void Print(bool asWhite);
        



};








#endif