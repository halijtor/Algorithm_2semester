#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<int> component_;
  std::vector<int> component_ids_;

 public:
  Graph(int vertexs) : component_ids_(vertexs) {}

  static void Dfs1(std::vector<int>& order, std::vector<bool>& visited,
                   std::vector<std::vector<int>>& adj_rev, int vvv) {
    visited[vvv] = true;
    for (int uuu : adj_rev[vvv]) {
      if (!visited[uuu]) {
        Dfs1(order, visited, adj_rev, uuu);
      }
    }
    order.push_back(vvv);
  }

  void Dfs2(int vvv, int ccl, std::vector<bool>& visited,
            std::vector<std::vector<int>>& adj) {
    visited[vvv] = true;
    component_.push_back(vvv);
    component_ids_[vvv] = ccl;
    for (int uuu : adj[vvv]) {
      if (!visited[uuu]) {
        Dfs2(uuu, ccl, visited, adj);
      }
    }
  }

  void Print(int ccl) {
    std::cout << ccl << "\n";
    for (size_t i = 0; i < component_ids_.size(); ++i) {
      std::cout << ccl - component_ids_[i] << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  int vertexs = 0;
  int edges = 0;
  std::cin >> vertexs >> edges;

  std::vector<std::vector<int>> adj(vertexs);
  std::vector<std::vector<int>> adj_rev(vertexs);
  std::vector<bool> visited(vertexs, false);
  std::vector<int> order;
  Graph graph(vertexs);

  for (int i = 0, uu = 0, vv = 0; i < edges; ++i) {
    std::cin >> uu >> vv;
    --uu;
    --vv;
    adj[uu].push_back(vv);
    adj_rev[vv].push_back(uu);
  }

  for (int i = 0; i < vertexs; ++i) {
    if (!visited[i]) {
      Graph::Dfs1(order, visited, adj_rev, i);
    }
  }

  visited.assign(vertexs, false);
  std::reverse(order.begin(), order.end());

  int ccl = 0;
  for (int vertex : order) {
    if (!visited[vertex]) {
      graph.Dfs2(vertex, ccl, visited, adj);
      ccl++;
    }
  }

  graph.Print(ccl);
  return 0;
}
