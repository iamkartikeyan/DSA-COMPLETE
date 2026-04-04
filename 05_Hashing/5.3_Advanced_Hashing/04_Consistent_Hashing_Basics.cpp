/*
 * File: 04_Consistent_Hashing_Basics.cpp
 * Topic: What is Consistent Hashing
 * Description: Distributed hash ring for load balancing
 */
#include <iostream>
#include <map>
using namespace std;

// Simple hash function
unsigned int hashFunc(string key) {
    unsigned int h = 5381;
    for (int i = 0; i < key.length(); i++) {
        h = ((h << 5) + h) + key[i];
    }
    return h;
}

int main() {
    cout << "=== Consistent Hashing ===" << endl;
    cout << endl;

    cout << "--- What is Consistent Hashing? ---" << endl;
    cout << "Used in distributed systems to map keys to servers." << endl;
    cout << "Keys and servers are placed on a circular hash ring." << endl;
    cout << "A key maps to the NEXT server clockwise on the ring." << endl;
    cout << endl;

    cout << "--- Why? ---" << endl;
    cout << "Traditional hashing: When server is added/removed," << endl;
    cout << "                    almost ALL keys need remapping." << endl;
    cout << "Consistent hashing: Only keys from affected server" << endl;
    cout << "                    need remapping." << endl;
    cout << endl;

    /*
     * Demo with 3 servers on a hash ring:
     *
     * Each server gets multiple positions (virtual nodes)
     * on the ring for even distribution.
     *
     * Key -> hash(key) -> find next server clockwise
     */

    // Simulate servers on ring
    string servers[] = {"server-A", "server-B", "server-C"};
    int numServers = 3;
    int virtualNodes = 100;

    // Hash ring: hash_value -> server_name
    map<unsigned int, string> ring;

    for (int s = 0; s < numServers; s++) {
        for (int v = 0; v < virtualNodes; v++) {
            // Create virtual node key
            string key = servers[s] + "#" + to_string(v);
            unsigned int hash = hashFunc(key);
            ring[hash] = servers[s];
        }
    }

    cout << "Ring setup:" << endl;
    for (int s = 0; s < numServers; s++) {
        cout << "  " << servers[s] << ": " << virtualNodes << " virtual nodes" << endl;
    }
    cout << endl;

    // Map keys to servers
    string keys[] = {"user:1", "user:2", "user:3", "session:1",
                     "cache:products", "cache:users", "data:100", "data:200"};
    int numKeys = 8;

    cout << "Key distribution:" << endl;
    for (int i = 0; i < numKeys; i++) {
        unsigned int hash = hashFunc(keys[i]);

        // Find next server clockwise
        map<unsigned int, string>::iterator it = ring.lower_bound(hash);
        if (it == ring.end()) {
            it = ring.begin(); // wrap around
        }

        cout << "  \"" << keys[i] << "\" -> " << it->second << endl;
    }

    cout << endl;
    cout << "--- What if a server is removed? ---" << endl;
    cout << "Only keys mapped to that server get remapped." << endl;
    cout << "Other keys stay on their current servers." << endl;
    cout << "This minimizes data movement." << endl;
    cout << endl;
    cout << "--- Use Cases ---" << endl;
    cout << "Memcached, DynamoDB, CDNs, distributed caches" << endl;

    return 0;
}
