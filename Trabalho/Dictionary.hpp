#include "Node.hpp"

template <typename T,typename U>
class Dictionary {
public:
    // Aqui temos todas as estruturas que implementarão o dicionário
    // Cada uma delas tem suas próprias características e implementações
    // O dicionário é uma abstração que permite usar qualquer uma dessas estruturas

    ChainedHash<T,U> chained_hash;
    OpenHash<T,U> open_hash;
    AVL<pair<T,U>> avl;
    RBTree<pair<T,U>> rbtree;
    int structureType;

    // Definimos os tipos de estruturas que o dicionário pode usar
    // Isso aqui deixa facinho resolver os switches depois
    enum structureTypes {
        AVL,
        RBTREE,
        OPENHASH,
        CHAINEDHASH
    };

    // Construtor padrão, só recebe o tipo de estrutura
    Dictionary(int structureType) {
        this->structureType = structureType;
    }

    // Construtor que recebe o tipo de estrutura e um vetor de pares (chave, valor)
    // (útil para inicializar o dicionário com dados)
    Dictionary(int structureType , std::vector<pair<T,U>> pairs) {
        this->structureType = structureType;
        for (const auto& i : pairs) {
            insert(i.first, i.second);
        }
    }

    // Chamamos o insert de cada estrutura
    bool insert(const T& key, const U& value) {
        switch (structureType) {
            case AVL:
                avl.insert({key, value});
                return true;
            case RBTREE:
                rbtree.insert({key, value});
                return true;
            case OPENHASH:
                open_hash.insert(key, value);
                return true;
            case CHAINEDHASH:
                chained_hash.insert(key, value);
                return true;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    // Chamamos o contains de cada estrutura
    bool contains(const T& key) {
        switch (structureType) {
            case AVL:
                return avl.contains({key, U()}); // In the case of a frequency dictionary, U = int and U() is 0;
            case RBTREE:
                return rbtree.contains({key, U()});
            case OPENHASH:
                return open_hash.contains(key);
            case CHAINEDHASH:
                return chained_hash.contains(key);
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    // Chamamos o remove de cada estrutura
    void remove (T key){
        switch (structureType) {
            case AVL:
                avl.remove({key, U()}); // In the case of a frequency dictionary, U = int and U() is 0;
                    break;
            case RBTREE:
                rbtree.remove({key, U()});
                break;
            case OPENHASH:
                open_hash.remove(key);
                break;
            case CHAINEDHASH:
                chained_hash.remove(key);
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
                break;
        }
    }


    // Chamamos o clear de cada estrutura
    void clear (){
        switch(structureType) {
            case AVL:
                avl.clear();
                break;
            case RBTREE:
                rbtree.clear();
                break;
            case OPENHASH:
                open_hash.clear();
                break;
            case CHAINEDHASH:
                chained_hash.clear();
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    // Retornamos o tamanho da estrutura em questão
    size_t size () const{
        switch(structureType) {
            case AVL:
                return avl.size();
            case RBTREE:
                return rbtree.size();
            case OPENHASH:
                return open_hash.size();
            case CHAINEDHASH:
                return chained_hash.size();
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    int get_comparison_counter() const {
        switch(structureType) {
            case AVL:
                return avl.get_comparison_counter();
            case RBTREE:
                return rbtree.get_comparison_counter();
            case OPENHASH:
                return open_hash.get_comparison_counter();
            case CHAINEDHASH:
                return chained_hash.get_comparison_counter();
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    int get_rotations_counter() const {
        switch(structureType) {
            case AVL:
                return avl.get_rotations_counter();
            case RBTREE:
                return rbtree.get_rotations_counter();
            default:
                throw std::invalid_argument("Only trees have rotations");
        }
    }

    int get_colision_counter() const {
        switch(structureType) {
            case OPENHASH:
                return open_hash.get_colision_counter();
            case CHAINEDHASH:
                return chained_hash.get_colision_counter();
            default:
                throw std::invalid_argument("Only hash tables have collisions");
        }
    }

    // Acessamos o valor associado a uma chave
    // Nas arvores, usamos o at para buscar o nó
    U& access (T& key){
        switch(structureType) {
            case AVL:{
                auto* aux = avl.at({key, U()});
                if (aux)
                    return aux->key.second;
                else
                    throw std::out_of_range("Key not found in AVL tree");
                break;
            }
                
            case RBTREE:{
                auto* aux = rbtree.at({key, U()});
                if (aux)
                    return aux->key.second;
                else
                    throw std::out_of_range("Key not found in Red-Black tree");
                    break;
            }
            case OPENHASH:
                return open_hash.at(key);
                break;
            case CHAINEDHASH:
                return chained_hash.at(key);
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
                break;
        }
    }

    // Atualizamos o valor associado a uma chave
    // Nas arvores, usamos o at para buscar o nó e então atualizamos o valor
    // Nas tabelas hash, simplesmente atribuímos o novo valor à chave
    void update (const T& key,const U& value){
        switch(structureType) {
            case AVL:{
                auto* aux = avl.at({key, U()});
                if (aux) {
                    aux->key.second = value;
                } else {
                    throw std::out_of_range("Key not found in AVL tree");                    
                }
                break;
            }
            case RBTREE:{
                auto* aux = rbtree.at({key, U()});
                if (aux){
                    aux->key.second = value;
                } else {
                    throw std::out_of_range("Key not found in Red-Black tree");
                }
                break;
            }
                
            case OPENHASH:
                open_hash[key] = value;
                break;
            case CHAINEDHASH:
                chained_hash[key] = value;
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
                break; 
        }
    }

    vector<pair<T,U>> iterate() {
        vector<pair<T,U>> result;
        switch(structureType) {
            case AVL:
                result = avl.iterate();
                break;
            case RBTREE:
                result = rbtree.iterate();
                break;
            case OPENHASH:
                result = open_hash.iterate();
                break;
            case CHAINEDHASH:
               result = chained_hash.iterate();
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
        return result;
    }


private:
    
};