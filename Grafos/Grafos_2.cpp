#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Cor {
    NAO_COLORIDO = -1,
    COR_1 = 0,
    COR_2 = 1
};

bool ehBipartido(vector<vector<int>>& grafo, int numeroVertices) {
    vector<int> cores(numeroVertices, NAO_COLORIDO); // Inicializa todas as cores como não coloridas
    
    for (int inicio = 0; inicio < numeroVertices; inicio++) {
        if (cores[inicio] == NAO_COLORIDO) {
            // BFS para colorir esta componente
            queue<int> fila;
            fila.push(inicio);
            cores[inicio] = COR_1;
            
            while (!fila.empty()) {
                int verticeAtual = fila.front();
                fila.pop();
                
                // Verifica todos os vizinhos do vértice atual
                for (int vizinho : grafo[verticeAtual]) {
                    if (cores[vizinho] == NAO_COLORIDO) {
                        // Vizinho não colorido - colorir com a outra cor
                        cores[vizinho] = (cores[verticeAtual] == COR_1) ? COR_2 : COR_1;                        
                        fila.push(vizinho);
                    } else if (cores[vizinho] == cores[verticeAtual]) {
                        // Vizinho tem a mesma cor - não é bipartido
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

int main() {
    int numeroVertices;
    
    while (cin >> numeroVertices && numeroVertices != 0) {
        vector<vector<int>> grafo(numeroVertices);
        
        int vertice1, vertice2;
        while (cin >> vertice1 >> vertice2 && (vertice1 != 0 || vertice2 != 0)) {
            grafo[vertice1].push_back(vertice2);
            grafo[vertice2].push_back(vertice1);
        }
        
        if (ehBipartido(grafo, numeroVertices)) {
            cout << "SIM" << endl;
        } else {
            cout << "NAO" << endl;
        }
    }
    
    return 0;
}