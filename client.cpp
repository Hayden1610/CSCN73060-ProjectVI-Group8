// ---------------- Client.cpp ----------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <thread>
#include <chrono>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int aircraftId = dis(gen);

    const char* serverAddress = "127.0.0.1";
    const char* port = DEFAULT_PORT;
    std::string telemetryFile = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) serverAddress = argv[++i];
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) port = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) telemetryFile = argv[++i];
        else if (strcmp(argv[i], "-id") == 0 && i + 1 < argc) aircraftId = std::stoi(argv[++i]);
    }

    if (telemetryFile.empty()) {
        std::cerr << "Telemetry file not specified!" << std::endl;
        return 1;
    }

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct addrinfo hints = {}, * addr = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(serverAddress, port, &hints, &addr) != 0) {
        std::cerr << "getaddrinfo failed" << std::endl;
        return 1;
    }

    SOCKET sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (connect(sock, addr->ai_addr, (int)addr->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "connect failed" << std::endl;
        freeaddrinfo(addr);
        return 1;
    }
    freeaddrinfo(addr);

    std::ifstream file(telemetryFile);
    std::string header, line;
    std::getline(file, header); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestampStr, fuelStr;
        if (std::getline(ss, timestampStr, ',') && std::getline(ss, fuelStr, ',')) {
            std::string packet = std::to_string(aircraftId) + "," + timestampStr + "," + fuelStr + "\n";
            send(sock, packet.c_str(), (int)packet.size(), 0);
            std::cout << "[SENT] " << packet;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    std::string endPacket = std::to_string(aircraftId) + ",END\n";
    send(sock, endPacket.c_str(), (int)endPacket.size(), 0);

    closesocket(sock);
    WSACleanup();
    return 0;
}
