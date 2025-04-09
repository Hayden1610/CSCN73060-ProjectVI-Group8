C...
c...
Idle



Direct Message

Sinbad
AKA
Sin
Search

chat
8 December 2024

Sinbad — 08/12/2024 9:35 PM
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
10 KB
[9:36 PM]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
10 KB

C... — 08/12/2024 9:38 PM
MAIN MENU
Login
Create new user
Exit
Choose an option: 2

CREATE NEW USER
Enter username: Adil
Enter password: Adilfarid1389

Server response: Username and password cannot be empty

MAIN MENU
Login
Create new user
Exit
Choose an option:

Sinbad — 08/12/2024 9:39 PM
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB
[9:39 PM]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
11 KB

C... — 08/12/2024 9:40 PM
sinbad@Sinbad:~/sinbad/Assignment3$ g++ Server.cpp -o server
./sinbad@Sinbad:~/sinbad/Assignment3$ ./server
Error: Bind failed
sinbad@Sinbad:~/sinbad/Assignment3$
[9:43 PM]
sinbad@Sinbad:~/sinbad/Assignment3$ sudo lsof -i :8080
[sudo] password for sinbad: 
COMMAND  PID   USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
server  3304 sinbad    3u  IPv4  52497      0t0  TCP *:http-alt (LISTEN)
[9:46 PM]
sinbad@Sinbad:~/sinbad/Assignment3$ ./server
Loaded user: admin
Server listening on port 8080
Attempting to create user: ''
Create user failed: empty username or password
Attempting to create user: ''
Create user failed: empty username or password



this is server whil I am trying yo create the account
[9:46 PM]
sinbad@Sinbad:~/sinbad/Assignment3$ ./client

MAIN MENU
Login
Create new user
Exit
Choose an option: 2

CREATE NEW USER
Enter username: Sinbad
Enter password: Adilfarid1389

Server response: Username or password cannot be empty

MAIN MENU
Login
Create new user
Exit
Choose an option: 



and this is the client

Sinbad — 08/12/2024 9:48 PM
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB
[9:48 PM]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
13 KB

C... — 08/12/2024 9:50 PM
d@Sinbad:~/sinbad/Assignment3$ g++ Server.cpp -o server
Server.cpp: In member function ‘void DiscussionServer::setupSocket()’:
Server.cpp:305:35: error: ‘inet_addr’ was not declared in this scope; did you mean ‘in_addr’?
  305 |         address.sin_addr.s_addr = inet_addr("172.16.5.12");  // Specific IP
      |                                   ^~~~~
      |                                   in_addr
sinbad@Sinbad:~/sinbad/Assignment3$ ./serv

Sinbad — 08/12/2024 9:51 PM
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
13 KB

C... — 08/12/2024 10:20 PM
CREATE NEW POST
Enter topic (optional): ail 
Enter message content: asdasd

Server response: Authentication failed

DISCUSSION BOARD - Logged in as: SInbad
Create a new post
View all posts
Filter posts
Logout
Exit
Choose an option:

Sinbad — 08/12/2024 10:21 PM
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB

C... — 08/12/2024 10:24 PM
CREATE NEW POST
Enter topic (optional): tech
Enter message content: tecy stuff
Debug - Sending post with message: [0|Sinbad|Sinbad|Sinbad|tech|tecy stuff]

Server response: Authentication failed

DISCUSSION BOARD - Logged in as: Sinbad
[10:24 PM]
tarting Discussion Board Server...
Server socket bound successfully to IP: 172.16.5.12, Port: 8080
Server listening on port 8080
Debug - Processing message: [1|Simbab|Simbab1389|||]
Debug - Message type: [1]
User not found: Simbab
Debug - Processing message: [0|Sinbad|Sinbad|Sinbad|tech|tecy stuff]
Debug - Message type: [0]
User not found: Sinbad

Sinbad — 08/12/2024 10:25 PM
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
13 KB
[10:31 PM]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
13 KB
[10:32 PM]
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB

C... — 08/12/2024 10:35 PM
Choose an option: 1

CREATE NEW POST
Enter topic (optional): techsavy
Enter message content: this is the message
Debug - Sending post with message: [0|Adila|Adila123|Adila|techsavy|this is the message]

