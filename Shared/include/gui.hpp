#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "figure.hpp"
#include <iostream>
using namespace std;
class GUI {
    private:
        int SQUARE_SIZE; 
        int TOP_OFFSET;
        bool asWhite;
        sf::Texture texture;
        sf::Sprite board_sprite;
        sf::Sprite white_king_sprite;
        sf::Sprite white_queen_sprite;
        sf::Sprite white_rook_sprite;
        sf::Sprite white_knight_sprite;
        sf::Sprite white_bishop_sprite;
        sf::Sprite white_pawn_sprite;
        sf::Sprite black_king_sprite;
        sf::Sprite black_queen_sprite;
        sf::Sprite black_rook_sprite;
        sf::Sprite black_knight_sprite;
        sf::Sprite black_bishop_sprite;
        sf::Sprite black_pawn_sprite;
        int _loadSprites();
    public:
        GUI(int SQUARE_SIZE, bool asWhite);
        sf::Sprite GetSprite(Figure *figure);
        void Draw(sf::RenderWindow &window, Board &board, vector<pmove> &possible_moves);
        void DrawPromotion(sf::RenderWindow &window, bool asWhite, int x);
        pair<int, int> ClickedFigure(sf::RenderWindow &window, Board &board, sf::Vector2i &mouse_position);
        
};

#endif