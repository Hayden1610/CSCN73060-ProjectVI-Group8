#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <queue>
#include <condition_variable>
#include <ctime>
#include <iomanip>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512
#define THREAD_POOL_SIZE 8

std::mutex coutMutex, dbMutex;


struct FlightData {
    double timestamp;
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


void safePrint(const std::string& msg) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << msg << std::endl;
}


std::queue<SOCKET> socketQueue;
std::condition_variable socketAvailable;
std::mutex queueMutex;

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
        out << "Flight ended: " << buffer;

        int min = static_cast<int>(record.totalFlightTime / 60);
        int sec = static_cast<int>(record.totalFlightTime) % 60;

        out << "Total flight time: " << min << " min " << sec << " sec\n";
        out << "Total fuel consumed: " << record.totalFuelConsumed << " gallons\n";
        out << "Average fuel consumption: " << record.avgFuelConsumption << " gallons/sec\n";
        out << "-----------------------------\n";

        for (const auto& entry : record.flightData) {
            time_t t = static_cast<time_t>(entry.timestamp);
            std::tm tm;
            localtime_s(&tm, &t);
            char timeStr[32];
            strftime(timeStr, sizeof(timeStr), "%m_%d_%Y %H:%M:%S", &tm);
            out << timeStr << "," << entry.fuelRemaining << ",\n";
        }


        out.close();
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
                aircraftDatabase[dbIndex].flightData.push_back({ timestamp, fuel });
                calculateFuelConsumption(dbIndex);

                std::ostringstream msg;
                msg << "Aircraft ID: " << aircraftId
                    << ", Time: " << timeStr
                    << ", Fuel: " << fuel
                    << ", Avg: " << aircraftDatabase[dbIndex].avgFuelConsumption;
                safePrint(msg.str());
            }
            catch (...) {
                continue;
            }
        }
    }

    std::lock_guard<std::mutex> lock(dbMutex);
    if (dbIndex != -1) {
        saveFinalFlightData(dbIndex);
        aircraftDatabase[dbIndex].flightData.clear();
    }

    closesocket(clientSocket);
}


void workerThread() {
    while (true) {
        SOCKET clientSocket;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            socketAvailable.wait(lock, [] { return !socketQueue.empty(); });
            clientSocket = socketQueue.front();
            socketQueue.pop();
        }
        handleClient(clientSocket);
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    addrinfo hints = {}, * addr = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, DEFAULT_PORT, &hints, &addr);
    SOCKET listenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(listenSocket, addr->ai_addr, (int)addr->ai_addrlen);
    listen(listenSocket, SOMAXCONN);
    freeaddrinfo(addr);

    safePrint("Server listening on port 27015...");

    
    for (int i = 0; i < THREAD_POOL_SIZE; ++i)
        std::thread(workerThread).detach();

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                socketQueue.push(clientSocket);
            }
            socketAvailable.notify_one();
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
