#ifndef Set_HPP
#define Set_HPP
#include "AVL.hpp"
#include "Node.hpp"
#include <iostream>

using namespace std;

class Set : public AVL {
    // This class implements a set using an AVL tree.
    // It inherits from the AVL class to utilize its functionalities.
    // The set does not allow duplicate elements.
private:
    AVL arvore; // AVL tree to store the set elements
public:
    Set() : arvore() {}

    ~Set() {
        arvore.clear();
    }

    // Add an element to the set
    void insert(int value) {
        AVL::add(value); // Use the AVL class's add method
        // The AVL class already handles duplicates, so we don't need to check for them here.
    }

    // Remove an element from the set
    void erase(int value) {
        if (arvore.contains(value)) {
            arvore.remove(value); // Use the AVL class's remove method
        }
    }

    bool contains(int value) const {
        return AVL::contains(value); // Use the AVL class's contains method
    }

    // Remove an element from the set
    void remove(int value) {
        if (arvore.contains(value)) {
            arvore.remove(value);
        }
    }

    // Check if an element exists in the set
    bool contains(int value) const {
        return arvore.contains(value); // Use the AVL class's contains method
    }

    void clear() {
        arvore.clear(); // Clear the AVL tree
    }

    void swap(Set& other) {
        std::swap(arvore, other.arvore); // Swap the AVL trees
    }

    int minimun() const {
        Node* temp = arvore.root();
        while (temp->left != nullptr) {
            temp = temp->left; // Traverse to the leftmost node
        }

    }

    
};

#endif