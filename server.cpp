#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 27015
#define BUFFER_SIZE 1024

struct FlightData {
    double timestamp;
    double fuelRemaining;
};

struct AircraftRecord {
    std::vector<FlightData> flightData;
    double totalFuelConsumed = 0.0;
    double totalFlightTime = 0.0;
    double avgFuelConsumption = 0.0;
    bool active = true;
};

std::map<SOCKET, int> socketToAircraftId;
std::map<int, AircraftRecord> aircraftDatabase;

void calculateFuelConsumption(AircraftRecord& record) {
    if (record.flightData.size() < 2) return;
    std::sort(record.flightData.begin(), record.flightData.end(),
        [](const FlightData& a, const FlightData& b) {
            return a.timestamp < b.timestamp;
        });
    double deltaFuel = record.flightData.front().fuelRemaining - record.flightData.back().fuelRemaining;
    double deltaTime = record.flightData.back().timestamp - record.flightData.front().timestamp;
    if (deltaTime > 0) {
        record.totalFuelConsumed = deltaFuel;
        record.totalFlightTime = deltaTime;
        record.avgFuelConsumption = deltaFuel / deltaTime;
    }
}

void saveFlightSummary(int aircraftId, const AircraftRecord& record) {
    std::string fileName = "aircraft_" + std::to_string(aircraftId) + "_history.txt";
    std::ofstream out(fileName, std::ios::app);
    if (!out.is_open()) return;

    time_t now = time(0);
    char timeStr[32];
    ctime_s(timeStr, sizeof(timeStr), &now);
    double minutes = record.totalFlightTime / 60.0;

    out << "Flight ended: " << timeStr;
    out << "Total flight time: " << minutes << " minutes\n";
    out << "Total fuel consumed: " << record.totalFuelConsumed << " gallons\n";
    out << "Average fuel consumption: " << record.avgFuelConsumption << " gallons/sec\n";
    out << "-----------------------------\n";
    for (const auto& data : record.flightData) {
        out << " , " << data.timestamp << "," << data.fuelRemaining << ", \n";
    }
    out << "\n";
    out.close();

    std::cout << "[Result Saved] Aircraft " << aircraftId << " | "
        << minutes << " min | Fuel: " << record.totalFuelConsumed
        << " | Avg: " << record.avgFuelConsumption << "\n";
}

void handleClientPacket(SOCKET clientSocket, const std::string& line) {
    std::istringstream ss(line);
    std::string idStr, timeStr, fuelStr;
    if (!getline(ss, idStr, ',') || !getline(ss, timeStr, ',') || !getline(ss, fuelStr)) return;

    int id = std::stoi(idStr);
    if (timeStr == "END") {
        calculateFuelConsumption(aircraftDatabase[id]);
        saveFlightSummary(id, aircraftDatabase[id]);
        aircraftDatabase[id].flightData.clear();
        aircraftDatabase[id].active = false;
        std::cout << "[Flight Ended] ID: " << id << std::endl;
        return;
    }

    std::tm tm = {};
    int month, day, year, hour, minute, second;
    if (sscanf(timeStr.c_str(), "%d_%d_%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second) == 6) {
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
    }
    else return;

    double timestamp = static_cast<double>(mktime(&tm));
    double fuel = std::stod(fuelStr);

    if (aircraftDatabase.find(id) == aircraftDatabase.end()) {
        aircraftDatabase[id] = {};
        socketToAircraftId[clientSocket] = id;
    }

    aircraftDatabase[id].flightData.push_back({ timestamp, fuel });
    calculateFuelConsumption(aircraftDatabase[id]);

    std::cout << "ID: " << id << ", Time: " << timeStr << ", Fuel: " << fuel
        << ", Avg: " << aircraftDatabase[id].avgFuelConsumption << std::endl;
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSocket, SOMAXCONN);
    std::cout << "Server listening on port " << PORT << "...\n";

    fd_set masterSet, readSet;
    FD_ZERO(&masterSet);
    FD_SET(listenSocket, &masterSet);

    char buffer[BUFFER_SIZE];

    while (true) {
        readSet = masterSet;
        int socketCount = select(0, &readSet, nullptr, nullptr, nullptr);

        for (int i = 0; i < socketCount; ++i) {
            SOCKET sock = readSet.fd_array[i];

            if (sock == listenSocket) {
                SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
                FD_SET(clientSocket, &masterSet);
            }
            else {
                int bytesReceived = recv(sock, buffer, BUFFER_SIZE - 1, 0);
                if (bytesReceived <= 0) {
                    int id = socketToAircraftId[sock];
                    closesocket(sock);
                    FD_CLR(sock, &masterSet);
                    socketToAircraftId.erase(sock);
                    if (aircraftDatabase[id].active) {
                        calculateFuelConsumption(aircraftDatabase[id]);
                        saveFlightSummary(id, aircraftDatabase[id]);
                        aircraftDatabase[id].flightData.clear();
                        aircraftDatabase[id].active = false;
                    }
                }
                else {
                    buffer[bytesReceived] = '\0';
                    std::istringstream lines(buffer);
                    std::string line;
                    while (std::getline(lines, line)) {
                        handleClientPacket(sock, line);
                    }
                }
            }
        }

        // Graceful cleanup if only the listenSocket remains
        if (masterSet.fd_count == 1) {
            std::cout << "[Server] No active clients. Cleaning up...\n";
            for (auto it = aircraftDatabase.begin(); it != aircraftDatabase.end(); ++it) {
                int id = it->first;
                AircraftRecord& record = it->second;
                if (record.active) {
                    calculateFuelConsumption(record);
                    saveFlightSummary(id, record);
                }
            }
            aircraftDatabase.clear();
            socketToAircraftId.clear();
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
