#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

// ===== SKIP LIST (Probabilistic Alternative to BST) =====
// Concept: Multiple linked lists at different levels for O(log n) search
struct SkipNode {
    int val;
    vector<SkipNode*> forward;
    SkipNode(int v, int level) : val(v), forward(level + 1, nullptr) {}
};

class SkipList {
    int maxLevel;
    float p;
    int level;
    SkipNode* header;
    mt19937 rng;

    int randomLevel() {
        int lvl = 0;
        while ((rng() % 100) / 100.0 < p && lvl < maxLevel) lvl++;
        return lvl;
    }
public:
    SkipList() : maxLevel(16), p(0.5), level(0), rng(random_device{}()) {
        header = new SkipNode(-1, maxLevel);
    }

    bool search(int target) {
        SkipNode* curr = header;
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < target)
                curr = curr->forward[i];
        }
        curr = curr->forward[0];
        return curr && curr->val == target;
    }

    void insert(int val) {
        vector<SkipNode*> update(maxLevel + 1);
        SkipNode* curr = header;
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < val)
                curr = curr->forward[i];
            update[i] = curr;
        }
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) update[i] = header;
            level = newLevel;
        }
        SkipNode* newNode = new SkipNode(val, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    // Avg: O(log n) search/insert/delete, O(n) space
};

// ===== SPLAY TREE (Self-adjusting BST) =====
// Concept: Recently accessed nodes move to root via rotations
// Amortized O(log n), no extra space for balance info
struct SplayNode {
    int key;
    SplayNode *left, *right;
    SplayNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

SplayNode* rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, int key) {
    if (!root || root->key == key) return root;
    if (root->key > key) {
        if (!root->left) return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = leftRotate(root->left);
        }
        return root->left ? rightRotate(root) : root;
    } else {
        if (!root->right) return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rightRotate(root->right);
        } else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return root->right ? leftRotate(root) : root;
    }
}

SplayNode* searchSplay(SplayNode* root, int key) {
    return splay(root, key);
}

// ===== TREAP (Tree + Heap) =====
// Concept: BST by key + heap by random priority
struct TreapNode {
    int key, priority;
    TreapNode *left, *right;
    TreapNode(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

TreapNode* treapInsert(TreapNode* root, int key) {
    if (!root) return new TreapNode(key);
    if (key < root->key) {
        root->left = treapInsert(root->left, key);
        if (root->left->priority > root->priority) root = rotateRight(root);
    } else {
        root->right = treapInsert(root->right, key);
        if (root->right->priority > root->priority) root = rotateLeft(root);
    }
    return root;
}

// ===== SUFFIX ARRAY (Concept) =====
// Stores sorted suffixes of a string for fast pattern matching
vector<pair<string, int>> buildSuffixArray(string s) {
    vector<pair<string, int>> suffixes;
    for (int i = 0; i < s.length(); i++)
        suffixes.push_back({s.substr(i), i});
    sort(suffixes.begin(), suffixes.end());
    return suffixes;
}

// ===== HEAVY-LIGHT DECOMPOSITION (Concept) =====
// Decomposes tree into chains for O(log^2 n) path queries
// Heavy edge: to child with largest subtree
// Light edge: all others
// Each root-to-node path has O(log n) light edges
// Used for: path sum, path max, LCA on trees

void hldConcept() {
    cout << "HLD decomposes tree into chains:\n";
    cout << "- Heavy edge: edge to largest subtree child\n";
    cout << "- Light edge: all other edges\n";
    cout << "- Any path = O(log n) light edges + chain segments\n";
    cout << "- Enables O(log^2 n) path queries on trees\n";
}

int main() {
    // Skip List
    cout << "=== Skip List ===\n";
    SkipList sl;
    sl.insert(3); sl.insert(6); sl.insert(7); sl.insert(9); sl.insert(12);
    cout << "Search 6: " << sl.search(6) << "\n";
    cout << "Search 8: " << sl.search(8) << "\n";

    // Splay Tree
    cout << "\n=== Splay Tree ===\n";
    SplayNode* splayRoot = nullptr;
    splayRoot = new SplayNode(10);
    splayRoot->left = new SplayNode(5);
    splayRoot->right = new SplayNode(20);
    splayRoot = searchSplay(splayRoot, 5);  // 5 moves to root
    cout << "After splaying 5, root = " << splayRoot->key << "\n";

    // Treap
    cout << "\n=== Treap ===\n";
    TreapNode* treapRoot = nullptr;
    treapRoot = treapInsert(treapRoot, 10);
    treapRoot = treapInsert(treapRoot, 5);
    treapRoot = treapInsert(treapRoot, 20);
    cout << "Treap root key: " << treapRoot->key << "\n";

    // Suffix Array
    cout << "\n=== Suffix Array ===\n";
    auto sa = buildSuffixArray("banana");
    for (auto &p : sa) cout << p.second << ": " << p.first << "\n";

    // HLD
    cout << "\n=== Heavy-Light Decomposition ===\n";
    hldConcept();

    return 0;
}
