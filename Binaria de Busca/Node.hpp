#ifndef NODE_HPP
#define NODE_HPP
#include<iostream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node (int k, Node* l, Node* r) {
        key = k;
        left = l;
        right = r;
    }

    ~Node() {
    } 
};

#endif