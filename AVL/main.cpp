#include <iostream>
#include "AVL.hpp"

int main(){
    AVL arvore;
    int n, v;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> v;
        arvore.add(v);
    }
    arvore.BFS();
    std::cout << std::endl;
    arvore.show();
    std::cout << std::endl;
    return 0;
}