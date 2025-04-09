// Server.cpp
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <ctime>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "27015"
#define BUFFER_SIZE 512

struct FlightData {
    double timestamp;
    double fuelRemaining;
};

struct AircraftRecord {
    int id;
    std::vector<FlightData> flightData;
    double totalFuelConsumed;
    double totalFlightTime;
    double avgFuelConsumption;
    bool activeFlight;
};

// Global variables
std::vector<AircraftRecord> aircraftDatabase;
std::mutex databaseMutex;

// Function to find aircraft in database by ID
int findAircraft(int id) {
    for (int i = 0; i < aircraftDatabase.size(); i++) {
        if (aircraftDatabase[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Function to calculate fuel consumption
void calculateFuelConsumption(int index) {
    if (aircraftDatabase[index].flightData.size() < 2) {
        return;
    }

    double initialFuel = aircraftDatabase[index].flightData[0].fuelRemaining;
    double finalFuel = aircraftDatabase[index].flightData.back().fuelRemaining;
    double fuelConsumed = initialFuel - finalFuel;

    double initialTime = aircraftDatabase[index].flightData[0].timestamp;
    double finalTime = aircraftDatabase[index].flightData.back().timestamp;
    double timeElapsed = finalTime - initialTime;

    if (timeElapsed > 0) {
        aircraftDatabase[index].totalFuelConsumed += fuelConsumed;
        aircraftDatabase[index].totalFlightTime += timeElapsed;
        aircraftDatabase[index].avgFuelConsumption = 
            aircraftDatabase[index].totalFuelConsumed / aircraftDatabase[index].totalFlightTime;
    }
}

// Function to save flight data
void saveFinalFlightData(int index) {
    std::string filename = "aircraft_" + std::to_string(aircraftDatabase[index].id) + "_history.txt";
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        time_t now = time(0);
        std::string dt = ctime(&now);
        dt.pop_back(); // Remove newline

        file << "Flight ended: " << dt << std::endl;
        file << "Total flight time: " << aircraftDatabase[index].totalFlightTime << " seconds" << std::endl;
        file << "Total fuel consumed: " << aircraftDatabase[index].totalFuelConsumed << " gallons" << std::endl;
        file << "Average fuel consumption: " << aircraftDatabase[index].avgFuelConsumption << " gallons/second" << std::endl;
        file << "--------------------------------" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open file for aircraft " << aircraftDatabase[index].id << std::endl;
    }
}

// Function to handle client connection
void handleClient(SOCKET clientSocket) {
    char recvbuf[BUFFER_SIZE];
    int recvResult;
    int aircraftId = -1;
    int dbIndex = -1;

    // Receive data from client
    while (true) {
        ZeroMemory(recvbuf, BUFFER_SIZE);
        recvResult = recv(clientSocket, recvbuf, BUFFER_SIZE, 0);
        
        if (recvResult > 0) {
            std::string data(recvbuf);
            std::istringstream ss(data);
            std::string token;
            
            // Parse aircraft ID
            if (getline(ss, token, ',')) {
                aircraftId = std::stoi(token);
                
                // Find or create aircraft record
                databaseMutex.lock();
                dbIndex = findAircraft(aircraftId);
                if (dbIndex == -1) {
                    AircraftRecord newAircraft;
                    newAircraft.id = aircraftId;
                    newAircraft.totalFuelConsumed = 0.0;
                    newAircraft.totalFlightTime = 0.0;
                    newAircraft.avgFuelConsumption = 0.0;
                    newAircraft.activeFlight = true;
                    aircraftDatabase.push_back(newAircraft);
                    dbIndex = aircraftDatabase.size() - 1;
                    std::cout << "New aircraft connected: ID " << aircraftId << std::endl;
                }
                databaseMutex.unlock();
                
                // Check if this is the end of flight marker
                if (getline(ss, token, ',') && token == "END") {
                    databaseMutex.lock();
                    aircraftDatabase[dbIndex].activeFlight = false;
                    calculateFuelConsumption(dbIndex);
                    saveFinalFlightData(dbIndex);
                    aircraftDatabase[dbIndex].flightData.clear(); // Clear flight data for next flight
                    databaseMutex.unlock();
                    std::cout << "Flight ended for aircraft ID " << aircraftId << std::endl;
                    continue;
                }
                
                // Parse timestamp and fuel remaining
                double timestamp = 0.0;
                double fuelRemaining = 0.0;
                
                if (getline(ss, token, ',')) {
                    timestamp = std::stod(token);
                    
                    if (getline(ss, token, ',')) {
                        fuelRemaining = std::stod(token);
                        
                        // Store flight data
                        databaseMutex.lock();
                        FlightData flightData;
                        flightData.timestamp = timestamp;
                        flightData.fuelRemaining = fuelRemaining;
                        aircraftDatabase[dbIndex].flightData.push_back(flightData);
                        
                        // Calculate current fuel consumption
                        calculateFuelConsumption(dbIndex);
                        
                        std::cout << "Aircraft ID: " << aircraftId 
                                  << ", Time: " << timestamp 
                                  << ", Fuel: " << fuelRemaining 
                                  << ", Avg Consumption: " << aircraftDatabase[dbIndex].avgFuelConsumption 
                                  << " gallons/second" << std::endl;
                        databaseMutex.unlock();
                    }
                }
            }
        }
        else if (recvResult == 0) {
            // Connection closing
            std::cout << "Connection closing for aircraft ID " << aircraftId << std::endl;
            
            // Mark flight as ended if it was active
            if (dbIndex != -1) {
                databaseMutex.lock();
                if (aircraftDatabase[dbIndex].activeFlight) {
                    aircraftDatabase[dbIndex].activeFlight = false;
                    calculateFuelConsumption(dbIndex);
                    saveFinalFlightData(dbIndex);
                    aircraftDatabase[dbIndex].flightData.clear();
                }
                databaseMutex.unlock();
            }
            break;
        }
        else {
            // recv failed
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // Close socket
    closesocket(clientSocket);
}

int main(int argc, char* argv[]) {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Determine port to listen on
    const char* port = DEFAULT_PORT;
    if (argc > 1) {
        port = argv[1];
    }
    
    // Create socket
    struct addrinfo hints;
    struct addrinfo* addr = NULL;
    
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    
    result = getaddrinfo(NULL, port, &hints, &addr);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << result << std::endl;
        WSACleanup();
        return 1;
    }
    
    SOCKET listenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addr);
        WSACleanup();
        return 1;
    }
    
    // Bind to address
    result = bind(listenSocket, addr->ai_addr, (int)addr->ai_addrlen);
    if (result == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addr);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    freeaddrinfo(addr);
    
    // Listen for connections
    result = listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Server is listening on port " << port << "..." << std::endl;
    
    // Accept connections and start threads to handle clients
    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        
        // Create a new thread to handle this client
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach(); // Let the thread run independently
    }
    
    // Cleanup
    closesocket(listenSocket);
    WSACleanup();
    
    return 0;
}
