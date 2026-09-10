#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

string readFile(const string& filename);

// ==================== Part 1: Pattern search ====================
bool findPattern(const string& text, const string& pattern, int& startPos);

// ==================== Part 2: Longest palindromic substring ====================
pair<int, int> longestPalindrome(const string& text);

// ==================== Part 3: Longest common substring ====================
pair<int, int> longestCommonSubstring(const string& a, const string& b);

int main() {
    // EJEMPLOS, CAMBIAR POR LOS ARCHIVOS DE TRANSMISIONES Y MCODES QUE SEAN NECESARIOS
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
    cout << lcs.first << " " << lcs.second << "\n";

    return 0;
}

string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        return "";
    }
    string content, line;
    while (getline(file, line)) {
        content += line; 
    }
    return content;
}

bool findPattern(const string& text, const string& pattern, int& startPos) {
    
}

pair<int, int> longestPalindrome(const string& text) {

}

pair<int, int> longestCommonSubstring(const string& a, const string& b) {

}