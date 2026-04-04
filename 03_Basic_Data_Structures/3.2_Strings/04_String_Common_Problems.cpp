/*
 * File: 04_String_Common_Problems.cpp
 * Topic: Common string problems - palindrome, anagram, reverse
 * Description: Frequently asked string interview questions
 */
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

// Check if string is palindrome
bool isPalindrome(string s) {
    int left = 0;
    int right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Check if two strings are anagrams
bool areAnagrams(string s1, string s2) {
    if (s1.length() != s2.length()) {
        return false;
    }

    // Sort both and compare
    // Alternative: use frequency array for O(n)
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    return true;
}

// Count vowels and consonants
void countVowelsConsonants(string s) {
    int vowels = 0;
    int consonants = 0;

    for (int i = 0; i < s.length(); i++) {
        char c = tolower(s[i]);
        if (c >= 'a' && c <= 'z') {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    cout << "  Vowels: " << vowels << endl;
    cout << "  Consonants: " << consonants << endl;
}

// Reverse words in a sentence
string reverseWords(string s) {
    // First reverse entire string
    reverse(s.begin(), s.end());

    // Then reverse each word
    int start = 0;
    for (int i = 0; i <= s.length(); i++) {
        if (i == s.length() || s[i] == ' ') {
            // Reverse word from start to i-1
            int end = i - 1;
            while (start < end) {
                char temp = s[start];
                s[start] = s[end];
                s[end] = temp;
                start++;
                end--;
            }
            start = i + 1;
        }
    }
    return s;
}

int main() {
    cout << "=== Common String Problems ===" << endl;
    cout << endl;

    // --- Palindrome ---
    cout << "--- Palindrome Check ---" << endl;
    string words[] = {"madam", "hello", "racecar", "abcba"};
    int n = 4;

    for (int i = 0; i < n; i++) {
        if (isPalindrome(words[i])) {
            cout << "  \"" << words[i] << "\" -> Palindrome" << endl;
        } else {
            cout << "  \"" << words[i] << "\" -> Not palindrome" << endl;
        }
    }

    cout << endl;

    // --- Anagram ---
    cout << "--- Anagram Check ---" << endl;
    string a1 = "listen";
    string a2 = "silent";
    cout << "  \"" << a1 << "\" and \"" << a2 << "\": " << (areAnagrams(a1, a2) ? "Anagrams" : "Not anagrams") << endl;

    string b1 = "hello";
    string b2 = "world";
    cout << "  \"" << b1 << "\" and \"" << b2 << "\": " << (areAnagrams(b1, b2) ? "Anagrams" : "Not anagrams") << endl;

    cout << endl;

    // --- Vowels and Consonants ---
    cout << "--- Count Vowels and Consonants ---" << endl;
    string sentence = "Hello World";
    cout << "  \"" << sentence << "\"" << endl;
    countVowelsConsonants(sentence);

    cout << endl;

    // --- Reverse Words ---
    cout << "--- Reverse Words in Sentence ---" << endl;
    string sent = "I love coding";
    cout << "  Before: \"" << sent << "\"" << endl;
    cout << "  After:  \"" << reverseWords(sent) << "\"" << endl;

    cout << endl;
    cout << "--- Key Techniques ---" << endl;
    cout << "Palindrome:    Two pointers from both ends" << endl;
    cout << "Anagram:       Sort both strings, then compare" << endl;
    cout << "Vowels:        Check each char against a,e,i,o,u" << endl;
    cout << "Reverse words: Reverse entire string, then reverse each word" << endl;

    return 0;
}
