// lab1_Ceaser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//latin 26 symb

#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>
#include <fstream>

using namespace std;

string readFile() {
    ifstream inputFile("D:/filename.txt");
    string content;

    if (!inputFile) { 
        cout << "File Error" << endl;
        return ""; 
    }

    char c;
    while (inputFile.get(c)) {
        content += c;
    }

    inputFile.close();
    return content; 
}

char compare(float target, map<char, float> alp) {

    char closest = '/0';
    float min = 1000000000.0;

    for (const auto& pair : alp) {
        float diff = abs(pair.second - target);
        if (diff < min) {
            min = diff;
            closest = pair.first;
        }
    }
    return closest;
}

char max_count(map<char, float>& sym) {
    char max_сhar = '\0'; 
    int max_сount = 0;   
    for (const auto& pair : sym) {
        if (pair.second > max_сount) {
            max_сount = pair.second;   
            max_сhar = pair.first;     
        }
    }
    return max_сhar;
}

map<char, float> symbol_count(string text) {
    map<char, float> sym;
    for (int i = 0; i < text.length(); i++) {
        sym[tolower(text[i])]++;
    }
    for (auto& pair : sym) {
        pair.second = pair.second * 100 / float(text.length());
    }
    return sym;
}

string decrypt_frq(string secret_text, map<char, float> alp) {
    map<char, float> sym = symbol_count(secret_text);
    for (auto& pair : sym) {
        cout << pair.first << " " << pair.second << " " << compare(pair.second, alp) << endl;
    }
    char space = max_count(sym);
    for (int i = 0; i < secret_text.length(); i++) {
        if (secret_text[i] == space) {
            secret_text[i] = ' ';
            continue;
        }
        secret_text[i] = compare(sym[secret_text[i]], alp);
    }
    return secret_text;
}

string encrypt(string open_text, int key) {
    int length = open_text.length();
    for (int i = 0; i < length; i++) {
        int x = int(open_text[i]) - 97;
        int y = x + key % 26;
        open_text[i] = char(y + 97);
    }
    return open_text;
}

string decrypt(string secret_text, int key) {
    
    for (int i = 0; i < secret_text.length(); i++) {
        
        int y = int(secret_text[i]) - 97;
        int x = y - key % 26;
        char s = char(x + 97);
        
        secret_text[i] = s;
    }
    return secret_text;
}

int main()
{
    //string open_text = "abcdefghijklmnosq";
    string open_text = readFile();
    int key = rand() % 26;
    map<char, float> count = symbol_count(open_text);

    string secret_text = encrypt(open_text, key);
    //string decrypted_text = decrypt(secret_text, key);

    string decrypted_text_frq = decrypt_frq(secret_text, count);

    for (int i = 0; i < secret_text.length(); i++) {
        cout << decrypted_text_frq[i];
    }
}
