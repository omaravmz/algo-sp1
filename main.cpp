#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

// --------------- FUNCTION DECLARATIONS ---------------

string readFile(const string& filename);

// ==================== Part 1: Pattern search ====================
bool findPattern(const string& text, const string& pattern, int& startPos);

// ==================== Part 2: Longest palindromic substring ====================
pair<int, int> longestPalindrome(const string& text);
string transform(const string& text);

// ==================== Part 3: Longest common substring ====================
pair<int, int> longestCommonSubstring(const string& a, const string& b);

// --------------- MAIN ---------------

int main() {
    const string transmission1File = "transmission1.txt";
    const string transmission2File = "transmission2.txt";
    const string mcodeFiles[3] = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

    string transmission1 = readFile(transmission1File);
    string transmission2 = readFile(transmission2File);
    string mcodes[3];
    for (int i = 0; i < 3; i++) {
        mcodes[i] = readFile(mcodeFiles[i]);
    }

    // ---------- Part 1 ----------
    string transmissions[2] = {transmission1, transmission2};
    for (int t = 0; t < 2; t++) {
        for (int m = 0; m < 3; m++) {
            int startPos = -1;
            bool found = findPattern(transmissions[t], mcodes[m], startPos);
            if (found) {
                cout << "true " << startPos << "\n";
            } else {
                cout << "false" << "\n";
            }
        }
    }

    // ---------- Part 2 ----------
    pair<int, int> pal1 = longestPalindrome(transmission1);
    pair<int, int> pal2 = longestPalindrome(transmission2);
    cout << pal1.first << " " << pal1.second << "\n";
    cout << pal2.first << " " << pal2.second << "\n";
    

    // ---------- Part 3 ----------
    pair<int, int> lcs = longestCommonSubstring(transmission1, transmission2);
    if (lcs.second == 0){
        cout << "No common substring found..." << "\n";
    } else {
        cout << lcs.first << " " << lcs.second << "\n";
    }

    return 0;
}

// --------------- FUNCTIONS IMPLEMENTATIONS ---------------

string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        return "";
    }

    string content, line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        content += line;
    }
    return content;
}

vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);   

    int length = 0;   
    int i = 1;           

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length = length + 1;
            lps[i] = length;
            i = i + 1;
        } else {
            if (length != 0) {
                length = lps[length - 1]; 
            } else {
                lps[i] = 0;
                i = i + 1;
            }
        }
    }

    return lps;
}

bool findPattern(const string& text, const string& pattern, int& startPos) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps = buildLPS(pattern);

    int i = 0;
    int j = 0;
    
    while(i < n){
        if (text[i]  == pattern[j]){
            i++;
            j++;
            if(j==m){
                startPos = i + 1 - j;
                return true;
            }
        } else {
            if (j !=0){
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

pair<int, int> longestPalindrome(const string& text) {
    string transformed = transform(text);
    int n = transformed.size();
    vector<int> p(n, 0);
    
    int center = 0;
    int right = 0;
    int maxLen = 0;
    int centerIndex = 0;

    for (int i = 1; i < n; i++) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        else {
            p[i] = 0;
        }

        while (i + 1 + p[i] < n && i - 1 - p[i] >= 0 && transformed[i + 1 + p[i]] == transformed[i - 1 - p[i]]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > maxLen) {
            maxLen = p[i];
            centerIndex = i;
        }

    }

    int start = (centerIndex - maxLen) / 2;
    int end = start + maxLen - 1;

    return maxLen > 0 ? make_pair(start + 1, end + 1) : make_pair(0, 0);
}

string transform(const string& text){
    string transformed = "#";
    for (char c : text) {
        transformed += c;
        transformed += "#";
    }
    return transformed;
}

pair<int, int> longestCommonSubstring(const string& a, const string& b) {
    int n = a.size();
    int m = b.size();

    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);

    int maxLen = 0;
    int endPos = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                curr[j] = prev[j - 1] + 1;
                if (curr[j] > maxLen) {
                    maxLen = curr[j];
                    endPos = i;
                }
            } else {
                curr[j] = 0;
            }
        }
        prev = curr;
    }

    if (maxLen == 0) {
        return {0, 0};
    }

    int startPos = endPos - maxLen + 1;
    return {startPos, endPos};
}