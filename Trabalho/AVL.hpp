    #ifndef AVL_HPP
    #define AVL_HPP
    #include "Node.hpp"
    #include "Comparator.hpp"
    #include <algorithm>
    #include <iostream>
    #include <string>
    #include <vector>

    // Nós usaremos essa estrutura para o dicionário, já que precisaremos 
    // usar pairs e não consegui pensar em uma forma de lidar com eles internamente sem forçar
    // a estrutura a ser de um tipo especifico.



    // Classe template para a árvore AVL
    template <typename T>
    class AVL {
    public:
        // Construtor: inicializa a raiz como nula
        AVL() {
            m_root = nullptr;
        }

        int size() const {
            return size(m_root);
        }

        // Chama a função recursiva para iterar sobre a árvore
        std::vector<T> iterate() {
            std::vector<T> result;
            iterate(m_root, result);
            return result;
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
            Node<T> *aux = search(m_root, k);
            return aux != nullptr;
        }

        // Busca um nó na árvore recursivamente
        // Usamos nosso comparador para checar igualdade
        //  if (!cmp(node->key, k) && !cmp(k, node->key)) é o mesmo que dizer if node->key == k
        // mas nosso comparador permite que usemos tuplas ou tipos comuns
        Node<T>* search(Node<T>* node, const T& key) const {
            Comparator<T> cmp;
            if (!node || (!cmp(node->key, key) && !cmp(key, node->key))) {
                comparison_counter+=2;
                return node;
            }
            if (cmp(key, node->key)) {
                comparison_counter++;
                return search(node->left, key);
            } else {
                return search(node->right, key);
            }
        }

        // Busca um valor na árvore
        Node<T>* at(T k) const {
            return search(m_root, k);
        }
        
        // Remove um valor da árvore
        void remove(const T& k) {
            m_root = _remove(m_root, k);
        }

        // Retorna o número de comparações realizadas
        int get_comparison_counter() const {
            return comparison_counter;
        }
        // Retorna o número de rotações realizadas
        int get_rotations_counter() const {
            return rotations_counter;
        }

    private:
        // Mutable pois precisei poder modificar em funções const
        mutable int comparison_counter = 0; // Contador de comparações
        mutable int rotations_counter = 0;
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

        size_t size(Node<T>* node) const {
            if (node == nullptr) return 0;
            return 1 + size(node->left) + size(node->right);
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
        // Usamos nosso comparador para checar igualdade
        //  if (!cmp(node->key, k) && !cmp(k, node->key)) é o mesmo que dizer if node->key == k
        // mas nosso comparador permite que usemos tuplas ou tipos comuns
        Node<T>* _insert(Node<T>* node, const T& k) {
            Comparator<T> cmp;
            if (node == nullptr){
                return new Node<T>(k, 1, nullptr, nullptr);
            } 
            if (!cmp(node->key, k) && !cmp(k, node->key)) {
                comparison_counter+=2;
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
        // Lidamos com os casos de rotação simples e dupla
        // e atualizamos a altura do nó
        Node<T>* fixup_node(Node<T>* node, const T& k) {
            Comparator<T> cmp;
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

        // Função recursiva que visita todos os nós da árvore 
        // e os adiciona a um vetor.
        void iterate(Node<T>* node, std::vector<T>& result) const {
            if (node != nullptr) {
                iterate(node->left, result);
                result.push_back(node->key);
                iterate(node->right, result);
            }
    }

        // Exibe a árvore de forma visual no console
        // (depreciado no caso do uso como dicionário)
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




        // Função recursiva para remover um valor da árvore
        Node<T>* _remove(Node<T>* node, const T& k) {
            Comparator<T> cmp;
            if (node == nullptr)
                return nullptr;
            if (!node || (!cmp(node->key, k) && !cmp(k, node->key))) {
                comparison_counter+=2;
                _remove_node(node);
                return nullptr;
            }
            if (cmp(k, node->key)) {
                comparison_counter++;
                node->left = _remove(node->left, k);;
            } else {
                node->right = _remove(node->right, k);
            }
            // Rebalanceio após remoção
            if (node != nullptr) {
                node = fixup_node(node, k);
            }
            return node;
        }

        // Remove o nó e rearranja os ponteiros
        void _remove_node(Node<T> *node) {
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
        }
    };

    #endif
