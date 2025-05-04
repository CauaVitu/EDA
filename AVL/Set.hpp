#ifndef Set_HPP
#define Set_HPP
#include "AVL.hpp"
#include "Node.hpp"
#include <iostream>
#include <queue>
#include <optional>
using namespace std;

class Set : public AVL {
    // This class implements a set using an AVL tree.
    // It inherits from the AVL class to utilize its functionalities.
    // The set does not allow duplicate elements.
private:
    AVL arvore; // AVL tree to store the set elements
public:
    Set() : arvore() {} // Default constructor

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
        if (contains(value)) {
            AVL::remove(value); // Use the AVL class's remove method
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

    int maximum () {
        return AVL::maximum(); // Call the AVL class's maximum method
    }

    int minimum () {
        return AVL::minimum(); // Call the AVL class's minimum method
    }
    
    int sucessor(int value) {
        try
        {
            vector<Node*> path;
            Node* temp = AVL::root();
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no sucessor value.");
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
            //Case 1: Node has a right child
            if (temp->right != nullptr) {
                temp = temp->right; // Move to the left subtree
                while (temp->left != nullptr) {
                    temp = temp->left; // Traverse to the leftmost node in the left subtree
                }
                return temp->key; // Return the sucessor value
            } 
            else{
                //Case 2: Node has no left child but it itself is the left child of its parent
                path.pop_back(); // Remove the current node from the path
                if (temp == path.back()->left) {
                    return path.back()->key; // Return the predecessor value
                } 
                else {
                    //Case 3: Node has no right child and it is the left child of its parent
                    while(!path.empty()) {
                        if (temp == path.back()->left) {
                            return path.back()->key; // Return the predecessor value
                        }
                        temp = path.back(); // Move to the parent node
                        path.pop_back(); // Remove the current node from the path
                    }
                    throw std::runtime_error("No sucessor found for the given value.");
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

    optional <int> predecessor(int value) {
        try
        {
            vector<Node*> path;
            Node* temp = AVL::root();
            if (temp == nullptr) {
                throw std::runtime_error("Set is empty, no predecessor value.");
                return nullopt; // Return nullopt or handle the error as needed;
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
            return nullopt; // Return nullopt or handle the error as needed
        }
    }

    // Function to see if the set is empty
    // Returns true if the set is empty, false otherwise
    bool empty() const {
        return arvore.empty(); // Check if the AVL tree is empty
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            arvore = other.arvore; // Use the assignment operator of AVL to perform a deep copy
        }
        return *this;
    }


    
};

#endif