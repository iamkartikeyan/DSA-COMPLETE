/*
 * File: 02_Trie_Autocomplete.cpp
 * Topic: Collect all words with a given prefix (Autocomplete)
 * Description: DFS traversal to find all words under a prefix
 */
#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isEnd = false;
    }
};

void insert(TrieNode* root, string word) {
    TrieNode* node = root;
    for (int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if (node->children[idx] == NULL) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
    }
    node->isEnd = true;
}

// Navigate to the node at end of prefix
TrieNode* goToPrefix(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (int i = 0; i < prefix.length(); i++) {
        int idx = prefix[i] - 'a';
        if (node->children[idx] == NULL) {
            return NULL;
        }
        node = node->children[idx];
    }
    return node;
}

// DFS: collect all words starting from this node
void collectWords(TrieNode* node, string current, vector<string>& result) {
    if (node->isEnd) {
        result.push_back(current);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            char c = 'a' + i;
            collectWords(node->children[i], current + c, result);
        }
    }
}

// Get all words with given prefix
vector<string> getWordsWithPrefix(TrieNode* root, string prefix) {
    vector<string> result;
    TrieNode* node = goToPrefix(root, prefix);
    if (node == NULL) {
        return result; // prefix not found
    }
    collectWords(node, prefix, result);
    return result;
}

void deleteTrie(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            deleteTrie(node->children[i]);
        }
    }
    delete node;
}

int main() {
    cout << "=== Trie - Autocomplete ===" << endl;
    cout << endl;

    TrieNode* root = new TrieNode();

    // Insert words
    string words[] = {"apple", "app", "apex", "ape", "bat", "batch", "batching"};
    int n = 7;

    cout << "Words in dictionary: ";
    for (int i = 0; i < n; i++) {
        insert(root, words[i]);
        cout << words[i] << " ";
    }
    cout << endl;
    cout << endl;

    // Autocomplete for "ap"
    string prefix = "ap";
    cout << "Autocomplete '" << prefix << "':" << endl;
    vector<string> apWords = getWordsWithPrefix(root, prefix);
    for (int i = 0; i < apWords.size(); i++) {
        cout << "  " << apWords[i] << endl;
    }

    cout << endl;

    // Autocomplete for "bat"
    prefix = "bat";
    cout << "Autocomplete '" << prefix << "':" << endl;
    vector<string> batWords = getWordsWithPrefix(root, prefix);
    for (int i = 0; i < batWords.size(); i++) {
        cout << "  " << batWords[i] << endl;
    }

    cout << endl;
    cout << "How it works:" << endl;
    cout << "  1. Navigate to the prefix node" << endl;
    cout << "  2. Do DFS from that node" << endl;
    cout << "  3. Whenever isEnd = true, we found a word" << endl;
    cout << "  4. Collect all such words" << endl;
    cout << endl;
    cout << "Used in: Search autocomplete, spell check, word games" << endl;

    deleteTrie(root);

    return 0;
}
