// Copyright [2022] <Tulio Bardini e Patrícia Arigoni>

#include <iostream>
#include <fstream>
#include <string>
#include "trie.h"


int main() {

    using namespace std;
    using namespace structures;

    string filename;
    ifstream file;

    cin >> filename;

    file.open(filename);

    if (!file.is_open()) {
        cout << "Could not open the file\n";
        return -1;
    }

    Trie trie;
    string line;
    int indexCount = 0;

    while (getline(file, line)) {

        string dicWord = line.substr(1, line.find_first_of(']') - 1);

        trie.insert(dicWord, indexCount, line.length());
        
        indexCount += line.length() + 1;
    }

    file.close();

    string word;
    while (1) {
        cin >> word;

        if (word.compare("0") == 0) {
            break;
        }

        int count = trie.prefixCounter(word);

        if (count > 0) {
            cout << word << " is prefix of " << count << " words" << endl;

            if (count == 1) {
                cout << word << " is at (" << trie.getIndex(word) << "," << trie.getLength(word) << ")" << endl;
            }

        } else {
            cout << word << " is not prefix" << endl;
        }
    }
    return 0;
}
