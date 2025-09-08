#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    string neighbor;
    string movie;
};

using Graph = unordered_map<string, vector<Edge>>;

void addEdge(Graph& graph, const string& actor1, const string& actor2, const string& movie) {
    graph[actor1].push_back({actor2, movie});
    graph[actor2].push_back({actor1, movie});
}

void computeBaconPaths(const Graph& graph,
                       unordered_map<string, int>& distance,
                       unordered_map<string, string>& movieUsed,
                       unordered_map<string, string>& parent,
                       const string& source = "Kevin Bacon") {
    queue<string> q;
    q.push(source);
    distance[source] = 0;

    while (!q.empty()) {
        string current = q.front(); q.pop();
        for (const Edge& edge : graph.at(current)) {
            const string& neighbor = edge.neighbor;
            if (distance.count(neighbor) == 0) {
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                movieUsed[neighbor] = edge.movie;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    Graph graph;

    // Leitura dos dados do grafo pelo terminal
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        
        stringstream ss(line);
        string actor1, movie, actor2;
        getline(ss, actor1, ';');
        getline(ss, movie, ';');
        getline(ss, actor2);
        
        addEdge(graph, actor1, actor2, movie);
    }

       unordered_map<string, int> distance;
    unordered_map<string, string> movieUsed;
    unordered_map<string, string> parent;
    computeBaconPaths(graph, distance, movieUsed, parent);

    // Coletar todos os atores e ordenar alfabeticamente
    vector<string> actors;
    for (const auto& pair : distance) {
        actors.push_back(pair.first);
    }
    sort(actors.begin(), actors.end());

    // Listar todos os atores em ordem alfabética
    for (const string& actor : actors) {
        if (actor == "Kevin Bacon") {
            cout << "O numero de Bacon de Kevin Bacon é 0 pelo filme \n";
        } else {
            cout << "O numero de Bacon de " << actor
                 << " é " << distance[actor]
                 << " pelo filme " << movieUsed[actor] << "\n";
        }
    }

    return 0;
}