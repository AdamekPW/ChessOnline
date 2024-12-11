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
                pair<int, int> &cords,
                bool &asWhite,
                bool &isWhiteToMove,
                bool &isPromotion,
                bool &END){

    cords = GUI.ClickedFigure(window, board, mouse_position);
    if (!asWhite){
        cords.first = 7 - cords.first;
        cords.second = 7 - cords.second;
    }
    
    cout << cords.first << " " << cords.second << endl;

    if (isPromotion){
        if (cords.first == 8 || cords.first == -1){
            cout << "promotion" << endl;
            if (cords.second < 2 || cords.second > 5) 
                return;
            int _y = asWhite ? cords.second : (7-cords.second);
            int figureId = board.GetPromotingFigureId(_y);
            cout << "New figure for: "<< figureId << endl;
            SendPromotion(client.Socket, figureId);

            isPromotion = false;
        }
        return;
    }

    if (cords.first < 0 || cords.first > 7) return;

    bool move_maked = false;
    if (active_figure.first != -1 && board.IsWhite(active_figure) == asWhite 
        && active_figure != cords && asWhite == isWhiteToMove){
        cout << active_figure.first << " " << active_figure.second << endl;
        client.SendMove(active_figure.first, active_figure.second, cords.first, cords.second);
        move_maked = true;
    }

    possible_moves.resize(0);
    

    //show possible moves
    int x = cords.first;
    int y = cords.second;
    
    if (!board.IsEmpty(x, y) && board.IsWhite(x, y) == asWhite){
        cout << "Calculating moves for " << x << " " << y << endl;
        possible_moves = board.board[x][y]->PossibleMoves(board, x, y);

        //adding possible castling moves
        board.addCastlingMoves(possible_moves, x, y);

        active_figure = make_pair(x, y);
        return;
    } 
    if (!move_maked){
        active_figure = make_pair(-1, -1);
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

    Board board;
    DataPackage dataPackage(board);
    RecvDataPackage(client.Socket, dataPackage, true);
    SendConfirmation(client.Socket);

    bool asWhite = dataPackage.amIWhite;
    bool END = false;


    //game loop
    sf::RenderWindow window(sf::VideoMode(SQUARE_SIZE/2*8, SQUARE_SIZE/2*10), "Chess");
    GUI GUI(SQUARE_SIZE, asWhite);
    

    sf::Sprite board_sprite;
    window.setFramerateLimit(60);    

    vector<pmove> possible_moves;
    pair<int, int> active_figure = make_pair(4, 4);
    pair<int, int> cords;
    bool isPromotion = false;

    while (window.isOpen())
    {
        RecvDataPackage(client.Socket, dataPackage, false);
        if (dataPackage.type == "Promotion"){
            isPromotion = true;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {    
            if (event.type == sf::Event::Closed){
                client.~Client();
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && !END){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

                    HandleEvent(mouse_position, board, client, window, 
                        GUI, possible_moves, active_figure, cords, asWhite, dataPackage.isWhiteToMove, isPromotion, END);

                }
            }
        }


        window.clear(sf::Color(145, 184, 154));
        
        GUI.Draw(window, board, possible_moves);
        if (isPromotion)
            GUI.DrawPromotion(window, asWhite, active_figure.second);
     
        window.display();

        if (END){
            cin.get();
        }
    }

  return 0;
}