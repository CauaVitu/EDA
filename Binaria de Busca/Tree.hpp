#ifndef TREE_HPP
#define TREE_HPP
#include "Node.hpp"
#include <queue>

using namespace std;
class Tree {
public:
    // Construtor: cria uma arvore vazia
    Tree() {
        m_root = nullptr;
    }
    // Função publica que insere a chave
    void insert(int v) {
        m_root = _insert(m_root, v);
    }
    // Funcao publica: libera os nodos da arvore
    void clear() {
        m_root = clear(m_root);
    }
    // Destrutor
    ~Tree() {
        m_root = clear(m_root);
    }
    // Imprime a arvore num formato amigavel
    void show() {
        show(m_root, "");
    }

    void BFS() {
        BFS(m_root);
}

    // Funcao publica que recebe uma chave e retorna true se 
    // e somente se a chave estiver na arvore. 
    bool contains(int k) {
        Node *aux = contains(m_root, k);
        return aux != nullptr;
    }

    // Funcao iterativa publica que recebe uma chave 
    // e retorna true se e somente se a chave estiver na arvore 
    bool contains_iterativo(int k) {
        Node* nodo_atual = m_root;
        while(nodo_atual != nullptr) {
            if(nodo_atual->key == k) {
                return true;
            }
            if(k < nodo_atual->key)
                nodo_atual = nodo_atual->left;
            else 
                nodo_atual = nodo_atual->right;
        }
        return false;
    }

    // Funcao que remove uma chave da arvore se ele existir
    void remove(int k) {
        m_root = _remove(m_root, k);
    }

    void pre() {
        bool first = true;
        pre(m_root,first);
    }

    void in() {
        bool first = true;
        in(m_root,first);
    }

    void pos(){
    bool first = true;    
    pos(m_root,first);
}

private:
    // ponteiro para a raiz da arvore
    Node* m_root;   

    // Funcao privada recrusiva 
    // que insere um nodo na arvore
    Node* _insert(Node* node, int k) {
        if (node == nullptr){
            return new Node(k, nullptr, nullptr);
        } else if (k < node->key){
            node->left = _insert(node->left, k);
        } else if (k > node->key){
            node->right = _insert(node->right, k);
        }
        return node;
    }

    // Funcao recursiva privada que recebe a raiz 
    // de uma arvore e garante que todos os descendentes 
    // dessa raiz e a propria raiz sejam liberados 
    // para a memoria.
    // Retorna nullptr indicando que a arvore ficou vazia.
    Node* clear(Node* node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }        
        return nullptr;
    }

    // Versão alternativa da funcao de liberar nodos
    void _clear(Node* node) {
        if(node != nullptr) {  
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void show(Node *node, std::string heranca) {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            show(node->right , heranca + "r");
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
            show(node->left, heranca + "l");
    }

    // Função recursiva privada que recebe a raiz de uma arvore,
    // e uma chave k e retorna o ponteiro para o nói que contém a
    // chave se a chave estiver na arvore; caso contrario, ela
    // retorna nulo.
    Node* contains(Node* node, int k) {
        // Caso de parada: achei ou não achei a chave
        if(node == nullptr || node->key == k) {
            return node;
        }
        // Caso geral: ainda nao achei 
        // e ainda tem arvore para percorrer
        if(k < node->key)
            return contains(node->left, k);
        else 
            return contains(node->right, k);
    }

    // Funcao privada recursiva que busca a chave a ser removida
    Node* _remove(Node* node, int k) {
        if(node == nullptr)
            return nullptr;
        if(node->key == k) 
            return _remove_node(node);
        if(k < node->key)
            node->left = _remove(node->left, k);
        else 
            node->right = _remove(node->right, k);
        return node;
    }

void in(Node* a, bool& first) {
    if (a == nullptr) return;
    in(a->left, first);
    if (!first) cout << " ";
    cout << a->key;
    first = false;
    in(a->right, first);
}

void pre(Node* a, bool& first) {
    if (a == nullptr) return;

    if (!first) cout << " ";
    cout << a->key;
    first = false;
    pre(a->left, first);
    pre(a->right, first);
}

void pos(Node* a, bool& first) {
    if (a == nullptr) return;

    pos(a->left, first);
    pos(a->right, first);
    if (!first) cout << " ";
    cout << a->key;
    first = false;
}

    void BFS(Node* node){
        queue <Node*> q;
        q.push(node);
        Node* atual;
        while(q.empty() != true){
        atual = q.front();
        cout << atual->key;
        q.pop();
        if (atual->left != nullptr) q.push(atual->left);
        if (atual->right != nullptr) q.push (atual->right);
        if (q.empty() != true) cout << " ";
        }
    }


    // Funcao privada iterativa que remove o nodo passado como parametro.
    // Essa funcao considera os dois casos da remocao: ou o nodo tem 
    // filho direito ou nao tem filho direito. 
    Node* _remove_node(Node *node) {
        Node *pai, *q;
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