Server response: Authentication failed

Sinbad — 08/12/2024 10:36 PM
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
10 KB
[10:37 PM]
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
5 KB
[10:37 PM]
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB

C... — 08/12/2024 10:38 PM
sinbad@Sinbad:~/sinbad/Assignment3$ g++ Client.cpp -o client
sinbad@Sinbad:~/sinbad/Assignment3$ ./client

DISCUSSION BOARD MENU
Login
Create new user
Exit
Choice: 2

CREATE NEW USER
Username: wip
Password: wipper
Error: Connection failed

Error: Connection failed

DISCUSSION BOARD MENU
Login
Create new user
Exit
Choice:
[10:42 PM]
ISCUSSION BOARD MENU
Login
Create new user
Exit
Choice: 2

CREATE NEW USER
Username: adilla
Password: adilla123
Debug - Sending message: [3||adilla|adilla123]
Debug - Received bytes: 25

User created successfully

DISCUSSION BOARD MENU
Login
Create new user
Exit
Choice:

C... — 08/12/2024 10:50 PM
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
Expand
message.txt
9 KB
[10:51 PM]
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
Expand
message.txt
10 KB
10 December 2024

Sinbad — 10/12/2024 10:57 AM

Required_Documents.pdf
3.31 MB

Sinbad — 10/12/2024 11:05 AM

Could you walk us through your process for creating engaging content.docx
14.24 KB

Sinbad — 10/12/2024 12:24 PM
https://conestogac.zoom.us/j/9725117914
Zoom Video
Join our Cloud HD Video Meeting
Zoom is the leader in modern enterprise video communications, with an easy, reliable cloud platform for video and audio conferencing, chat, and webinars across mobile, desktop, and room systems. Zoom Rooms is the original software-based conference room solution used around the world in board, conference, huddle, and training rooms, as well as ex...

Sinbad — 10/12/2024 12:37 PM
https://conestogac.zoom.us/j/9725117914
Zoom Video
Join our Cloud HD Video Meeting
Zoom is the leader in modern enterprise video communications, with an easy, reliable cloud platform for video and audio conferencing, chat, and webinars across mobile, desktop, and room systems. Zoom Rooms is the original software-based conference room solution used around the world in board, conference, huddle, and training rooms, as well as ex...

Sinbad — 10/12/2024 1:04 PM


C... — 10/12/2024 4:44 PM




Sinbad — 10/12/2024 5:05 PM

[5:05 PM]

26 January 2025

Sinbad — 26/01/2025 12:39 AM
1
00:00:51,093 --> 00:00:52,094
Graner.

2
00:00:52,177 --> 00:00:54,596
Expand
Severance - 1x06 - Hide and Seek.WEB.ATVP.en.srt
31 KB

Sinbad — 26/01/2025 2:08 AM
1
00:00:44,671 --> 00:00:47,132
All right, Radar. Okay,
come on. Let's go.

2
Expand
Severance.S01E08.WEB.x264-TG.srt
25 KB

Sinbad — 26/01/2025 2:47 AM
1
00:00:17,017 --> 00:00:18,393
What?

2
00:00:18,477 --> 00:00:21,355
Expand
Severance.S01E09.1080p.WEBRip.x265-RARBG-en.srt
29 KB
9 February 2025

C... — 09/02/2025 11:46 PM


[11:46 PM]

Assignment #1.pdf
504.02 KB
31 March 2025

Sinbad — 31/03/2025 11:02 PM

Event-App.zip
6.54 MB

C... — 31/03/2025 11:35 PM
take a look at download\event-app

I cant log in in this app and create my own account implement all the featires fpr a real website for this and whatever is written that its done for a real website do it for this and make this a full fledge working website
1 April 2025

Sinbad — 01/04/2025 1:08 AM

Group-16-Software-Design-Techniques.zip
313.49 KB

Sinbad — 01/04/2025 1:55 AM

pikachu.zip
402.36 KB

Sinbad — 01/04/2025 2:41 AM










3 April 2025

Sinbad — 03/04/2025 12:45 PM

Group-16-Software-Design-Techniques-main.zip
163.14 KB
NEW

