// 17.2.02 - Horizontal vs Vertical Scaling
// Vertical: add resources to single server (CPU, RAM, disk).
// Horizontal: add more servers, distribute load.
// Compare trade-offs, when to use each.

#include <iostream>
#include <string>

using namespace std;

// Simulate a server with capacity
struct Server {
    int id;
    int cpuCores;
    int memoryGB;
    int maxRequests;
    int currentRequests;

    bool canHandle(int requests) {
        return (currentRequests + requests) <= maxRequests;
    }

    void addRequests(int requests) {
        currentRequests += requests;
    }

    void reset() {
        currentRequests = 0;
    }
};

// ---- Vertical Scaling Simulation ----
void verticalScalingDemo() {
    cout << "=== Vertical Scaling (Scale Up) ===" << endl;

    // Start with a small server
    Server s;
    s.id = 1;
    s.cpuCores = 4;
    s.memoryGB = 8;
    s.maxRequests = 100;
    s.currentRequests = 0;

    cout << "Initial server: " << s.cpuCores << " cores, " << s.memoryGB
         << "GB RAM, " << s.maxRequests << " max req/s" << endl;

    // Add load
    int load[] = {30, 50, 40};
    int numLoads = 3;
    int totalLoad = 0;
    for (int i = 0; i < numLoads; i++) {
        totalLoad += load[i];
    }

    cout << "Incoming load: " << totalLoad << " req/s" << endl;
    if (s.canHandle(totalLoad)) {
        cout << "Server handles all load: " << totalLoad << " <= " << s.maxRequests << endl;
    } else {
        cout << "Server OVERLOADED: " << totalLoad << " > " << s.maxRequests << endl;

        // Scale up vertically
        s.cpuCores = 8;
        s.memoryGB = 32;
        s.maxRequests = 500;
        cout << "SCALED UP: " << s.cpuCores << " cores, " << s.memoryGB
             << "GB RAM, " << s.maxRequests << " max req/s" << endl;
        cout << "Now handles: " << totalLoad << " <= " << s.maxRequests << endl;
    }
    cout << endl;

    cout << "Pros of Vertical Scaling:" << endl;
    cout << "  - Simple: no code changes needed" << endl;
    cout << "  - No data distribution complexity" << endl;
    cout << "  - Single point of management" << endl;
    cout << endl;
    cout << "Cons of Vertical Scaling:" << endl;
    cout << "  - Hardware upper limit exists" << endl;
    cout << "  - Single point of failure" << endl;
    cout << "  - Expensive at high end" << endl;
    cout << "  - Downtime during upgrade" << endl;
    cout << endl;
}

// ---- Horizontal Scaling Simulation ----
void horizontalScalingDemo() {
    cout << "=== Horizontal Scaling (Scale Out) ===" << endl;

    // Start with 1 server
    int numServers = 1;
    int maxPerServer = 100;
    int totalCapacity = numServers * maxPerServer;
    int totalLoad = 250;

    cout << "Initial: " << numServers << " server(s), " << totalCapacity << " total req/s capacity" << endl;
    cout << "Load: " << totalLoad << " req/s" << endl;
    cout << (totalLoad > totalCapacity ? "OVERLOADED!" : "Handling load") << endl;

    // Add servers until capacity is sufficient
    while (totalCapacity < totalLoad) {
        numServers++;
        totalCapacity = numServers * maxPerServer;
        cout << "Added server #" << numServers << ". Total capacity: " << totalCapacity << " req/s" << endl;
    }

    cout << endl << "Final: " << numServers << " servers handling " << totalLoad << " req/s" << endl;

    // Distribute load (round robin)
    Server servers[10];
    for (int i = 0; i < numServers && i < 10; i++) {
        servers[i].id = i + 1;
        servers[i].maxRequests = maxPerServer;
        servers[i].currentRequests = 0;
    }

    // Distribute load evenly
    int perServer = totalLoad / numServers;
    int remainder = totalLoad % numServers;
    for (int i = 0; i < numServers; i++) {
        int load = perServer + (i < remainder ? 1 : 0);
        servers[i].addRequests(load);
    }

    cout << endl << "Load distribution:" << endl;
    for (int i = 0; i < numServers; i++) {
        cout << "  Server " << servers[i].id << ": " << servers[i].currentRequests
             << " / " << servers[i].maxRequests << " req/s" << endl;
    }
    cout << endl;

    cout << "Pros of Horizontal Scaling:" << endl;
    cout << "  - No theoretical upper limit" << endl;
    cout << "  - Fault tolerance (redundancy)" << endl;
    cout << "  - Can use commodity hardware" << endl;
    cout << "  - Zero-downtime scaling" << endl;
    cout << endl;
    cout << "Cons of Horizontal Scaling:" << endl;
    cout << "  - Requires load balancer" << endl;
    cout << "  - Data consistency challenges" << endl;
    cout << "  - Network latency between servers" << endl;
    cout << "  - Complex deployment and monitoring" << endl;
    cout << endl;
}

// ---- Comparison Table ----
void comparisonTable() {
    cout << "=== Comparison ===" << endl;
    cout << endl;
    cout << "| Aspect            | Vertical       | Horizontal      |" << endl;
    cout << "|-------------------|----------------|-----------------|" << endl;
    cout << "| Scalability       | Limited        | Unlimited       |" << endl;
    cout << "| Complexity        | Low            | High            |" << endl;
    cout << "| Fault Tolerance   | Low            | High            |" << endl;
    cout << "| Cost at Scale     | High           | Lower           |" << endl;
    cout << "| Data Consistency  | Easy           | Challenging     |" << endl;
    cout << "| Downtime          | Yes (upgrade)  | No              |" << endl;
    cout << "| Best For          | Small-medium   | Large-scale     |" << endl;
    cout << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  HORIZONTAL VS VERTICAL SCALING" << endl;
    cout << "========================================" << endl;
    cout << endl;

    verticalScalingDemo();
    horizontalScalingDemo();
    comparisonTable();

    cout << "========================================" << endl;
    cout << "  WHEN TO USE WHICH" << endl;
    cout << "========================================" << endl;
    cout << "  - Start with vertical scaling (simple, cheap)" << endl;
    cout << "  - Move to horizontal when hitting limits" << endl;
    cout << "  - Most systems use both (hybrid approach)" << endl;
    cout << "  - Database: vertical first, then sharding" << endl;
    cout << "  - Web tier: horizontal from the start" << endl;

    return 0;
}
