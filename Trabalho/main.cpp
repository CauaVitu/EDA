#include <iostream>
#include "AVL.hpp"
#include "RBTree.hpp"
#include "ChainedHashTable.hpp"
#include "OpenHash.hpp"
using namespace std;

int main(int argc, char* argv[]) {

    // Teste da AVL
    AVL<int> avl;
    for (int i = 0; i < 100; i++) {
        avl.insert(i);
    }
    avl.show();
    cout << "Contador de comparações AVL: " << avl.get_comparison_counter() << endl;

    // Teste da RBTree
    RBTree<int> rbtree;
    for (int i = 0; i < 1000; i++) {
        rbtree.insert(i);
    }
    rbtree.show();
    cout << "Contador de comparações RBTree: " << rbtree.get_comparison_counter() << endl;
    
    // Teste da ChainedHashTable
    ChainedHashTable<int, string> hashTable(10);
    for (int i = 0; i < 1000; i++) {
        hashTable.insert(i, "Amoeba");
    }

    for (int i = 0; i < 1000; i++) {
        if (hashTable.contains(i)) {
        }
    }
    cout << "Contador de comparações ChainedHashTable: " << hashTable.get_comparison_counter() << endl;


    OpenHash<int, string> openHashTable(10);
    for (int i = 0; i < 1000; i++) {
        openHashTable.insert(i, "Amoeba");
    }
    
    for (int i = 0; i < 1000; i++) {
        if (openHashTable.contains(i)) {
        }
    }
    cout << "Contador de comparações OpenHashTable: " << openHashTable.get_comparison_counter() << endl;


    }