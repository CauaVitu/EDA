#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include "Node.hpp"
using namespace std;

enum Color { RED, BLACK };

template<typename T>
class RBTree {
private:
    struct Node {
        T key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(T k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
   
    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
        rotations_counter++; // Incrementa o contador de rotações
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
        rotations_counter++; // Incrementa o contador de rotações
    }

    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            comparison_counter++; // Incrementa o contador de comparações
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    comparison_counter++;
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (!u->parent)
            root = v;
        else if (u == u->parent->left){
            comparison_counter++;
            u->parent->left = v;
        }
        else
            u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    void fixDelete(Node* x) {
        while (x != root && (!x || x->color == BLACK)) {
            comparison_counter++; // Incrementa o contador de comparações
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if ((!w->left || w->left->color == BLACK) &&
                    (!w->right || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (!w->right || w->right->color == BLACK) {
                        if (w->left) w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right) w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w && w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if ((!w->right || w->right->color == BLACK) &&
                    (!w->left || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (!w->left || w->left->color == BLACK) {
                        if (w->right) w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left) w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x) x->color = BLACK;
    }

    Node* search(Node* node, T key) {
        if (!node || node->key == key){
            comparison_counter++;
            return node;
        }   
        if (key < node->key){
            comparison_counter++;
            return search(node->left, key);
        }
        else
            return search(node->right, key);
    }


    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void bshow(Node* node, std::string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << (node->color == RED ? "(R)" : "(B)") << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

public:
     mutable int comparison_counter = 0; // Contador de comparações
     int rotations_counter = 0; // Contador de rotações

    int get_rotations_counter() const {
        return rotations_counter;
    }

     get_comparison_counter() const {
        return comparison_counter;
    }
    RBTree() : root(nullptr) {}
    ~RBTree() { destroy(root); }

    void insert(T key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (z->key < x->key){
                comparison_counter++; // Incrementa o contador de comparações
                x = x->left;
            }
            else
                x = x->right;
        }

        z->parent = y;
        if (!y)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    void remove(T key) {
        Node* z = search(root, key);
        if (!z) return;

        Node* y = z;
        Node* x = nullptr;
        Color yOriginalColor = y->color;

        if (!z->left) {
            x = z->right;
            transplant(z, z->right);
        } else if (!z->right) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                comparison_counter++;
                if (x) x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left) y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        if (yOriginalColor == BLACK && x)
            fixDelete(x);
    }

    bool contains(T key) {
        return search(root, key) != nullptr;
    }

void show() const {
        bshow(root, "");
    }
};

#endif
