#ifndef NODE_HPP
#define NODE_HPP
#include<iostream>

template<typename T>
// Esse cara aqui vai ser o Node tanto da AVL quanto da RBTree
// Ele vai armazenar a chave, a altura, os filhos e o pai
// Também vai ter a cor da Arvore Rubro-Negra ( true for RED, false for BLACK)
// E tem height para a AVL, que é a altura do nó na árvore AVL
struct Node {
    T key;
    T value; // Valor associado à chave (opcional, mas será util para não precisar criar um par)
    int height;
    Node* left;
    Node* right;
    Node* p;
    bool color; // true for RED, false for BLACK
    

    // Construtor
    Node (T k, int height, Node* l, Node* r,Node* p = nullptr,bool c = true) {
        key = k;
        this->height = height;
        left = l;
        right = r;
        color = c;
        this->p = p;
    }
    
};

#endif