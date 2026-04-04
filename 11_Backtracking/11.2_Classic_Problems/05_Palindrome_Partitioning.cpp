// 05_Palindrome_Partitioning.cpp
// Given a string, partition it into substrings such that every
// substring is a palindrome. Return all possible such partitions.
//
// Example: "aab" -> ["a","a","b"], ["aa","b"]
//
// Approach: Try every possible split point. For each prefix that is
// a palindrome, include it in the current partition and recurse
// on the remaining suffix.
//
// Time Complexity: O(2^n * n) where n = string length.
//   - 2^n possible ways to split the string (cut or not between each pair).
//   - O(n) to check palindrome and copy partition.
// Space Complexity: O(n) for current partition + O(n) recursion depth.

#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LEN = 20;
int partitionCount = 0;

/*
 * isPalindrome - Check if s[l..r] (inclusive) is a palindrome.
 *
 * Uses two pointers: move inward from both ends, comparing characters.
 */
bool isPalindrome(const char s[], int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

/*
 * copySubstring - Copy s[l..r] into dest and null-terminate.
 */
void copySubstring(const char s[], int l, int r, char dest[]) {
    int idx = 0;
    for (int i = l; i <= r; i++) {
        dest[idx++] = s[i];
    }
    dest[idx] = '\0';
}

/*
 * printPartition - Display one partition of palindromic substrings.
 */
void printPartition(char parts[][MAX_LEN], int count) {
    cout << "  [";
    for (int i = 0; i < count; i++) {
        cout << "\"" << parts[i] << "\"";
        if (i + 1 < count) cout << ", ";
    }
    cout << "]" << endl;
}

/*
 * partitionPalindrome - Find all palindrome partitions of s[idx..].
 *
 * Parameters:
 *   s[]         - the input string
 *   len         - total length of the string
 *   idx         - current position in the string (start of next substring)
 *   parts[][]   - buffer holding current partition (array of substrings)
 *   partCount   - number of substrings in current partition
 *
 * Backtracking flow:
 *   CHOICE:     Pick a split point i (idx <= i < len).
 *               Substring s[idx..i] becomes the next part.
 *   CONSTRAINT: s[idx..i] must be a palindrome.
 *   GOAL:       idx == len (entire string partitioned).
 *   PRUNING:    Not a palindrome -> skip this split point.
 *   BACKTRACK:  The recursive call returns; we overwrite parts[partCount]
 *               in the next iteration (no explicit undo needed).
 */
void partitionPalindrome(const char s[], int len, int idx,
                         char parts[][MAX_LEN], int partCount) {
    // GOAL: entire string partitioned into palindromes
    if (idx == len) {
        partitionCount++;
        printPartition(parts, partCount);
        return;
    }

    // Try every possible split point
    for (int i = idx; i < len; i++) {
        // CONSTRAINT: s[idx..i] must be a palindrome
        if (isPalindrome(s, idx, i)) {
            // CHOICE: take s[idx..i] as the next palindrome substring
            copySubstring(s, idx, i, parts[partCount]);

            partitionPalindrome(s, len, i + 1, parts, partCount + 1);  // recurse

            // BACKTRACK: no explicit undo needed (parts[partCount] overwritten next iteration)
        }
    }
}

int main() {
    cout << "=== Palindrome Partitioning ===" << endl;
    cout << endl;

    cout << "Problem: Split a string into all possible palindrome substrings." << endl;
    cout << "  A palindrome reads the same forwards and backwards." << endl;
    cout << endl;

    // ---- Example 1: "aab" ----
    char s1[] = "aab";
    int len1 = 3;
    char parts1[MAX_LEN][MAX_LEN];

    cout << "--- Partition \"" << s1 << "\" ---" << endl;
    cout << "Expected: [\"a\",\"a\",\"b\"], [\"aa\",\"b\"]" << endl;
    cout << endl;

    partitionCount = 0;
    partitionPalindrome(s1, len1, 0, parts1, 0);
    cout << "Total: " << partitionCount << " partitions" << endl;
    cout << endl;

    // ---- Example 2: "aba" ----
    char s2[] = "aba";
    int len2 = 3;
    char parts2[MAX_LEN][MAX_LEN];

    cout << "--- Partition \"" << s2 << "\" ---" << endl;
    partitionCount = 0;
    partitionPalindrome(s2, len2, 0, parts2, 0);
    cout << "Total: " << partitionCount << " partitions" << endl;
    cout << endl;

    // ---- Example 3: "aabb" ----
    char s3[] = "aabb";
    int len3 = 4;
    char parts3[MAX_LEN][MAX_LEN];

    cout << "--- Partition \"" << s3 << "\" ---" << endl;
    partitionCount = 0;
    partitionPalindrome(s3, len3, 0, parts3, 0);
    cout << "Total: " << partitionCount << " partitions" << endl;
    cout << endl;

    // ---- Example 4: "abc" (no multi-char palindromes) ----
    char s4[] = "abc";
    int len4 = 3;
    char parts4[MAX_LEN][MAX_LEN];

    cout << "--- Partition \"" << s4 << "\" ---" << endl;
    partitionCount = 0;
    partitionPalindrome(s4, len4, 0, parts4, 0);
    cout << "Total: " << partitionCount << " partitions" << endl;
    cout << endl;

    cout << "Backtracking approach:" << endl;
    cout << "  1. Start at index 0 of the string" << endl;
    cout << "  2. Try every possible ending index i (from idx to len-1)" << endl;
    cout << "  3. Check if s[idx..i] is a palindrome" << endl;
    cout << "  4. If yes: include s[idx..i] in partition, recurse on s[i+1..]" << endl;
    cout << "  5. When idx == len: entire string is partitioned, record result" << endl;
    cout << "  6. Backtrack: try next ending index i" << endl;
    cout << endl;
    cout << "The palindrome check is the CONSTRAINT that prunes invalid splits." << endl;
    cout << "Only palindrome prefixes are explored further." << endl;

    return 0;
}
