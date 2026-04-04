/*
 * Huffman Coding
 *
 * Build optimal prefix-free binary codes for characters based
 * on their frequencies. More frequent characters get shorter codes.
 *
 * Algorithm:
 *   1. Create a leaf node for each character with its frequency.
 *   2. Insert all nodes into a min-heap (priority queue).
 *   3. While heap has more than 1 node:
 *      a. Extract two nodes with smallest frequencies.
 *      b. Create a new internal node with frequency = sum of both.
 *      c. Insert the new node back into the heap.
 *   4. The remaining node is the root of the Huffman tree.
 *   5. Traverse the tree: left = 0, right = 1 to generate codes.
 *
 * Time  : O(n log n)  for n insertions/extractions from heap
 * Space : O(n)        for the tree
 */

#include <iostream>
#include <climits>

#define MAX_NODES 100
#define MAX_CODE_LEN 20

struct TreeNode {
    char ch;              /* character (for leaf nodes) */
    int freq;             /* frequency */
    int left;             /* index of left child (-1 if leaf) */
    int right;            /* index of right child (-1 if leaf) */
};

TreeNode tree[MAX_NODES];
int nodeCount = 0;
char codes[256][MAX_CODE_LEN];  /* code for each ASCII character */

/* Create a new tree node, return its index */
int createNode(char ch, int freq, int left, int right) {
    int idx = nodeCount;
    tree[idx].ch = ch;
    tree[idx].freq = freq;
    tree[idx].left = left;
    tree[idx].right = right;
    nodeCount = nodeCount + 1;
    return idx;
}

/* ---- Min-Heap (priority queue) of node indices ---- */
int heap[MAX_NODES];
int heapSize = 0;

void heapInsert(int nodeIdx) {
    heap[heapSize] = nodeIdx;
    int i = heapSize;
    heapSize = heapSize + 1;

    /* Bubble up */
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (tree[heap[i]].freq < tree[heap[parent]].freq) {
            int temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

int heapExtractMin() {
    if (heapSize <= 0) {
        return -1;
    }

    int minNode = heap[0];
    heapSize = heapSize - 1;

    if (heapSize > 0) {
        heap[0] = heap[heapSize];

        /* Bubble down */
        int i = 0;
        while (1) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < heapSize && tree[heap[left]].freq < tree[heap[smallest]].freq) {
                smallest = left;
            }
            if (right < heapSize && tree[heap[right]].freq < tree[heap[smallest]].freq) {
                smallest = right;
            }
            if (smallest != i) {
                int temp = heap[i];
                heap[i] = heap[smallest];
                heap[smallest] = temp;
                i = smallest;
            } else {
                break;
            }
        }
    }

    return minNode;
}

/* Generate codes by traversing the tree */
void generateCodes(int nodeIdx, char code[], int depth) {
    if (nodeIdx < 0) return;

    /* Leaf node */
    if (tree[nodeIdx].left == -1 && tree[nodeIdx].right == -1) {
        code[depth] = '\0';
        int i = 0;
        while (i <= depth) {
            codes[(int)tree[nodeIdx].ch][i] = code[i];
            i = i + 1;
        }
        return;
    }

    /* Go left (append '0') */
    code[depth] = '0';
    generateCodes(tree[nodeIdx].left, code, depth + 1);

    /* Go right (append '1') */
    code[depth] = '1';
    generateCodes(tree[nodeIdx].right, code, depth + 1);
}

int huffmanBuild(char chars[], int freqs[], int n) {
    nodeCount = 0;
    heapSize = 0;

    /* Create leaf nodes and insert into min-heap */
    int i = 0;
    while (i < n) {
        int idx = createNode(chars[i], freqs[i], -1, -1);
        heapInsert(idx);
        i = i + 1;
    }

    /* Build the Huffman tree */
    while (heapSize > 1) {
        int left = heapExtractMin();
        int right = heapExtractMin();
        int sumFreq = tree[left].freq + tree[right].freq;
        int parent = createNode('$', sumFreq, left, right);
        heapInsert(parent);
    }

    return heapExtractMin();  /* root of the tree */
}

int main() {
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[]  = {5, 9, 12, 13, 16, 45};
    int n = 6;

    std::cout << "=== Huffman Coding ===" << std::endl;
    std::cout << std::endl;
    std::cout << "Characters and frequencies:" << std::endl;

    int i = 0;
    while (i < n) {
        std::cout << "  '" << chars[i] << "' : " << freqs[i] << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;

    /* Build Huffman tree */
    int root = huffmanBuild(chars, freqs, n);

    /* Generate codes */
    char code[MAX_CODE_LEN];
    generateCodes(root, code, 0);

    /* Print codes */
    std::cout << "Huffman Codes:" << std::endl;

    i = 0;
    while (i < n) {
        std::cout << "  '" << chars[i] << "' -> " << codes[(int)chars[i]] << std::endl;
        i = i + 1;
    }

    std::cout << std::endl;
    std::cout << "Key Properties:" << std::endl;
    std::cout << "  1. PREFIX-FREE: No code is a prefix of another." << std::endl;
    std::cout << "     This means decoding is unambiguous." << std::endl;
    std::cout << "  2. OPTIMAL: Minimizes total encoded length." << std::endl;
    std::cout << "     More frequent characters get shorter codes." << std::endl;
    std::cout << "  3. GREEDY: At each step, merge the two smallest" << std::endl;
    std::cout << "     frequency nodes. This is the greedy choice." << std::endl;

    return 0;
}
