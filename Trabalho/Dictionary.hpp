#include "Node.hpp"

template <typename T,typename U>
class Dictionary {
public:
    // Estruturas internas
    ChainedHash<T,U> chained_hash;
    OpenHash<T,U> open_hash;
    AVL<pair<T,U>> avl;
    RBTree<pair<T,U>> rbtree;
    int structureType;

    // Novo enum
    enum structureTypes {
        AVL_TYPE,
        RBTREE_TYPE,
        OPENHASH_TYPE,
        CHAINEDHASH_TYPE
    };

    Dictionary(int structureType) {
        this->structureType = structureType;
    }

    Dictionary(int structureType , std::vector<pair<T,U>> pairs) {
        this->structureType = structureType;
        for (const auto& i : pairs) {
            insert(i.first, i.second);
        }
    }

    bool insert(const T& key, const U& value) {
        switch (structureType) {
            case AVL_TYPE:
                avl.insert({key, value});
                return true;
            case RBTREE_TYPE:
                rbtree.insert({key, value});
                return true;
            case OPENHASH_TYPE:
                open_hash.insert(key, value);
                return true;
            case CHAINEDHASH_TYPE:
                chained_hash.insert(key, value);
                return true;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    bool contains(const T& key) {
        switch (structureType) {
            case AVL_TYPE:
                return avl.contains({key, U()});
            case RBTREE_TYPE:
                return rbtree.contains({key, U()});
            case OPENHASH_TYPE:
                return open_hash.contains(key);
            case CHAINEDHASH_TYPE:
                return chained_hash.contains(key);
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    void remove (T key){
        switch (structureType) {
            case AVL_TYPE:
                avl.remove({key, U()});
                break;
            case RBTREE_TYPE:
                rbtree.remove({key, U()});
                break;
            case OPENHASH_TYPE:
                open_hash.remove(key);
                break;
            case CHAINEDHASH_TYPE:
                chained_hash.remove(key);
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
                break;
        }
    }

    void clear (){
        switch(structureType) {
            case AVL_TYPE:
                avl.clear();
                break;
            case RBTREE_TYPE:
                rbtree.clear();
                break;
            case OPENHASH_TYPE:
                open_hash.clear();
                break;
            case CHAINEDHASH_TYPE:
                chained_hash.clear();
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    size_t size () const{
        switch(structureType) {
            case AVL_TYPE:
                return avl.size();
            case RBTREE_TYPE:
                return rbtree.size();
            case OPENHASH_TYPE:
                return open_hash.size();
            case CHAINEDHASH_TYPE:
                return chained_hash.size();
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    int get_comparison_counter() const {
        switch(structureType) {
            case AVL_TYPE:
                return avl.get_comparison_counter();
            case RBTREE_TYPE:
                return rbtree.get_comparison_counter();
            case OPENHASH_TYPE:
                return open_hash.get_comparison_counter();
            case CHAINEDHASH_TYPE:
                return chained_hash.get_comparison_counter();
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
    }

    int get_rotations_counter() const {
        switch(structureType) {
            case AVL_TYPE:
                return avl.get_rotations_counter();
            case RBTREE_TYPE:
                return rbtree.get_rotations_counter();
            default:
                throw std::invalid_argument("Only trees have rotations");
        }
    }

    int get_colision_counter() const {
        switch(structureType) {
            case OPENHASH_TYPE:
                return open_hash.get_colision_counter();
            case CHAINEDHASH_TYPE:
                return chained_hash.get_colision_counter();
            default:
                throw std::invalid_argument("Only hash tables have collisions");
        }
    }

    U& access (T& key){
        switch(structureType) {
            case AVL_TYPE:{
                auto* aux = avl.at({key, U()});
                if (aux)
                    return aux->key.second;
                else
                    throw std::out_of_range("Key not found in AVL tree");
                break;
            }
            case RBTREE_TYPE:{
                auto* aux = rbtree.at({key, U()});
                if (aux)
                    return aux->key.second;
                else{
                    throw std::out_of_range("Key not found in Red-Black tree");
                    break;
                }
            }
            case OPENHASH_TYPE:
                return open_hash.at(key);
                break;
            case CHAINEDHASH_TYPE:
                return chained_hash.at(key);
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
                break;
        }
    }

    void update (const T& key,const U& value){
        switch(structureType) {
            case AVL_TYPE:{
                auto* aux = avl.at({key, U()});
                if (aux) {
                    aux->key.second = value;
                } else {
                    throw std::out_of_range("Key not found in AVL tree");                    
                }
                break;
            }
            case RBTREE_TYPE:{
                auto* aux = rbtree.at({key, U()});
                if (aux){
                    aux->key.second = value;
                } else {
                    throw std::out_of_range("Key not found in Red-Black tree");
                }
                break;
            }
            case OPENHASH_TYPE:
                open_hash[key] = value;
                break;
            case CHAINEDHASH_TYPE:
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
            case AVL_TYPE:
                result = avl.iterate();
                break;
            case RBTREE_TYPE:
                result = rbtree.iterate();
                break;
            case OPENHASH_TYPE:
                result = open_hash.iterate();
                break;
            case CHAINEDHASH_TYPE:
                result = chained_hash.iterate();
                break;
            default:
                throw std::invalid_argument("Structure type must be in the defined range");
        }
        return result;
    }

private:
    
};
