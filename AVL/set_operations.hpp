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
            if (first.contains(temp->key)){
                result.add(temp->key);
            }
        }
        return result;
    }

    Set setCopy(Set& set){
        Set result;
        queue<Node*> q;
        q.push(result.root());
        while (!q.empty()){
            Node* temp = q.front();
            q.pop();
            if (temp->left != nullptr) {
                result.add(temp->left->key);
                q.push(temp->left);
            }
            if (temp->right != nullptr){
                result.add(temp->right->key);
                q.push(temp->right);
            }
        }
        return result;
    }

    // Will always operate first - second
    Set setDifference(Set& first,Set& second){
        Set result = setCopy(first);
        queue<Node*> q;
        q.push(second.root());
        while (!q.empty()){
            Node* temp = q.front();
            q.pop();
            if (temp->left != nullptr) {
                if (result.contains(temp->left->key)){
                    result.remove(temp->left->key);
                }
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                if (result.contains(temp->right->key)){
                    result.remove(temp->right->key);
                }
                q.push(temp->right);
            }
        }
        return result;
    }

#endif