// Copyright [2022] <Tulio Bardini e Patricia Arigoni>

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <string>

#define ALPHABET_SIZE 26

namespace structures { 

class Trie {
 public:
  Trie(); //
  void inserir(std::string word, int index, int length);
  int getIndex(std::string word);
  int getLength(std::string word);
  int n_prefixo(std::string word);
  int n_children();
  int n_palavras();

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

void structures::Trie::inserir(std::string word, int index, int length) {
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

int structures::Trie::n_prefixo(std::string word) {
    auto current = this;
    int n_prefix = 0;
    for (int i = 0; i < word.length(); i++) {
        int position = word[i] - 'a';
        if (current->children[position] == NULL) {
            break;
        }
        current = current->children[position];
    }
    if (current) {
        if (current->leaf) {
            n_prefix = n_prefix + 1;
        } else {
            n_prefix += current->n_palavras();
        }
    }
    return n_prefix;
}

//  Conta o número de filhos, e retorna um inteiro sendo ele o número de filhos

int structures::Trie::n_children() {
    auto current = this;
    int n_children = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i]) {
            n_children++;
        }
    }
    return n_children;
}
//  Conta o número de palavras a partir do nodo, e retorna um número inteiro 
//  com a quantidade de palavras.

int structures::Trie::n_palavras() {
    int n_words = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (children[i]) {
            if (children[i]->leaf) {
                n_words++;
            } else {
                n_words += children[i]->n_palavras();
            }
        }
    }
    return n_words;
}