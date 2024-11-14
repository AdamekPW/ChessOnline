#include "common.hpp"


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