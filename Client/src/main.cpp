#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <pthread.h>
#include <signal.h>
#include "Client.hpp"
#include "common.hpp"
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include "board.hpp"
#include "custom_structs.hpp"

#define SQUARE_SIZE 150

using json = nlohmann::json;


void handle_sigint(int sig){
    std::cout << "\nClosing program..." << std::endl;
    exit(0); 
}


void HandleEvent(sf::Vector2i &mouse_position, 
                Board &board, 
                Client &client,
                sf::RenderWindow &window,
                GUI &GUI,
                vector<pmove> &possible_moves,
                pair<int, int> &active_figure, 
                bool &asWhite,
                bool &is_white_to_move,
                bool &is_promotion,
                bool &END){

    pair<int, int> cords = GUI.ClickedFigure(window, board, mouse_position);
    if (!asWhite){
        cords.first = 7 - cords.first;
        cords.second = 7 - cords.second;
    }
    //cout << cords.first << " " << cords.second << endl;
    if (is_promotion){
        if (cords.first == 8 || cords.first == -1){
            cout << "promotion" << endl;
            board.Promote(active_figure, cords.second);
            is_promotion = false;
        }
        return;
    }
    if (cords.first < 0 || cords.first > 7) return;

    
    bool move_maked = false;
    if (active_figure.first != -1 && board.IsWhite(active_figure) == asWhite){
        cout << active_figure.first << " " << active_figure.second << endl;
        //move_maked = board.MakeMove(possible_moves, active_figure, cords);
        if (!client.SendMove(active_figure.first, active_figure.second, cords.first, cords.second)){
            cout << "Error while sending move" << endl;
        }
    }
    possible_moves.resize(0);
    if (!move_maked){
        //show possible moves
        int x = cords.first;
        int y = cords.second;
        
        if (!board.IsEmpty(x, y) && board.IsWhite(x, y) == asWhite){
            cout << "Calculating moves for " << x << " " << y << endl;
            possible_moves = board.board[x][y]->PossibleMoves(board, x, y);
            //adding possible castling moves
            board.addCastlingMoves(possible_moves, x, y);

            active_figure = make_pair(x, y);
        } else {
            active_figure = make_pair(-1, -1);
            
        }
    } else {
        //check for promotions
        if (board.IsPromotion(active_figure.first, active_figure.second)){
            is_promotion = true;
        }

        is_white_to_move = !is_white_to_move;
        //check for mate
        if (board.IsMate(is_white_to_move)){
            END=true;
            if (is_white_to_move){
                cout << "Black wins!" << endl;
            } else {
                cout << "White wins!" << endl;
            }
        }
    }
}   

int main(){
    signal(SIGINT, handle_sigint);
    ServerConfig config;
    try {
        config = loadConfig("../Shared/config.json");
    } catch (const std::exception& e) {
        cout << "Error while opening config.json file: " << e.what() << std::endl;
        return 1;
    }

    Client client = Client(config.ip, config.port);
    if (!client.Connect())
        return EXIT_FAILURE;
    
    cout << "Połączono z serwerem." << endl;


    set_blocking(client.Socket);

    char buffer[1024];
    int bytes_received = recv(client.Socket, buffer, 1024 - 1, 0);
    if (bytes_received < 0) {
        cerr << "Receive failed" << endl;
        close(client.Socket);
        return 1;
    }
    buffer[bytes_received] = '\0';  
    cout << "Received JSON: " << buffer << endl;

    SendConfirmation(client.Socket);
    bool asWhite = true;

    try {
        json json_obj = json::parse(buffer);
        cout << "Type: " << json_obj["type"].get<string>() << endl;
        cout << "Color: " << json_obj["color"].get<string>() << endl;
        cout << "Opponent_nick: " << json_obj["opponent_nick"].get<string>() << endl;
        asWhite = json_obj["color"].get<string>() == "White" ? true : false;
    } catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    //game loop
    sf::RenderWindow window(sf::VideoMode(SQUARE_SIZE/2*8, SQUARE_SIZE/2*10), "Chess");
    GUI GUI(SQUARE_SIZE, asWhite);
    Board board;
    bool END = false;
    bool is_promotion = false;
    sf::Sprite board_sprite;
    window.setFramerateLimit(60);    

    vector<pmove> possible_moves;
    pair<int, int> active_figure = make_pair(4, 4);
    bool is_white_to_move = false;

    while (window.isOpen())
    {
        set_nonblocking(client.Socket);
        if (client.GetBoard(board)){
            is_white_to_move = !is_white_to_move;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {    
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && !END){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                    HandleEvent(mouse_position, board, client, window, 
                        GUI, possible_moves, active_figure, asWhite, is_white_to_move, is_promotion, END);

                }
            }
        }


        window.clear(sf::Color(145, 184, 154));
        
        GUI.Draw(window, board, possible_moves);
        if (is_promotion)
            GUI.DrawPromotion(window, !is_white_to_move, active_figure.second);

     
        window.display();

        if (END){
            cin.get();
        }
    }

  return 0;
}