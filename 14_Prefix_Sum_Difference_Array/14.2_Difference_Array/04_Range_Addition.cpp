// Range Addition Problem (LeetCode 370)
// Start with array of given length filled with zeros.
// Apply range additions: updates[i] = [startIndex, endIndex, increment].
// Return the final array after all updates.
//
// Approach: Difference array
//   1. Start with diff array of length zeros
//   2. For each update [start, end, inc]:
//      - diff[start] += inc
//      - if end+1 < length: diff[end+1] -= inc
//   3. Reconstruct with prefix sum
//
// Time Complexity: O(length + numUpdates)
// Space Complexity: O(length)

#include <iostream>
using namespace std;

const int MAXN = 1000;

struct Update {
    int start;
    int end;
    int inc;
};

void rangeAddition(int length, const int updates[][3], int numUpdates, int result[]) {
    // Initialize difference array with zeros
    int diff[MAXN];
    for (int i = 0; i < length; i++) {
        diff[i] = 0;
    }

    // Apply each update as O(1) range update
    for (int i = 0; i < numUpdates; i++) {
        diff[updates[i][0]] += updates[i][2];
        if (updates[i][1] + 1 < length) {
            diff[updates[i][1] + 1] -= updates[i][2];
        }
    }

    // Reconstruct via prefix sum
    result[0] = diff[0];
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] + diff[i];
    }
}

int main() {
    cout << "=== Application: Range Addition (LeetCode 370) ===" << endl;
    cout << endl;

    // Example
    int length = 5;
    int updates[][3] = {
        {1, 3, 2},    // indices 1-3: +2
        {2, 4, 3},    // indices 2-4: +3
        {0, 2, -2}    // indices 0-2: -2
    };
    int numUpdates = 3;

    cout << "Length: " << length << endl;
    cout << "Initial array: 0 0 0 0 0" << endl;
    cout << "Updates:" << endl;
    for (int i = 0; i < numUpdates; i++) {
        cout << "  Update " << i + 1 << ": indices " << updates[i][0] << "-" << updates[i][1];
        if (updates[i][2] >= 0) {
            cout << " add +" << updates[i][2] << endl;
        } else {
            cout << " add " << updates[i][2] << endl;
        }
    }
    cout << endl;

    // Show diff array step by step
    int diff[MAXN];
    for (int i = 0; i < length; i++) diff[i] = 0;

    cout << "Difference array evolution:" << endl;
    cout << "  Initial: ";
    for (int i = 0; i < length; i++) cout << diff[i] << " ";
    cout << endl;

    for (int i = 0; i < numUpdates; i++) {
        diff[updates[i][0]] += updates[i][2];
        if (updates[i][1] + 1 < length) {
            diff[updates[i][1] + 1] -= updates[i][2];
        }
        cout << "  After update [" << updates[i][0] << "," << updates[i][1] << ",";
        if (updates[i][2] >= 0) cout << "+";
        cout << updates[i][2] << "]: ";
        for (int j = 0; j < length; j++) cout << diff[j] << " ";
        cout << endl;
    }
    cout << endl;

    // Solve
    int result[MAXN];
    rangeAddition(length, updates, numUpdates, result);

    cout << "Final array (prefix sum of diff):" << endl;
    cout << "  ";
    for (int i = 0; i < length; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "  Expected: -2 0 3 5 3" << endl;

    cout << endl;
    cout << "Manual verification:" << endl;
    cout << "  Start:  [ 0,  0,  0,  0,  0]" << endl;
    cout << "  +[1,3,2]: [ 0,  2,  2,  2,  0]" << endl;
    cout << "  +[2,4,3]: [ 0,  2,  5,  5,  3]" << endl;
    cout << "  +[0,2,-2]: [-2,  0,  3,  5,  3]" << endl;

    return 0;
}
