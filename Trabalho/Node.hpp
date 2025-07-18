#ifndef NODE_HPP
#define NODE_HPP
#include<iostream>

template<typename T>
// Deveria ser um nó global, mas eu fiquei com preguiça de usar na Rubro-Negra
// reliquia de quando eu tinha a ambição de fazer um nó genérico
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