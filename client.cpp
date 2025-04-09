// Client.cpp (Corrected Version for Raspberry Pi/Linux)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <thread>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int aircraftId = dis(gen);

    const char* serverAddress = "127.0.0.1";
    const char* port = DEFAULT_PORT;
    std::string telemetryFile = "Telem_2023_3_12 14_56_40.txt";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            serverAddress = argv[i + 1]; i++;
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = argv[i + 1]; i++;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            telemetryFile = argv[i + 1]; i++;
        } else if (strcmp(argv[i], "-id") == 0 && i + 1 < argc) {
            aircraftId = std::stoi(argv[i + 1]); i++;
        }
    }

    std::cout << "Client starting with Aircraft ID: " << aircraftId << std::endl;
    std::cout << "Connecting to server: " << serverAddress << ":" << port << std::endl;
    std::cout << "Using telemetry file: " << telemetryFile << std::endl;

    struct addrinfo hints;
    struct addrinfo* addr = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int result = getaddrinfo(serverAddress, port, &hints, &addr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(result) << std::endl;
        return 1;
    }

    int connectSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (connectSocket < 0) {
        std::cerr << "socket failed" << std::endl;
        freeaddrinfo(addr);
        return 1;
    }

    result = connect(connectSocket, addr->ai_addr, (int)addr->ai_addrlen);
    if (result < 0) {
        std::cerr << "connect failed" << std::endl;
        close(connectSocket);
        freeaddrinfo(addr);
        return 1;
    }
    freeaddrinfo(addr);

    std::ifstream file(telemetryFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open telemetry file: " << telemetryFile << std::endl;
        close(connectSocket);
        return 1;
    }

    std::string line, header;
    std::getline(file, header);

    int lineCount = 0;
    static double timeCounter = 0.0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestampStr, fuelStr;

        if (std::getline(ss, timestampStr, ',') && std::getline(ss, fuelStr, ',')) {
            std::string timeStr = std::to_string(timeCounter);
            timeCounter += 1.0;

            // Correct order: aircraftId, time, fuel
            std::string packet = std::to_string(aircraftId) + "," + timeStr + "," + fuelStr;
            result = send(connectSocket, packet.c_str(), (int)packet.length(), 0);

            if (result < 0) {
                std::cerr << "send failed" << std::endl;
                break;
            }

            std::cout << "Sent: " << packet << std::endl;
            lineCount++;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::string endPacket = std::to_string(aircraftId) + ",END";
    send(connectSocket, endPacket.c_str(), (int)endPacket.length(), 0);
    std::cout << "End of flight. Sent " << lineCount << " data points." << std::endl;

    file.close();
    close(connectSocket);
    return 0;
}