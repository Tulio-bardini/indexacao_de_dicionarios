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
    int index_count = 0;

    while (getline(file, line)) {

        string dic_word = line.substr(1, line.find_first_of(']') - 1);

        trie.inserir(dic_word, index_count, line.length());
        
        index_count += line.length() + 1;
    }

    file.close();

    string word;
    pair<int, int> pair;
    while (1) {
        cin >> word;

        if (word.compare("0") == 0) {
            break;
        }

        pair = trie.procurar(word);
        
        if (pair.first  == 0 && pair.second == 0) {
            int n = trie.n_prefixo(word);
            cout << word << " is prefix of " << n << " words" << endl;
        } else if (pair.first  == -1) {
            cout << word << " is not prefix" << endl;
        } else {
            int n = trie.n_prefixo(word);
            int d = pair.first;
            int c = pair.second;
            cout << word << " is prefix of " << n << " words" << endl;
            cout << word << " is at (" << d << "," << c << ")" << endl;
        }
    }
    return 0;
}