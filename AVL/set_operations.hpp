#ifndef SET_OPERATIONS_HPP
#define SET_OPERATIONS_HPP
#include "Set.hpp"
#include <queue>

    Set setUnion(Set& first, Set& second){
        Set result;
        queue<Node*> q;
        q.push(first.root());
        while (!q.empty()){
            Node* temp = q.front();
            result.add(temp->key);
            q.pop();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
        }
        q.push(second.root());
        while (!q.empty()){
            Node* temp = q.front();
            result.add(temp->key);
            q.pop();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
        }
        return result;
    }

    Set setIntersection (Set& first, Set& second){
        Set result;
        queue<Node*> q;
        q.push(second.root());
        while (!q.empty()){
            Node* temp = q.front();
            q.pop();
            if (first.contains(temp->key)){
                cout <<"Inserimos a chave: " << temp->key << endl;
                result.add(temp->key);
            }
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
        }
        return result;
    }

    Set* setCopy(Set& set) {
        Set* result = new Set(); // Dynamically allocate memory for the result
        queue<Node*> q;
        Node* root = set.root();
        if (root != nullptr) {
            result->add(root->key); // Add the root node's key to the result
            q.push(root);
        }
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            if (temp->left != nullptr) {
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                q.push(temp->right);
            }
            result->insert(temp->key);
        }
        return result; // Return the dynamically allocated result
    }


    // Check for null
    bool OperationNull(Set& first, Set& second){
        if (first.root() == nullptr || second.root() == nullptr){
            cout << "One of the sets is empty" << endl;
            return true;
        }
        return false;
    }

    Set setDifference(Set& first, Set& second) {
        if (OperationNull(first, second)) return Set(); // Return an empty set if one of the sets is null
        Set* result = new Set(); // Create a new set for the result
        queue<Node*> q;
        q.push(first.root());
    
        // Traverse the first set
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
    
            // Add to result if not in second
            if (!second.contains(temp->key)) {
                result->add(temp->key);
            }
    
            // Traverse left and right children
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
        }
    
        return *result; // Return the result directly
    }

#endif