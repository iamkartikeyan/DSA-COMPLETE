// 17.2.01 - What Is System Design
// System design covers scalability, load balancing, caching,
// databases, CAP theorem, and distributed system concepts.

#include <iostream>
#include <string>

using namespace std;

// ---- Scalability Concepts ----
void explainScalability() {
    cout << "=== Scalability ===" << endl;
    cout << "A system is scalable if it can handle increased load" << endl;
    cout << "by adding resources (CPU, memory, servers)." << endl;
    cout << endl;
    cout << "Two types of scaling:" << endl;
    cout << "  1. Vertical Scaling (Scale Up):" << endl;
    cout << "     - Add more power to existing server" << endl;
    cout << "     - More CPU, RAM, faster disk" << endl;
    cout << "     - Simple: no code changes needed" << endl;
    cout << "     - Limit: hardware has upper bound" << endl;
    cout << "     - Single point of failure remains" << endl;
    cout << endl;
    cout << "  2. Horizontal Scaling (Scale Out):" << endl;
    cout << "     - Add more servers" << endl;
    cout << "     - Distribute load across machines" << endl;
    cout << "     - No theoretical upper limit" << endl;
    cout << "     - Requires load balancer" << endl;
    cout << "     - More complex: data consistency, distributed state" << endl;
    cout << endl;
}

// ---- Load Balancing ----
void explainLoadBalancing() {
    cout << "=== Load Balancing ===" << endl;
    cout << "Distributes incoming requests across multiple servers." << endl;
    cout << endl;
    cout << "Algorithms:" << endl;
    cout << "  1. Round Robin:" << endl;
    cout << "     - Cycle through servers: S1, S2, S3, S1, ..." << endl;
    cout << "     - Simple, but ignores server load" << endl;
    cout << "  2. Least Connections:" << endl;
    cout << "     - Send to server with fewest active connections" << endl;
    cout << "     - Better for varied request durations" << endl;
    cout << "  3. IP Hash:" << endl;
    cout << "     - Hash client IP to determine server" << endl;
    cout << "     - Ensures same client hits same server (sticky sessions)" << endl;
    cout << "  4. Weighted Round Robin:" << endl;
    cout << "     - Assign weights based on server capacity" << endl;
    cout << "     - Powerful servers get more traffic" << endl;
    cout << endl;
}

// ---- Caching ----
void explainCaching() {
    cout << "=== Caching ===" << endl;
    cout << "Store frequently accessed data in fast memory (RAM)" << endl;
    cout << "to reduce database load and improve response time." << endl;
    cout << endl;
    cout << "Cache strategies:" << endl;
    cout << "  1. LRU (Least Recently Used):" << endl;
    cout << "     - Evict least recently accessed item" << endl;
    cout << "     - Good for temporal locality" << endl;
    cout << "  2. LFU (Least Frequently Used):" << endl;
    cout << "     - Evict least frequently accessed item" << endl;
    cout << "     - Good for popularity-based access" << endl;
    cout << "  3. FIFO (First In, First Out):" << endl;
    cout << "     - Evict oldest item" << endl;
    cout << "     - Simple but may evict hot data" << endl;
    cout << endl;
    cout << "Cache placement:" << endl;
    cout << "  - Client-side (browser cache)" << endl;
    cout << "  - CDN (Content Delivery Network)" << endl;
    cout << "  - Application-level (Redis, Memcached)" << endl;
    cout << "  - Database-level (query cache)" << endl;
    cout << endl;
}

// ---- CAP Theorem ----
void explainCAPTheorem() {
    cout << "=== CAP Theorem ===" << endl;
    cout << "A distributed system can guarantee at most 2 of 3:" << endl;
    cout << endl;
    cout << "  C - Consistency:" << endl;
    cout << "    Every read gets the latest write (or error)" << endl;
    cout << endl;
    cout << "  A - Availability:" << endl;
    cout << "    Every request gets a response (may be stale)" << endl;
    cout << endl;
    cout << "  P - Partition Tolerance:" << endl;
    cout << "    System continues despite network failures" << endl;
    cout << endl;
    cout << "In practice, P is unavoidable (networks fail)." << endl;
    cout << "So systems choose CP or AP:" << endl;
    cout << "  - CP: Relational DBs (PostgreSQL, MySQL)" << endl;
    cout << "  - AP: NoSQL DBs (Cassandra, DynamoDB)" << endl;
    cout << endl;
}

// ---- Database Types ----
void explainDatabases() {
    cout << "=== Database Types ===" << endl;
    cout << endl;
    cout << "SQL (Relational):" << endl;
    cout << "  - Structured schema, ACID transactions" << endl;
    cout << "  - Good for: financial systems, user data" << endl;
    cout << "  - Examples: PostgreSQL, MySQL, Oracle" << endl;
    cout << "  - Scales vertically (mostly)" << endl;
    cout << endl;
    cout << "NoSQL (Non-relational):" << endl;
    cout << "  - Flexible schema, eventual consistency" << endl;
    cout << "  - Good for: high throughput, unstructured data" << endl;
    cout << "  - Types:" << endl;
    cout << "    - Key-Value: Redis, DynamoDB" << endl;
    cout << "    - Document: MongoDB, CouchDB" << endl;
    cout << "    - Column-Family: Cassandra, HBase" << endl;
    cout << "    - Graph: Neo4j, JanusGraph" << endl;
    cout << "  - Scales horizontally" << endl;
    cout << endl;
}

// ---- Sharding ----
void explainSharding() {
    cout << "=== Sharding (Horizontal Partitioning) ===" << endl;
    cout << "Split database across multiple servers by key ranges." << endl;
    cout << endl;
    cout << "Example: Users by ID range" << endl;
    cout << "  Shard 1: user_id 1-10000" << endl;
    cout << "  Shard 2: user_id 10001-20000" << endl;
    cout << "  Shard 3: user_id 20001-30000" << endl;
    cout << endl;
    cout << "Pros: Scales writes, parallel processing" << endl;
    cout << "Cons: Cross-shard queries slow, rebalancing hard" << endl;
    cout << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  SYSTEM DESIGN BASICS" << endl;
    cout << "========================================" << endl;
    cout << endl;

    explainScalability();
    explainLoadBalancing();
    explainCaching();
    explainCAPTheorem();
    explainDatabases();
    explainSharding();

    cout << "========================================" << endl;
    cout << "  KEY TAKEAWAYS" << endl;
    cout << "========================================" << endl;
    cout << "  - Horizontal scaling > vertical for growth" << endl;
    cout << "  - Load balancer is essential for distributed systems" << endl;
    cout << "  - Cache reduces DB load, improves latency" << endl;
    cout << "  - CAP theorem: choose CP or AP (P is unavoidable)" << endl;
    cout << "  - SQL for consistency, NoSQL for scale" << endl;
    cout << "  - Sharding enables horizontal DB scaling" << endl;

    return 0;
}
