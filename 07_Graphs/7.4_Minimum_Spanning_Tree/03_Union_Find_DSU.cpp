/*
 * File: 03_Union_Find_DSU.cpp
 * Topic: Union-Find (Disjoint Set Union) data structure
 * Description: Path compression + union by rank
 */
#include <iostream>
using namespace std;

const int MAXV = 100;
int parent[MAXV];
int rankArr[MAXV];

// Initialize: each element is its own parent
void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

// Find with path compression
int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]); // point directly to root
    }
    return parent[x];
}

// Union by rank
void unionSets(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);

    if (rootA != rootB) {
        // Attach shorter tree under taller tree
        if (rankArr[rootA] < rankArr[rootB]) {
            parent[rootA] = rootB;
            cout << "  Union: " << a << " joins " << b << "'s set" << endl;
        } else if (rankArr[rootA] > rankArr[rootB]) {
            parent[rootB] = rootA;
            cout << "  Union: " << b << " joins " << a << "'s set" << endl;
        } else {
            parent[rootB] = rootA;
            rankArr[rootA]++;
            cout << "  Union: " << b << " joins " << a << "'s set (same rank)" << endl;
        }
    } else {
        cout << "  Already in same set" << endl;
    }
}

bool connected(int a, int b) {
    return findSet(a) == findSet(b);
}

int main() {
    cout << "=== Union-Find (DSU) ===" << endl;
    cout << endl;

    int n = 6;
    makeSet(n);

    cout << "Initial sets (each element is its own set):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  parent[" << i << "] = " << parent[i] << endl;
    }
    cout << endl;

    cout << "--- Union Operations ---" << endl;
    unionSets(0, 1);
    unionSets(2, 3);
    unionSets(1, 2);

    cout << endl;
    cout << "--- Connectivity Checks ---" << endl;
    cout << "0 and 3 connected? " << (connected(0, 3) ? "YES" : "NO") << endl;
    cout << "0 and 5 connected? " << (connected(0, 5) ? "YES" : "NO") << endl;

    cout << endl;
    cout << "--- After All Unions ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  findSet(" << i << ") = " << findSet(i) << endl;
    }

    cout << endl;
    cout << "--- How DSU Works ---" << endl;
    cout << "  findSet(x): returns representative (root) of x's set" << endl;
    cout << "  unionSets(a, b): merge sets containing a and b" << endl;
    cout << "  connected(a, b): check if a and b in same set" << endl;
    cout << endl;

    cout << "--- Optimizations ---" << endl;
    cout << "1. Path Compression:" << endl;
    cout << "   During find, make all nodes point directly to root" << endl;
    cout << "   Flattens the tree for faster future finds" << endl;
    cout << endl;
    cout << "2. Union by Rank:" << endl;
    cout << "   Attach shorter tree under taller tree" << endl;
    cout << "   Keeps tree height small" << endl;
    cout << endl;
    cout << "Amortized time: O(alpha(n)) per operation" << endl;
    cout << "alpha(n) <= 4 for all practical values of n!" << endl;
    cout << endl;
    cout << "Use: Kruskal's MST, cycle detection, connected components" << endl;

    return 0;
}
