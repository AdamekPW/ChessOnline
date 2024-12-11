#include "gui.hpp"



GUI::GUI(int SQUARE_SIZE, bool asWhite){
    this->SQUARE_SIZE = SQUARE_SIZE;
    this->TOP_OFFSET = SQUARE_SIZE/2;
    this->_loadSprites();
    this->asWhite = asWhite;
}


int GUI::_loadSprites(){
  
    if (!this->texture.loadFromFile("pieces.png"))
    {
        return -1;
    }
    this->board_sprite = sf::Sprite(texture);
    this->board_sprite.setScale(0.5f, 0.5f);
    this->board_sprite.setTextureRect(sf::IntRect(0, 5, SQUARE_SIZE*8, SQUARE_SIZE*8)); 
    this->board_sprite.setPosition(0, this->TOP_OFFSET);

    this->black_bishop_sprite = sf::Sprite(texture);
    this->black_bishop_sprite.setScale(0.5f, 0.5f);
    this->black_bishop_sprite.setTextureRect(sf::IntRect(2, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_bishop_sprite.setPosition(0*SQUARE_SIZE/2, 0);

    this->black_king_sprite = sf::Sprite(texture);
    this->black_king_sprite.setScale(0.5f, 0.5f);
    this->black_king_sprite.setTextureRect(sf::IntRect(SQUARE_SIZE, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_king_sprite.setPosition(1*SQUARE_SIZE/2, 0);

    this->black_knight_sprite = sf::Sprite(texture);
    this->black_knight_sprite.setScale(0.5f, 0.5f);
    this->black_knight_sprite.setTextureRect(sf::IntRect(2*SQUARE_SIZE+3, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_knight_sprite.setPosition(2*SQUARE_SIZE/2, 0);

    this->black_pawn_sprite = sf::Sprite(texture);
    this->black_pawn_sprite.setScale(0.5f, 0.5f);
    this->black_pawn_sprite.setTextureRect(sf::IntRect(3*SQUARE_SIZE+2, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_pawn_sprite.setPosition(3*SQUARE_SIZE/2, 0);

    this->black_queen_sprite = sf::Sprite(texture);
    this->black_queen_sprite.setScale(0.5f, 0.5f);
    this->black_queen_sprite.setTextureRect(sf::IntRect(4*SQUARE_SIZE+3, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_queen_sprite.setPosition(4*SQUARE_SIZE/2, 0);

    this->black_rook_sprite = sf::Sprite(texture);
    this->black_rook_sprite.setScale(0.5f, 0.5f);
    this->black_rook_sprite.setTextureRect(sf::IntRect(5*SQUARE_SIZE+4, 10+SQUARE_SIZE*8, SQUARE_SIZE, SQUARE_SIZE)); 
    this->black_rook_sprite.setPosition(5*SQUARE_SIZE/2, 0);




    this->white_bishop_sprite = sf::Sprite(texture);
    this->white_bishop_sprite.setScale(0.5f, 0.5f);
    this->white_bishop_sprite.setTextureRect(sf::IntRect(1, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_bishop_sprite.setPosition(0*SQUARE_SIZE/2, SQUARE_SIZE/2);

    this->white_king_sprite = sf::Sprite(texture);
    this->white_king_sprite.setScale(0.5f, 0.5f);
    this->white_king_sprite.setTextureRect(sf::IntRect(SQUARE_SIZE, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_king_sprite.setPosition(1*SQUARE_SIZE/2, SQUARE_SIZE/2);

    this->white_knight_sprite = sf::Sprite(texture);
    this->white_knight_sprite.setScale(0.5f, 0.5f);
    this->white_knight_sprite.setTextureRect(sf::IntRect(2*SQUARE_SIZE+1, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_knight_sprite.setPosition(2*SQUARE_SIZE/2, SQUARE_SIZE/2);

    this->white_pawn_sprite = sf::Sprite(texture);
    this->white_pawn_sprite.setScale(0.5f, 0.5f);
    this->white_pawn_sprite.setTextureRect(sf::IntRect(3*SQUARE_SIZE+2, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_pawn_sprite.setPosition(3*SQUARE_SIZE/2, SQUARE_SIZE/2);

    this->white_queen_sprite = sf::Sprite(texture);
    this->white_queen_sprite.setScale(0.5f, 0.5f);
    this->white_queen_sprite.setTextureRect(sf::IntRect(4*SQUARE_SIZE+3, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_queen_sprite.setPosition(4*SQUARE_SIZE/2, SQUARE_SIZE/2);

    this->white_rook_sprite = sf::Sprite(texture);
    this->white_rook_sprite.setScale(0.5f, 0.5f);
    this->white_rook_sprite.setTextureRect(sf::IntRect(5*SQUARE_SIZE, 15+SQUARE_SIZE*9, SQUARE_SIZE, SQUARE_SIZE)); 
    this->white_rook_sprite.setPosition(5*SQUARE_SIZE/2, SQUARE_SIZE/2);


    return 0;
}

sf::Sprite GUI::GetSprite(Figure *figure){
    if (figure->isWhite()){
        switch (figure->getId()){
            case 1:
                return this->white_pawn_sprite;
            case 2:
                return this->white_rook_sprite;
            case 3:
                return this->white_knight_sprite;
            case 4:
                return this->white_bishop_sprite;
            case 5:
                return this->white_queen_sprite;
            case 6:
                return this->white_king_sprite;
            default:
                break;
        }
    } else {
        switch (figure->getId()){
            case 1:
                return this->black_pawn_sprite;
            case 2:
                return this->black_rook_sprite;
            case 3:
                return this->black_knight_sprite;
            case 4:
                return this->black_bishop_sprite;
            case 5:
                return this->black_queen_sprite;
            case 6:
                return this->black_king_sprite;
            default:
                break;
        }
    }
    return this->black_king_sprite;
}

void GUI::Draw(sf::RenderWindow &window, Board &board, vector<pmove> &possible_moves){
    window.draw(this->board_sprite);

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            int x_cord = this->asWhite ? (7-i) : (i);
            int y_cord = this->asWhite ? (j) : (7 - j);
            if (!board.IsEmpty(i, j)){
                
                sf::Sprite sprite = this->GetSprite(board.board[i][j]);
                sprite.setPosition((y_cord)*this->SQUARE_SIZE/2, this->TOP_OFFSET+(x_cord)*this->SQUARE_SIZE/2);
                window.draw(sprite);
            }
        }
    }
    

    float Radius = 20;
    sf::CircleShape circle(Radius);
    circle.setFillColor(sf::Color(128, 128, 128, 150));  
    sf::RectangleShape rectangle(sf::Vector2f(75.0f, 75.0f));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-4.0f);

    for (auto& move : possible_moves){
        int x_cord = this->asWhite ? (7 - move.x) : (move.x);
        int y_cord = this->asWhite ? (move.y) : (7 - move.y);
        if (move.type == 0){
            float x = this->TOP_OFFSET+(x_cord) * 75 + 75/2 + 2 - Radius;
            float y = (y_cord) * 75 + 75/2 + 2 - Radius;
            circle.setPosition(y, x);
            window.draw(circle); 
        } else if (move.type == 1){
            float x = this->TOP_OFFSET+(x_cord) * 75;
            float y = (y_cord) * 75+1;
            rectangle.setPosition(y, x);
            rectangle.setOutlineColor(sf::Color(255, 20, 20));
            window.draw(rectangle);
        } else {
            float x = this->TOP_OFFSET+(x_cord) * 75;
            float y = (y_cord) * 75+1;
            rectangle.setPosition(y, x);
            rectangle.setOutlineColor(sf::Color(20, 200, 20));
            window.draw(rectangle);
        }
        
    }

}

void GUI::DrawPromotion(sf::RenderWindow &window, bool asWhite, int y){
    y = 2;
    if (asWhite){
        //if (y > 4) y = 4;
        this->white_rook_sprite.setPosition((y)*SQUARE_SIZE/2, 0);
        this->white_knight_sprite.setPosition((y+1)*SQUARE_SIZE/2, 0);
        this->white_bishop_sprite.setPosition((y+2)*SQUARE_SIZE/2, 0);
        this->white_queen_sprite.setPosition((y+3)*SQUARE_SIZE/2, 0);
        window.draw(this->white_rook_sprite);
        window.draw(this->white_knight_sprite);
        window.draw(this->white_bishop_sprite);
        window.draw(this->white_queen_sprite);
    } else {
        //if (y < 3) y = 3;
        this->black_rook_sprite.setPosition((y)*SQUARE_SIZE/2, 0);
        this->black_knight_sprite.setPosition((y+1)*SQUARE_SIZE/2, 0);
        this->black_bishop_sprite.setPosition((y+2)*SQUARE_SIZE/2, 0);
        this->black_queen_sprite.setPosition((y+3)*SQUARE_SIZE/2, 0);
        window.draw(this->black_rook_sprite);
        window.draw(this->black_knight_sprite);
        window.draw(this->black_bishop_sprite);
        window.draw(this->black_queen_sprite);
    }
}

pair<int, int> GUI::ClickedFigure(sf::RenderWindow &window, Board &board, sf::Vector2i &mouse_position){
    int x = (int)(mouse_position.x / 75);
    int y = 8-(mouse_position.y) / 75;
    return make_pair(y, x);

}