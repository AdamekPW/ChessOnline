#include "common.hpp"


void DataPackage::Print(){
    cout << "Type: " << type << endl;    
    cout << "MyColor: " << (amIWhite ? "White" : "Black") << endl;
    cout << "Opponent nick: " << opponentNick << endl;
    cout << "Now moving: " << (isWhiteToMove ? "White" : "Black") << endl;   
    board.Print(amIWhite); 
}


// Funkcja wczytująca konfigurację z pliku JSON
ServerConfig loadConfig(const std::string& configPath) {
    ServerConfig config;

    // Otwieranie pliku JSON
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku konfiguracyjnego: " << configPath << std::endl;
        throw std::runtime_error("Błąd otwierania pliku konfiguracyjnego");
    }

    // Parsowanie pliku JSON
    json jsonConfig;
    configFile >> jsonConfig;

    // Pobieranie wartości IP i portu, z domyślnymi wartościami w razie braku klucza
    config.ip = jsonConfig.value("server_ip", "127.0.0.1");
    config.port = jsonConfig.value("server_port", 8080);

    return config;
}

void set_nonblocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}
void set_blocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1) {
        return;
    }
    flags &= ~O_NONBLOCK; 
    if (fcntl(socket, F_SETFL, flags) == -1) {
        perror("fcntl F_SETFL");
    }
}

bool SendConfirmation(int socket){
    char buff[20] = "PackageReceived";
    if (send(socket, buff, 20, 0) == -1){
        return false;
    }
    return true;
}

int RecvConfirmation(int socket){
    set_blocking(socket);
    char buff[20];
    if (recv(socket, buff, 20, 0) == -1)
        return -1;
    
    if (strcmp(buff, "PackageReceived") != 0)
        return 1;
    
    return 0;
}

void parseBoard(string &board_str, Board &board){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            delete board.board[i][j];
            board.board[i][j] = nullptr;
            int index = i*24 + j*3;
            char colorSymbol = board_str[index + 1];
            
            if (colorSymbol == 'N') 
                continue;
            int id = board_str[index] - '0';

            string color = colorSymbol == 'W' ? "White" : "Black";
            board.board[i][j] = board.CreateFigure(id, color);
        }
    }
}

bool RecvDataPackage(int socket, DataPackage &dataPackage, bool isBlocking){
    if (isBlocking)
        set_blocking(socket);
    else
        set_nonblocking(socket);

    char buffer[1024];
    bzero(buffer, sizeof(buffer));
    int n = recv(socket, buffer, sizeof(buffer), 0);
    if (n <= 0) {
        return false;
    }

    //printf("%s\n", buffer);

    string board_str;
    try {
        json json_obj = json::parse(buffer);
        dataPackage.type = json_obj["type"].get<string>();
        dataPackage.amIWhite = json_obj["myColor"].get<string>() == "White" ? true : false;
        dataPackage.opponentNick = json_obj["opponentNick"].get<string>();
        dataPackage.isWhiteToMove = json_obj["colorToMove"].get<string>() == "White" ? true : false;
        board_str = json_obj["board"].get<string>();

    } catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return false;
    }

    parseBoard(board_str, dataPackage.board);

    dataPackage.Print();
    return true;
    
}

bool SendDataPackage(int socket, DataPackage &dataPackage){
    stringstream ss;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            int id = 0;
            char colorSymbol = 'N';
            if (!dataPackage.board.IsEmpty(i, j)){
                id = dataPackage.board.board[i][j]->getId();
                colorSymbol = dataPackage.board.board[i][j]->isWhite() ? 'W' : 'B';
            }
            ss << id << colorSymbol;  
            if (j == 7) ss <<"\n";
            else ss << "|";
        }
    }

    json json_obj;
    json_obj["type"] = dataPackage.type;
    json_obj["myColor"] = dataPackage.amIWhite ? "White" : "Black";
    json_obj["opponentNick"] = dataPackage.opponentNick;
    json_obj["colorToMove"] = dataPackage.isWhiteToMove ? "White" : "Black";
    json_obj["number"] = dataPackage.moveNumber;
    json_obj["board"] = ss.str();

    string json_str = json_obj.dump();

    if (send(socket, json_str.c_str(), json_str.size(), 0) < 0) {
        cout << "Error while sending " << socket << endl;
        return false;
    }

    
    return true;
}