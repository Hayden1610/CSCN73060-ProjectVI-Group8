#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    int aircraftId = 1001;
    const char* serverAddress = "127.0.0.1";
    const char* port = DEFAULT_PORT;
    std::string telemetryFile;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-id") == 0 && i + 1 < argc) aircraftId = std::stoi(argv[++i]);
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) telemetryFile = argv[++i];
    }

    if (telemetryFile.empty()) {
        std::cerr << "Usage: Client.exe -id [AircraftID] -f [TelemetryFile]" << std::endl;
        return 1;
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct addrinfo hints = {}, * addr = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo(serverAddress, port, &hints, &addr);
    SOCKET sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(sock, addr->ai_addr, (int)addr->ai_addrlen);
    freeaddrinfo(addr);

    std::ifstream file(telemetryFile);
    std::string header, line;
    std::getline(file, header);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestampStr, fuelStr;
        if (std::getline(ss, timestampStr, ',') && std::getline(ss, fuelStr, ',')) {
            std::string packet = std::to_string(aircraftId) + "," + timestampStr + "," + fuelStr + "\n";
            send(sock, packet.c_str(), (int)packet.length(), 0);
            std::cout << "[SENT] " << packet;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::string endPacket = std::to_string(aircraftId) + ",END,\n";
    send(sock, endPacket.c_str(), (int)endPacket.length(), 0);

    closesocket(sock);
    WSACleanup();
    return 0;
}
