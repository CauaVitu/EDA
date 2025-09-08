#include <iostream>
#include <map>
#include <vector>
#include <functional>

enum Cor {
    BRANCO, // nunca visitado
    CINZA,  // visitando
    PRETO   // já visitado
};
using namespace std;

bool dfs(const string& cidadeAtual, const string& cidade2, 
         map<string, Cor>& visitado, map<string, vector<string>>& vizinhos) {
    if (cidadeAtual == cidade2) {
        return true; // Encontrou o caminho
    }
    
    visitado[cidadeAtual] = CINZA; // Marca a cidade atual como visitada
    
    for (const auto& vizinho : vizinhos[cidadeAtual]) {
        if (visitado[vizinho] == BRANCO) { // Se o vizinho não foi visitado
            if (dfs(vizinho, cidade2, visitado, vizinhos)) {
                return true; // Se encontrou o caminho, retorna true
            }
        }
    }
    
    visitado[cidadeAtual] = PRETO; // Marca a cidade atual como completamente visitada
    return false; // Não encontrou o caminho
}

int main (){
    int n; //Numero de cidades
    map<string, vector <string>> vizinhos; // Vizinhos do vertice
    cin >> n;
    for(int i = 0; i < n; i++) {
        string cidade;
        cin >> cidade; //Lendo as cidades
        vizinhos[cidade] = vector<string>(); // Inicializando a lista de vizinhos
    }
    int m; //Numero de estradas
    cin >> m;
    for (int i = 0; i < m; i++) {
        string cidade1, cidade2;
        cin >> cidade1 >> cidade2; //Lendo as estradas
        vizinhos[cidade1].push_back(cidade2); // Adicionando vizinho
        vizinhos[cidade2].push_back(cidade1); // Adicionando vizinho
    }
    int p; // Numero de consultas
    cin >> p;
    for (int i = 0; i < p; i++) {
        string cidade1, cidade2;
        cin >> cidade1 >> cidade2; //Lendo as consultas
        // Realiza a busca em profundidade
        map<string, Cor> visitado; // Mapa para marcar as cidades visitadas
        for (const auto& par : vizinhos) {
            visitado[par.first] = BRANCO; // Marca todas as cidades como não visitadas
        }
        
        bool caminhoExiste = dfs(cidade1, cidade2, visitado, vizinhos);
        
        if (caminhoExiste) {
            cout << "true " << cidade1 << " " << cidade2 << endl;
        } else {
            cout << "false " << cidade1 << " " << cidade2 << endl;
        }
    }
    return 0;
}

