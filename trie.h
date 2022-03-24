// Copyright [2022] <Tulio Bardini e Patricia Arigoni>

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H
#define ALPHABET_SIZE 26

#include <string>


namespace structures { 

class Trie {
 public:
  Trie(); //
  void insert(std::string word, int index, int length);
  int getIndex(std::string word);
  int getLength(std::string word);
  int prefixCounter(std::string word);
  int childrenCounter();
  int wordCounter();

 private:
    Trie* children[ALPHABET_SIZE];
    int index;
    int length;
    bool leaf;
};

}  // namespace structures

#endif

//  No novo Trie o index que é a posição e o lenght que é o comprimento vão 
//  ser definidos inicialmente como 0 e as posições de children que 
//  são os nodos filhos são  nulos

structures::Trie::Trie() {
    index = 0;
    length = 0;
    leaf = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
}
// Vai adicionar uma chave na árvore, word é a palavra a ser inserida, 
// o index a posição no dicionario da palavra a ser inserida, e o lenght o 
//comprimento da linha do dicionario que possui a palavra a ser inserida.

void structures::Trie::insert(std::string word, int index, int length) {
    auto current = this;
    for (int i = 0; i < word.length(); i++) {
        int position = word[i] - 'a';
        if (current->children[position] == NULL) {
            current->children[position] = new Trie;
        }
        current = current->children[position];
    }
    current->index = index;
    current->length = length;
    current->leaf = true;
}

int structures::Trie::getIndex(std::string word) {
    auto current = this;
    for (int i = 0; i < word.length(); i++) {
        int position = word[i] - 'a';
        if (current->children[position] == nullptr) {
            return -1;
        }
        current = current->children[position];
    }
    
    return current->index;
}

int structures::Trie::getLength(std::string word) {
    auto current = this;
    for (int i = 0; i < word.length(); i++) {
        int position = word[i] - 'a';
        if (current->children[position] == nullptr) {
            return -1;
        }
        current = current->children[position];
    }
    
    return current->length;
}


// Conta o número de vezes que a palavra é prefixo, 
//o word é a palavra a ser contada, 
//ele ira retornar um número inteiro com as vezes que a palavra foi prefixo

int structures::Trie::prefixCounter(std::string word) {
    auto current = this;
    int prefixCount = 0;
    for (int i = 0; i < word.length(); i++) {
        int position = word[i] - 'a';
        if (current->children[position] == NULL) {
            return 0;
        }
        current = current->children[position];
    }
    if (current) {
        if (current->leaf) {
            prefixCount++;
        } else {
            prefixCount += current->wordCounter();
        }
    }
    return prefixCount;
}

//  Conta o número de filhos, e retorna um inteiro sendo ele o número de filhos

int structures::Trie::childrenCounter() {
    auto current = this;
    int childrenCount = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i]) {
            childrenCount++;
        }
    }
    return childrenCount;
}
//  Conta o número de palavras a partir do nodo, e retorna um número inteiro 
//  com a quantidade de palavras.

int structures::Trie::wordCounter() {
    int wordCount = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (children[i]) {
            if (children[i]->leaf) {
                wordCount++;
            } else {
                wordCount += children[i]->wordCounter();
            }
        }
    }
    return wordCount;
}