Sinbad — 03/04/2025 1:18 PM
https://github.com/ksantos7146/Group-16-Software-Design-Techniques.git
GitHub
GitHub - ksantos7146/Group-16-Software-Design-Techniques
Contribute to ksantos7146/Group-16-Software-Design-Techniques development by creating an account on GitHub.

NEW

Sinbad — 03/04/2025 1:31 PM
ok now
NEW
[1:31 PM]
thats gpt talk
NEW
8 April 2025

C... — 6:13 PM
// Client.cpp for Linux/Raspberry Pi
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
    // Generate a unique aircraft ID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int aircraftId = dis(gen);
    
    // Get server address and port
    const char* serverAddress = "127.0.0.1"; // Default to localhost
    const char* port = DEFAULT_PORT;
    std::string telemetryFile = "Telem_2023_3_12 14_56_40.txt";
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            serverAddress = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            telemetryFile = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-id") == 0 && i + 1 < argc) {
            aircraftId = std::stoi(argv[i + 1]);
            i++;
        }
    }
    
    std::cout << "Client starting with Aircraft ID: " << aircraftId << std::endl;
    std::cout << "Connecting to server: " << serverAddress << ":" << port << std::endl;
    std::cout << "Using telemetry file: " << telemetryFile << std::endl;
    
    // Create socket structures
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
    
    // Create a socket for connecting to server
    int connectSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (connectSocket < 0) {
        std::cerr << "socket failed" << std::endl;
        freeaddrinfo(addr);
        return 1;
    }
    
    // Connect to server
    result = connect(connectSocket, addr->ai_addr, (int)addr->ai_addrlen);
    if (result < 0) {
        std::cerr << "connect failed" << std::endl;
        close(connectSocket);
        freeaddrinfo(addr);
        return 1;
    }
    
    freeaddrinfo(addr);
    
    // Open telemetry file
    std::ifstream file(telemetryFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open telemetry file: " << telemetryFile << std::endl;
        close(connectSocket);
        return 1;
    }
    
    std::string line;
    std::string header;
    
    // Read header line (if exists)
    std::getline(file, header);
... (38 lines left)
Collapse
message.txt
5 KB
NEW

C... — 6:30 PM
FUEL TOTAL QUANTITY,12_3_2023 14:56:47,47.865124, 
 12_3_2023 14:56:48,47.865021, 
 12_3_2023 14:56:49,47.864925, 
 12_3_2023 14:56:50,47.864826, 
 12_3_2023 14:56:51,47.864727, 
 12_3_2023 14:56:53,47.864624, ... (64 KB left)
Expand
Telem_2023_3_12 14_56_40.txt
114 KB
NEW
[6:33 PM]
#!/bin/bash
index=1
count=25

Replace with your server's actual IP address
SERVER_IP="192.168.0.13"
PORT="27015"
TELEMETRY_FILE="Telem_2023_3_12 14_56_40.txt"

while [ $index -le $count ]
do
  ./Client -s $SERVER_IP -p $PORT -f "$TELEMETRY_FILE" &
  index=$((index+1))
  echo $index
done
NEW
[6:34 PM]
#!/bin/bash

