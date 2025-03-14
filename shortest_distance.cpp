#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stdexcept>

class Graph {

    using vertex_index_t = int;
    using graph_t = std::vector<std::vector<vertex_index_t>>;

    static constexpr auto infinity = std::numeric_limits<vertex_index_t>::max();

public:
    
    explicit Graph(vertex_index_t cnt_vertexes) 
        : graph(cnt_vertexes)
    {}

    void add_edge(vertex_index_t to, vertex_index_t from) {
        if (from >= graph.size() || from < 0 || to >= graph.size() || to < 0) {
            throw std::out_of_range{"Vertexes are out of range!"};
        }
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    auto shortest_distance_from(vertex_index_t start) const {
        
        std::vector<vertex_index_t> dist(graph.size(), infinity);
        std::queue<vertex_index_t> q;

        q.push(start);
        dist[start] = 0;

        while(!q.empty()) {

            const auto v = q.front();
            q.pop();

            for(const auto to : graph[v]) {
                if (dist[to] == infinity) {
                    
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }

        return dist;
    }

private:
    graph_t graph;
};




int main() {

    std::ifstream inputFile("graph.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open an input file!\n";
        return 1;
    }

    int count_vertexes, count_edges;
    inputFile >> count_vertexes >> count_edges;

    Graph graph(count_vertexes);
    
    for(int i = 0; i < count_edges; ++i) {
        
        int to, from;
        inputFile >> to >> from;
        
        graph.add_edge(to, from);
    }

    int start;
    inputFile >> start;

    inputFile.close();

    const auto shortest_dist = graph.shortest_distance_from(start);
    
    for(const auto d : shortest_dist) {
        std::cout << d << std::endl;
    }

    return 0;
}