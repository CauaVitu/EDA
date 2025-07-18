#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include "Node.hpp"
#include <vector>
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
   
    // Rotação esquerda
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

    // Rotação direita
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

    // Corrige a árvore após a inserção
    // Mantém as propriedades da árvore rubro-negra
    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
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

    // Transplanta um nó u por um nó v
    // Utilizado na remoção de nós
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

    // Encontra o nó de menor valor na sub-árvore
    // Utilizado na remoção de nós
    Node* minimum(Node* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    // Corrige a árvore após a remoção
    // Mantém as propriedades da árvore rubro-negra
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

    // Busca um nó com a chave especificada recursivamente
    Node* search(Node* node, T key) const{
        Comparator<T> cmp;
        if (!node || (!cmp(node->key, key) && !cmp(key, node->key))) {
            comparison_counter+=2;
            return node;
        }   
        if (cmp(key, node->key)){
            comparison_counter++;
            return search(node->left, key);
        }
        else
            return search(node->right, key);
    }


    // Limpa a árvore recursivamente
    // Deleta todos os nós e retorna nullptr
    Node* clear(Node* node) {
        if (!node) return nullptr;
        clear(node->left);
        clear(node->right);
        delete node;
        return nullptr;
    }

    int size(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + size(node->left) + size(node->right);
    }

    // Exibe a árvore em formato de texto
    // (Depreciado no caso de dicionários por causa do uso de pair)
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

    // Itera recursivamente sobre a arvore e guarda num vector
    vector<T> iterate (Node* node, vector<T>& result){
        if (node) {
            iterate(node->left,result);
            result.push_back(node->key);
            iterate(node->right,result);
        }
        return result;
    }

public:

    
    vector<T> iterate() {
        vector<T> result;
        iterate(root, result);
        return result;
    }

    // Mutable pois precisa ser usado em funções const
    mutable int comparison_counter = 0; // Contador de comparações
    mutable int rotations_counter = 0; // Contador de rotações

    int get_rotations_counter() const {
        return rotations_counter;
    }

    int get_comparison_counter() const {
        return comparison_counter;
    }



    RBTree() : root(nullptr) {}
    ~RBTree() { clear(root); }

    void clear(){
        root = clear(root);
    }

    // Insere um novo nó com a chave especificada
    // Mantém as propriedades da árvore rubro-negra
    void insert(T key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;
        Comparator<T> cmp;
        while (x) {
            y = x;
            if (cmp(z->key, x->key)) {
                comparison_counter++; // Incrementa o contador de comparações
                x = x->left;
            }
            else
                x = x->right;
        }

        z->parent = y;
        if (!y)
            root = z;
        else if (cmp(z->key, y->key))
            y->left = z;
        else
            y->right = z;

        fixInsert(z);
    }

    // Remove o nó com a chave especificada
    // Rebalanceia a árvore se necessário
    // Mantém as propriedades da árvore rubro-negra
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

    // Verifica se a árvore contém um nó com a chave especificada
    bool contains(T key) {
        return search(root, key) != nullptr;
    }
    
    // Retorna o nó com a chave especificada (usado pro update)
    Node* at(T key) const {
        return search(root, key);
    }

    void show() const {
        bshow(root, "");
    }

    int size() const {
        return size(root);
    }
};

#endif
