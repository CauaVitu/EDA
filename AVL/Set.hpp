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
        AVL::add(value); // Directly call the AVL class's add method
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

    void clear() {
        arvore.clear(); // Clear the AVL tree
    }

    void swap(Set& other) {
        std::swap(arvore, other.arvore); // Swap the AVL trees
    }

    int minimun(){
        try
        {
            Node* temp = arvore.root();
            cout << "Root: " << temp->key << endl;
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no minimum value.");
            }
            while (temp->left != nullptr) {
                temp = temp->left; // Traverse to the leftmost node
            }
            return temp->key; // Return the minimum value
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1; // Return -1 or handle the error as needed
        }
    }

    int maximum() {
        try
        {
            Node* temp = arvore.root();
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no maximum value.");
            }
            while (temp->right != nullptr) {
                temp = temp->right; // Traverse to the rightmost node
            }
            return temp->key; // Return the maximum value
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1; // Return -1 or handle the error as needed
        }
    }
    
    int sucessor(int value) {
        try
        {
            Node* temp = arvore.root();
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no sucessor value.");
            }
            temp = arvore.find(value); // Find the node with the given value
            temp = temp->right; // Move to the right subtree
            if (temp == nullptr) {
                throw std::runtime_error("No sucessor found for the given value.");
            }
            while (temp->left != nullptr) {
                temp = temp->left; // Traverse to the leftmost node in the right subtree
            }
            return temp->key; // Return the sucessor value   
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    int predecessor(int value) {
        try
        {
            vector<Node*> path;
            Node* temp = AVL::root();
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no predecessor value.");
            }
            while (temp != nullptr) {
                path.push_back(temp); // Store the path to the node
                if (value < temp->key) {
                    temp = temp->left; // Move to the left subtree
                } else if (value > temp->key) {
                    temp = temp->right; // Move to the right subtree
                } else {
                    break; // Found the node with the given value
                }
            }
            if (temp == nullptr) {
                throw std::runtime_error("Value not found in the set.");
                return -1; // Return -1 or handle the error as needed
            }
            //Case 1: Node has a left child
            if (temp->left != nullptr) {
                temp = temp->left; // Move to the left subtree
                while (temp->right != nullptr) {
                    temp = temp->right; // Traverse to the rightmost node in the left subtree
                }
                return temp->key; // Return the predecessor value
            } 
            else{
                //Case 2: Node has no left child but it itself is the right child of its parent
                path.pop_back(); // Remove the current node from the path
                if (temp == path.back()->right) {
                    return path.back()->key; // Return the predecessor value
                } 
                else {
                    //Case 3: Node has no left child and it is the left child of its parent
                    while(!path.empty()) {
                        if (temp == path.back()->right) {
                            return path.back()->key; // Return the predecessor value
                        }
                        temp = path.back(); // Move to the parent node
                        path.pop_back(); // Remove the current node from the path
                    }
                    throw std::runtime_error("No predecessor found for the given value.");
                    return -1; // Return -1 or handle the error as needed
                }
            }     

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1; // Return -1 or handle the error as needed
        }
    }

    // Function to see if the set is empty
    // Returns true if the set is empty, false otherwise
    bool empty() const {
        return arvore.empty(); // Check if the AVL tree is empty
    }



    
};

#endif