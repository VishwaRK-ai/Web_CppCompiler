#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

// --- ESSENTIAL STRING TOOLS ---

// 1. Palindrome Check (Classic)
inline bool is_palindrome(const string &s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

// 2. Subsequence Check (Is 'sub' hidden inside 'main'?)
// Example: "ace" is a subsequence of "abcde" -> True
inline bool is_subsequence(const string &sub, const string &main) {
    int i = 0, j = 0;
    while (i < sub.length() && j < main.length()) {
        if (sub[i] == main[j]) i++;
        j++;
    }
    return i == sub.length();
}

// 3. Join Vector (Python style: ",".join(vec))
// Turns {"a", "b", "c"} -> "a,b,c"
inline string join(const vector<string> &v, string delim) {
    if (v.empty()) return "";
    string res = v[0];
    for (size_t i = 1; i < v.size(); i++) res += delim + v[i];
    return res;
}

// 4. Repeat String (Python style: "abc" * 3)
inline string repeat(string s, int n) {
    string res = "";
    while (n--) res += s;
    return res;
}

// 5. Count Specific Character
inline int count_char(const string &s, char c) {
    return count(s.begin(), s.end(), c);
}

// 6. Case Conversion
inline string to_upper(string s) {
    for(auto &c : s) c = toupper(c);
    return s;
}

inline string to_lower(string s) {
    for(auto &c : s) c = tolower(c);
    return s;
}

// 7. Split (Python style)
inline vector<string> split(const string &s, char delim) {
    vector<string> res;
    string token;
    istringstream ss(s);
    while (getline(ss, token, delim)) res.push_back(token);
    return res;
}