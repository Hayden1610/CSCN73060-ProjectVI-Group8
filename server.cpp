// Updated Server.cpp with human-readable time parsing and avg fuel calculation
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512

struct FlightData {
    double timestamp;  // seconds since epoch
    std::string readableTime; // human-readable
    double fuelRemaining;
};

struct AircraftRecord {
    int id;
    std::vector<FlightData> flightData;
    double totalFuelConsumed = 0.0;
    double totalFlightTime = 0.0;
    double avgFuelConsumption = 0.0;
    bool activeFlight = true;
};

std::vector<AircraftRecord> aircraftDatabase;
std::mutex dbMutex;

int findAircraft(int id) {
    for (int i = 0; i < aircraftDatabase.size(); i++) {
        if (aircraftDatabase[i].id == id)
            return i;
    }
    return -1;
}

void calculateFuelConsumption(int index) {
    auto& record = aircraftDatabase[index];
    if (record.flightData.size() < 2) return;

    std::sort(record.flightData.begin(), record.flightData.end(), [](const FlightData& a, const FlightData& b) {
        return a.timestamp < b.timestamp;
        });

    double initialFuel = record.flightData.front().fuelRemaining;
    double finalFuel = record.flightData.back().fuelRemaining;
    double initialTime = record.flightData.front().timestamp;
    double finalTime = record.flightData.back().timestamp;

    double fuelConsumed = initialFuel - finalFuel;
    double timeElapsed = finalTime - initialTime;

    if (timeElapsed > 0) {
        record.totalFuelConsumed = fuelConsumed;
        record.totalFlightTime = timeElapsed;
        record.avgFuelConsumption = fuelConsumed / timeElapsed;
    }
}

void saveFinalFlightData(int index) {
    const auto& record = aircraftDatabase[index];
    std::string fileName = "aircraft_" + std::to_string(record.id) + "_history.txt";
    std::ofstream out(fileName, std::ios::app);
    if (out.is_open()) {
        time_t now = time(0);
        char buffer[32];
        ctime_s(buffer, sizeof(buffer), &now);
        int minutes = static_cast<int>(record.totalFlightTime) / 60;
        int seconds = static_cast<int>(record.totalFlightTime) % 60;

        out << "Flight ended: " << buffer;
        out << "Total flight time: " << minutes << " minutes " << seconds << " seconds\n";
        out << "Total fuel consumed: " << record.totalFuelConsumed << " gallons\n";
        out << "Average fuel consumption: " << record.avgFuelConsumption << " gallons/sec\n";
        out << "-----------------------------\n";

        for (const auto& fd : record.flightData) {
            out << fd.readableTime << "," << fd.fuelRemaining << ",\n";
        }

        out.close();

        std::cout << "Flight Summary for aircraft " << record.id << ":\n";
        std::cout << "  Time: " << minutes << " minutes " << seconds << " seconds\n";
        std::cout << "  Fuel: " << record.totalFuelConsumed << " gal\n";
        std::cout << "  Avg:  " << record.avgFuelConsumption << " gal/s\n";
    }
}

void handleClient(SOCKET clientSocket) {
    char recvbuf[BUFFER_SIZE];
    std::string buffer;
    int recvResult;

    int aircraftId = -1;
    int dbIndex = -1;

    while ((recvResult = recv(clientSocket, recvbuf, BUFFER_SIZE - 1, 0)) > 0) {
        recvbuf[recvResult] = '\0';
        buffer += recvbuf;

        size_t pos;
        while ((pos = buffer.find('\n')) != std::string::npos) {
            std::string line = buffer.substr(0, pos);
            buffer.erase(0, pos + 1);

            std::istringstream ss(line);
            std::string idStr, timeStr, fuelStr;
            if (!getline(ss, idStr, ',') || !getline(ss, timeStr, ',') || !getline(ss, fuelStr)) continue;

            try {
                aircraftId = std::stoi(idStr);

                std::tm tm = {};
                std::istringstream ts(timeStr);
                ts >> std::get_time(&tm, "%m_%d_%Y %H:%M:%S");
                if (ts.fail()) continue;
                double timestamp = static_cast<double>(mktime(&tm));

                double fuel = std::stod(fuelStr);

                std::lock_guard<std::mutex> lock(dbMutex);
                dbIndex = findAircraft(aircraftId);
                if (dbIndex == -1) {
                    aircraftDatabase.push_back({ aircraftId });
                    dbIndex = aircraftDatabase.size() - 1;
                }

                FlightData fd;
                fd.timestamp = timestamp;
                fd.readableTime = timeStr;
                fd.fuelRemaining = fuel;
                aircraftDatabase[dbIndex].flightData.push_back(fd);
                calculateFuelConsumption(dbIndex);

                std::cout << "Aircraft ID: " << aircraftId
                    << ", Time: " << timeStr
                    << ", Fuel: " << fuel
                    << ", Avg: " << aircraftDatabase[dbIndex].avgFuelConsumption
                    << std::endl;
            }
            catch (...) {
                continue;
            }
        }
    }

    std::cout << "Flight ended for aircraft " << aircraftId << std::endl;
    std::lock_guard<std::mutex> lock(dbMutex);
    if (dbIndex != -1) {
        saveFinalFlightData(dbIndex);
        aircraftDatabase[dbIndex].flightData.clear();
    }

    closesocket(clientSocket);
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) return 1;

    const char* port = DEFAULT_PORT;
    if (argc > 1) port = argv[1];

    struct addrinfo hints = {}, * addr = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, port, &hints, &addr);
    if (result != 0) {
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }

    bind(listenSocket, addr->ai_addr, (int)addr->ai_addrlen);
    freeaddrinfo(addr);

    listen(listenSocket, SOMAXCONN);
    std::cout << "Server listening on port " << port << "..." << std::endl;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            std::thread t(handleClient, clientSocket);
            t.detach();
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
