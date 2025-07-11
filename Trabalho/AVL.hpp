#ifndef AVL_HPP
#define AVL_HPP
#include "Node.hpp"
#include <algorithm>
#include <iostream>
#include <string>

// Classe template para a árvore AVL
template <typename T>
class AVL {
public:
    // Construtor: inicializa a raiz como nula
    AVL() {
        m_root = nullptr;
    }

    // Insere um valor na árvore
    void insert(const T& v) {
        m_root = _insert(m_root, v);
    }

    // Remove todos os nós da árvore
    void clear() {
        m_root = clear(m_root);
    }

    // Destrutor: limpa a árvore ao destruir o objeto
    ~AVL() {
        m_root = clear(m_root);
    }

    // Mostra a árvore no console
    void show() {
        bshow(m_root, "");
    }

    // Verifica se um valor está na árvore
    bool contains(const T& k) {
        Node<T> *aux = contains(m_root, k);
        return aux != nullptr;
    }
    
    // Remove um valor da árvore
    void remove(const T& k) {
        m_root = _remove(m_root, k);
    }

    // Retorna o número de comparações realizadas
    int get_comparison_counter() const {
        return comparison_counter;
    }

    int get_rotations_counter() const {
        return rotations_counter;
    }

private:
    int comparison_counter = 0; // Contador de comparações
    int rotations_counter = 0;
    Node<T>* m_root; // Raiz da árvore

    // Retorna a altura de um nó
    int height(Node<T>* node) {
        if(node == nullptr) return 0;
        else return node->height;
    }

    // Calcula o fator de balanceamento de um nó
    int balance(Node<T>* node) {
        return height(node->right) - height(node->left);
    }

    // Rotação simples à direita
    Node<T>* right_rotation(Node<T> *p) {
        Node<T>* u = p->left;
        p->left = u->right;
        u->right = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        rotations_counter++;
        return u;
    }

    // Rotação simples à esquerda
    Node<T>* left_rotation(Node<T>* p) {
        rotations_counter++;
        Node<T>* u = p->right;
        p->right = u->left;
        u->left = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    // Função recursiva para inserir um valor na árvore
    Node<T>* _insert(Node<T>* node, const T& k) {
        std::less<T> cmp;
        if (node == nullptr){
            return new Node<T>(k, 1, nullptr, nullptr);
        } 
        if (node->key == k) {
            comparison_counter++;
            return node;
        }
        if (cmp(k, node->key)){
            comparison_counter++;
            node->left = _insert(node->left, k);
        } else {
            comparison_counter++;
            node->right = _insert(node->right, k);
        }
        node = fixup_node(node, k);
        return node;
    }

    // Corrige o balanceamento do nó após inserção ou remoção
    Node<T>* fixup_node(Node<T>* node, const T& k) {
        std::less<T> cmp;
        int bal = balance(node);
        // Caso de rotação simples à direita
        if(bal == -2 && cmp(k, node->left->key)) {
            comparison_counter++;
            return right_rotation(node);
        }
        // Caso de rotação dupla à direita
        if(bal == -2 && !cmp(k, node->left->key)) {
            comparison_counter++;
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        // Caso de rotação simples à esquerda
        if(bal == 2 && !cmp(k, node->right->key)) {
            comparison_counter++;
            return left_rotation(node);
        }
        // Caso de rotação dupla à esquerda
        if(bal == 2 && cmp(k, node->right->key)) {
            comparison_counter++;
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
        // Atualiza a altura do nó
        node->height = 1 + std::max(height(node->left), height(node->right));
        return node;
    }

    // Remove todos os nós da árvore recursivamente
    Node<T>* clear(Node<T>* node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }        
        return nullptr;
    }

    // Exibe a árvore de forma visual no console
    void bshow(Node<T> *node, std::string heranca) {
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
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    // Busca um valor na árvore
    Node<T>* contains(Node<T>* node, const T& k) {
        std::less<T> cmp;
        if(node == nullptr || node->key == k) {
            comparison_counter++;
            return node;
        }
        if(cmp(k, node->key)){
            comparison_counter++;
            return contains(node->left, k);
        }
        else 
            return contains(node->right, k);
    }

    // Função recursiva para remover um valor da árvore
    Node<T>* _remove(Node<T>* node, const T& k) {
        std::less<T> cmp;
        if(node == nullptr)
            return nullptr;
        if(node->key == k) 
            comparison_counter++;
            return _remove_node(node);
        if(cmp(k, node->key)){
            comparison_counter++;
            node->left = _remove(node->left, k);
        }
        else 
            node->right = _remove(node->right, k);
        return node;
    }

    // Remove o nó e rearranja os ponteiros
    Node<T>* _remove_node(Node<T> *node) {
        Node<T> *pai, *q;
        if(node->right == nullptr) {
            q = node->left;
        }
        else {
            pai = node;
            q = node->right;
            while(q->left != nullptr) {
                pai = q;
                q = q->left;
            }
            if(pai != node) {
                pai->left = q->right;
                q->right = node->right;
            }
            q->left = node->left;
        }
        delete node;
        return q;
    }
};

#endif
