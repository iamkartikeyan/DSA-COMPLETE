// 17.2.03 - Load Balancing
// Load balancing algorithms: Round Robin, Least Connections,
// Weighted Round Robin, IP Hash. Simulate each algorithm.

#include <iostream>

using namespace std;

const int MAX_SERVERS = 10;

// Server with load capacity
struct Server {
    int id;
    int weight;
    int activeConnections;
    int totalHandled;
};

// ---- Round Robin ----
// Cycle through servers in order: S0, S1, S2, S0, S1, ...
int roundRobinIndex = 0;

int roundRobin(Server servers[], int numServers) {
    int selected = roundRobinIndex % numServers;
    roundRobinIndex++;
    servers[selected].activeConnections++;
    servers[selected].totalHandled++;
    return selected;
}

// ---- Least Connections ----
// Select server with fewest active connections
int leastConnections(Server servers[], int numServers) {
    int minConn = servers[0].activeConnections;
    int selected = 0;
    for (int i = 1; i < numServers; i++) {
        if (servers[i].activeConnections < minConn) {
            minConn = servers[i].activeConnections;
            selected = i;
        }
    }
    servers[selected].activeConnections++;
    servers[selected].totalHandled++;
    return selected;
}

// ---- Weighted Round Robin ----
// Servers with higher weight get more traffic
int weightedRRIndex = 0;
int weightedRRCounter = 0;

int weightedRoundRobin(Server servers[], int numServers) {
    // Calculate total weight
    int totalWeight = 0;
    for (int i = 0; i < numServers; i++) {
        totalWeight += servers[i].weight;
    }

    // Select based on weight distribution
    int count = 0;
    int selected = 0;
    for (int i = 0; i < numServers; i++) {
        count += servers[i].weight;
        if (weightedRRCounter < count) {
            selected = i;
            break;
        }
    }
    weightedRRCounter++;
    if (weightedRRCounter >= totalWeight) {
        weightedRRCounter = 0;
    }

    servers[selected].activeConnections++;
    servers[selected].totalHandled++;
    return selected;
}

// ---- IP Hash (Sticky Sessions) ----
// Hash client IP to determine server
int ipHash(int clientIP, Server servers[], int numServers) {
    int selected = clientIP % numServers;
    servers[selected].activeConnections++;
    servers[selected].totalHandled++;
    return selected;
}

// Reset active connections
void resetConnections(Server servers[], int numServers) {
    for (int i = 0; i < numServers; i++) {
        servers[i].activeConnections = 0;
    }
}

// Print server stats
void printStats(Server servers[], int numServers, int totalRequests) {
    for (int i = 0; i < numServers; i++) {
        cout << "  Server " << servers[i].id << " (weight=" << servers[i].weight
             << "): " << servers[i].totalHandled << " requests" << endl;
    }
    cout << "  Total: " << totalRequests << " requests" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  LOAD BALANCING ALGORITHMS" << endl;
    cout << "========================================" << endl;

    int numServers = 3;
    Server servers[3];
    servers[0].id = 1; servers[0].weight = 3;
    servers[1].id = 2; servers[1].weight = 2;
    servers[2].id = 3; servers[2].weight = 1;

    int clientIPs[] = {101, 102, 103, 104, 105, 106};
    int numRequests = 6;

    // 1. Round Robin
    cout << endl << "1. ROUND ROBIN" << endl;
    for (int i = 0; i < numServers; i++) {
        servers[i].totalHandled = 0;
        servers[i].activeConnections = 0;
    }
    roundRobinIndex = 0;
    for (int i = 0; i < numRequests; i++) {
        int s = roundRobin(servers, numServers);
        cout << "  Request " << (i + 1) << " -> Server " << servers[s].id << endl;
    }
    printStats(servers, numServers, numRequests);

    // 2. Least Connections
    cout << endl << "2. LEAST CONNECTIONS" << endl;
    for (int i = 0; i < numServers; i++) {
        servers[i].totalHandled = 0;
        servers[i].activeConnections = 0;
    }
    // Simulate varying connection durations
    servers[0].activeConnections = 5;
    servers[1].activeConnections = 2;
    servers[2].activeConnections = 8;
    cout << "  Initial connections: S1=5, S2=2, S3=8" << endl;
    for (int i = 0; i < numRequests; i++) {
        int s = leastConnections(servers, numServers);
        cout << "  Request " << (i + 1) << " -> Server " << servers[s].id
             << " (conn=" << servers[s].activeConnections << ")" << endl;
    }
    printStats(servers, numServers, numRequests);

    // 3. Weighted Round Robin
    cout << endl << "3. WEIGHTED ROUND ROBIN" << endl;
    for (int i = 0; i < numServers; i++) {
        servers[i].totalHandled = 0;
        servers[i].activeConnections = 0;
    }
    weightedRRIndex = 0;
    weightedRRCounter = 0;
    int totalWeight = 0;
    for (int i = 0; i < numServers; i++) totalWeight += servers[i].weight;
    int wrRequests = totalWeight * 2;  // 2 complete cycles
    cout << "  Weights: S1=3, S2=2, S3=1 (total=" << totalWeight << ")" << endl;
    for (int i = 0; i < wrRequests; i++) {
        int s = weightedRoundRobin(servers, numServers);
    }
    printStats(servers, numServers, wrRequests);
    cout << "  Expected ratio: 3:2:1 = ";
    cout << (wrRequests * 3 / totalWeight) << ":"
         << (wrRequests * 2 / totalWeight) << ":"
         << (wrRequests * 1 / totalWeight) << endl;

    // 4. IP Hash
    cout << endl << "4. IP HASH (Sticky Sessions)" << endl;
    for (int i = 0; i < numServers; i++) {
        servers[i].totalHandled = 0;
        servers[i].activeConnections = 0;
    }
    for (int i = 0; i < numRequests; i++) {
        int s = ipHash(clientIPs[i], servers, numServers);
        cout << "  Client IP " << clientIPs[i] << " -> Server " << servers[s].id << endl;
    }
    printStats(servers, numServers, numRequests);
    cout << "  Same IP always goes to same server (sticky session)" << endl;

    cout << endl << "========================================" << endl;
    cout << "  ALGORITHM COMPARISON" << endl;
    cout << "========================================" << endl;
    cout << "  Round Robin:    Simple, fair for equal servers" << endl;
    cout << "  Least Conn:     Best for varying request durations" << endl;
    cout << "  Weighted RR:    Accounts for server capacity" << endl;
    cout << "  IP Hash:        Session affinity, cache-friendly" << endl;

    return 0;
}
