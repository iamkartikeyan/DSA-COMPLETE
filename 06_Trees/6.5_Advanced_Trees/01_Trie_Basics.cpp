/*
 * File: 01_Trie_Basics.cpp
 * Topic: Trie Node Structure, Insert, Search
 * Description: What is Trie and how to insert/search words
 */
#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[26]; // for letters 'a' to 'z'
    bool isEnd; // true if this node marks end of a word

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isEnd = false;
    }
};

// Insert a word into Trie
void insert(TrieNode* root, string word) {
    TrieNode* node = root;
    for (int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a'; // 'a' -> 0, 'b' -> 1, ...
        if (node->children[idx] == NULL) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }
    node->isEnd = true; // mark end of word
}

// Search for exact word
bool search(TrieNode* root, string word) {
    TrieNode* node = root;
    for (int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if (node->children[idx] == NULL) {
            return false; // path doesn't exist
        }
        node = node->children[idx];
    }
    return node->isEnd; // must be end of a word
}

// Check if any word starts with given prefix
bool startsWith(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (int i = 0; i < prefix.length(); i++) {
        int idx = prefix[i] - 'a';
        if (node->children[idx] == NULL) {
            return false;
        }
        node = node->children[idx];
    }
    return true; // full prefix path exists
}

// Free Trie memory
void deleteTrie(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            deleteTrie(node->children[i]);
        }
    }
    delete node;
}

int main() {
    cout << "=== Trie (Prefix Tree) - Basics ===" << endl;
    cout << endl;

    TrieNode* root = new TrieNode();

    // Insert words
    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");
    insert(root, "batch");

    cout << "Inserted: apple, app, bat, batch" << endl;
    cout << endl;

    /*
     * Trie structure:
     * root
     *  |
     *  a -> p -> p -> l -> e* (word ends)
     *         |
     *         * (word "app" ends here too)
     *  |
     *  b -> a -> t -> c -> h* (word "batch" ends)
     *         |
     *         * (word "bat" ends here too)
     */

    cout << "Search results:" << endl;

    if (search(root, "apple")) {
        cout << "  'apple'  -> Found" << endl;
    } else {
        cout << "  'apple'  -> Not Found" << endl;
    }

    if (search(root, "app")) {
        cout << "  'app'    -> Found" << endl;
    } else {
        cout << "  'app'    -> Not Found" << endl;
    }

    if (search(root, "bat")) {
        cout << "  'bat'    -> Found" << endl;
    } else {
        cout << "  'bat'    -> Not Found" << endl;
    }

    if (search(root, "batc")) {
        cout << "  'batc'   -> Found" << endl;
    } else {
        cout << "  'batc'   -> Not Found (not a complete word)" << endl;
    }

    if (search(root, "cat")) {
        cout << "  'cat'    -> Found" << endl;
    } else {
        cout << "  'cat'    -> Not Found" << endl;
    }

    cout << endl;

    cout << "Prefix check:" << endl;
    if (startsWith(root, "ap")) {
        cout << "  'ap'  -> Yes" << endl;
    } else {
        cout << "  'ap'  -> No" << endl;
    }

    if (startsWith(root, "bat")) {
        cout << "  'bat' -> Yes" << endl;
    } else {
        cout << "  'bat' -> No" << endl;
    }

    if (startsWith(root, "cat")) {
        cout << "  'cat' -> Yes" << endl;
    } else {
        cout << "  'cat' -> No" << endl;
    }

    cout << endl;
    cout << "Time: Insert = O(L), Search = O(L), Prefix = O(L)" << endl;
    cout << "      where L = length of word/prefix" << endl;
    cout << "Space: O(26 * N * L) worst case for N words" << endl;

    deleteTrie(root);

    return 0;
}