Check if server IP is provided as argument
if [ $# -lt 1 ]; then
  echo "Usage: $0 <server_ip> [port] [count]"
  echo "Example: $0 192.168.0.13 27015 25"
  exit 1
fi

Set parameters
SERVER_IP=$1
PORT=${2:-27015}  # Default to 27015 if not specified
count=${3:-25}    # Default to 25 if not specified
TELEMETRY_FILE="Telem_2023_3_12 14_56_40.txt"

index=1

echo "Starting load test with $count clients connecting to $SERVER_IP:$PORT"

while [ $index -le $count ]
do
  ./Client -s $SERVER_IP -p $PORT -f "$TELEMETRY_FILE" &
  index=$((index+1))
  echo "Started client $index of $count"
done

echo "All $count clients started"
NEW

Sinbad — 7:22 PM
https://pink-petal-chat.lovable.app/login
pink-petal-chat
Lovable Generated Project

NEW

C... — 7:50 PM
FUEL TOTAL QUANTITY,12_3_2023 16:26:11,41.702572, 
 12_3_2023 16:27:48,41.702160, 
 12_3_2023 16:27:49,41.701828, 
 12_3_2023 16:27:51,41.701283, 
 12_3_2023 16:27:52,41.701035, 
 12_3_2023 16:27:54,41.700779, ... (13 KB left)
Expand
Telem_2023_3_12 16_26_4.txt
63 KB
NEW

C... — 8:06 PM
// Client.cpp (Patched Version for Raspberry Pi/Linux)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
Expand
message.txt
4 KB
NEW

C... — 8:15 PM
// Client.cpp (Corrected Version for Raspberry Pi/Linux)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
Expand
message.txt
4 KB
NEW

C... — 8:25 PM
// Client.cpp (Corrected Version)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
Expand
message.txt
7 KB
NEW

C... — 8:40 PM
// Client.cpp (Corrected Version)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
Expand
message.txt
9 KB
NEW

C... — 8:55 PM
// Client.cpp (Windows Compatible Version)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
Expand
message.txt
9 KB
NEW
[8:58 PM]
FUEL TOTAL QUANTITY,12_3_2023 14:56:47,47.865124, 
 12_3_2023 14:56:48,47.865021, 
 12_3_2023 14:56:49,47.864925, 
 12_3_2023 14:56:50,47.864826, 
 12_3_2023 14:56:51,47.864727, 
 12_3_2023 14:56:53,47.864624, ... (64 KB left)
Expand
Telem_2023_3_12 14_56_40.txt
114 KB
NEW
[8:58 PM]
#!/bin/bash

SERVER_IP="192.168.X.X"
PORT=27015
FILE="Telem_2023_3_12 14_56_40.txt"
COUNT=25

for ((i=1; i<=COUNT; i++)); do
  ./main_client -s "$SERVER_IP" -p "$PORT" -f "$FILE" &
  echo "Started client $i"
  sleep 0.2
done
NEW
[9:00 PM]
@echo off
SETLOCAL ENABLEEXTENSIONS

SET SERVER_IP=192.168.X.X
SET PORT=27015
SET FILE=Telem_2023_3_12 14_56_40.txt
SET /A "COUNT=25"
SET /A "INDEX=1"

:spawn_loop
IF %INDEX% LEQ %COUNT% (
    START /MIN Client.exe -s %SERVER_IP% -p %PORT% -f "%FILE%"
    SET /A INDEX+=1
    GOTO spawn_loop
)

ENDLOCAL
NEW

C... — 9:16 PM
// Server.cpp (Crash-proof version for load testing)
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
Expand
message.txt
10 KB
NEW

Sinbad — 9:35 PM
std::string buffer;

while ((recvResult = recv(clientSocket, recvbuf, BUFFER_SIZE - 1, 0)) > 0) {
    recvbuf[recvResult] = '\0';
    buffer += recvbuf;
Expand
message.txt
3 KB
NEW
NEW
[9:38 PM]
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
Expand
message.txt
10 KB
NEW


Message @Sinbad
?








Sinbad
_...
zip/zap



Member Since
Aug 24, 2021
Mutual Servers — 4
Mutual Friends — 2

View Full Profile
;
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
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

#define _CRT_SECURE_NO_WARNINGS_
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

std::vector<AircraftRecord> aircraftDatabase;
std::mutex databaseMutex;

int findAircraft(int id) {
    for (int i = 0; i < aircraftDatabase.size(); i++) {
        if (aircraftDatabase[i].id == id) {
            return i;
        }
    }
    return -1;
}

void calculateFuelConsumption(int index) {
    if (aircraftDatabase[index].flightData.size() < 2) return;

    std::sort(
        aircraftDatabase[index].flightData.begin(),
        aircraftDatabase[index].flightData.end(),
        [](const FlightData& a, const FlightData& b) {
            return a.timestamp < b.timestamp;
        }
    );

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

void saveFinalFlightData(int index) {
    std::string filename = "aircraft_" + std::to_string(aircraftDatabase[index].id) + "_history.txt";
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &now);
        std::string dt(timeStr);
        dt.pop_back();

        file << "Flight ended: " << dt << std::endl;
        file << "Total flight time: " << aircraftDatabase[index].totalFlightTime << " seconds" << std::endl;
        file << "Total fuel consumed: " << aircraftDatabase[index].totalFuelConsumed << " gallons" << std::endl;
        file << "Average fuel consumption: " << aircraftDatabase[index].avgFuelConsumption << " gallons/second" << std::endl;
        file << "--------------------------------" << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file for aircraft " << aircraftDatabase[index].id << std::endl;
    }
}

void handleClient(SOCKET clientSocket) {
    char recvbuf[BUFFER_SIZE];
    int recvResult;
    int aircraftId = -1;
    int dbIndex = -1;

    std::string buffer;

    while ((recvResult = recv(clientSocket, recvbuf, BUFFER_SIZE - 1, 0)) > 0) {
        recvbuf[recvResult] = '\0';
        buffer += recvbuf;

        size_t pos;
        while ((pos = buffer.find('\n')) != std::string::npos) {
            std::string line = buffer.substr(0, pos);
            buffer.erase(0, pos + 1);

            try {
                std::istringstream ss(line);
                std::string token;

                if (getline(ss, token, ',')) {
                    try {
                        aircraftId = std::stoi(token);
                    }
                    catch (...) {
                        std::cerr << "Invalid aircraft ID received: " << token << std::endl;
                        continue;
                    }

                    std::lock_guard<std::mutex> lock(databaseMutex);
                    dbIndex = findAircraft(aircraftId);
                    if (dbIndex == -1) {
                        AircraftRecord newAircraft{ aircraftId, {}, 0.0, 0.0, 0.0, true };
                        aircraftDatabase.push_back(newAircraft);
                        dbIndex = aircraftDatabase.size() - 1;
                        std::cout << "New aircraft connected: ID " << aircraftId << std::endl;
                    }
                } else continue;

                if (getline(ss, token, ',') && token == "END") {
                    std::lock_guard<std::mutex> lock(databaseMutex);
                    aircraftDatabase[dbIndex].activeFlight = false;
                    calculateFuelConsumption(dbIndex);
                    saveFinalFlightData(dbIndex);
                    aircraftDatabase[dbIndex].flightData.clear();
                    std::cout << "Flight ended for aircraft ID " << aircraftId << std::endl;
                    continue;
                }

                double timestamp = 0.0, fuelRemaining = 0.0;
                if (getline(ss, token, ',')) {
                    try {
                        timestamp = std::stod(token);
                    } catch (...) {
                        std::cerr << "Invalid timestamp received." << std::endl;
                        continue;
                    }

                    if (getline(ss, token, ',')) {
                        try {
                            fuelRemaining = std::stod(token);
                        } catch (...) {
                            std::cerr << "Invalid fuel value received." << std::endl;
                            continue;
                        }

                        std::lock_guard<std::mutex> lock(databaseMutex);
                        FlightData fd{ timestamp, fuelRemaining };
                        aircraftDatabase[dbIndex].flightData.push_back(fd);
                        calculateFuelConsumption(dbIndex);

                        std::cout << "Aircraft ID: " << aircraftId << ", Time: " << timestamp
                                  << ", Fuel: " << fuelRemaining
                                  << ", Avg Consumption: " << aircraftDatabase[dbIndex].avgFuelConsumption
                                  << " gallons/second" << std::endl;
                    }
                }
            }
            catch (...) {
                std::cerr << "Unhandled exception while parsing line." << std::endl;
            }
        }
    }

    std::cout << "Connection closing for aircraft ID " << aircraftId << std::endl;
    std::lock_guard<std::mutex> lock(databaseMutex);
    if (dbIndex != -1 && aircraftDatabase[dbIndex].activeFlight) {
        aircraftDatabase[dbIndex].activeFlight = false;
        calculateFuelConsumption(dbIndex);
        saveFinalFlightData(dbIndex);
        aircraftDatabase[dbIndex].flightData.clear();
    }

    closesocket(clientSocket);
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    const char* port = DEFAULT_PORT;
    if (argc > 1) port = argv[1];

    struct addrinfo hints {}, * addr = nullptr;
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

    result = bind(listenSocket, addr->ai_addr, (int)addr->ai_addrlen);
    freeaddrinfo(addr);
    if (result == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    result = listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << port << "..." << std::endl;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}