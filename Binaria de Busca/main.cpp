#include <iostream>
#include "Tree.hpp"
using namespace std;



int main() {
    // Numero de Testes
    int n;
    cin >> n;
    for (int i=0; i<n; i++){
        // Leitura do numero de elementos
        int num;
        cin >> num;
        // Cria a arvore
        Tree arvore;
        // Leitura dos elementos
        for (int j=0; j<num; j++){
            int temp;
            cin >> temp;
            arvore.insert(temp);
        }
        // Mostra a arvore
        cout << "Case " << i+1 << ":\n";
        arvore.BFS();
        cout << "\n";
        
    }
    

    
}