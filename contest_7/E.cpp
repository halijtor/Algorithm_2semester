#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Graph {
 private:
  int timer_ = 0;
  std::vector<int> tin_;
  std::vector<int> low_;
  std::vector<std::pair<int, int>> bridges_;

 public:
  Graph(int vertexs) : tin_(vertexs, -1), low_(vertexs, -1) {}

  void Dfs(std::vector<bool>& visited, std::vector<std::vector<int>>& adj,
           std::map<std::pair<int, int>, int>& edge_count, int vvv,
           int ppp = -1) {
    visited[vvv] = true;
    tin_[vvv] = low_[vvv] = timer_++;
    for (int too : adj[vvv]) {
      if (too == ppp) {
        continue;
      }
      if (visited[too]) {
        low_[vvv] = std::min(low_[vvv], tin_[too]);
      } else {
        Dfs(visited, adj, edge_count, too, vvv);
        low_[vvv] = std::min(low_[vvv], low_[too]);
        if (low_[too] > tin_[vvv] &&
            edge_count[{std::min(vvv, too), std::max(vvv, too)}] == 1) {
          bridges_.emplace_back(std::min(vvv, too), std::max(vvv, too));
        }
      }
    }
  }

  void Print(std::map<std::pair<int, int>, int>& help) {
    std::cout << bridges_.size() << "\n";
    std::vector<int> ans;
    for (auto& bridge : bridges_) {
      ans.push_back(help[bridge]);
    }
    std::sort(ans.begin(), ans.end());
    for (int elem : ans) {
      std::cout << elem << "\n";
    }
  }
};

int main() {
  int vertexs = 0;
  int edges = 0;
  std::cin >> vertexs >> edges;

  std::map<std::pair<int, int>, int> help;
  std::vector<std::vector<int>> adj(vertexs);
  std::vector<bool> visited(vertexs, false);
  std::map<std::pair<int, int>, int> edge_count;
  Graph graph(vertexs);

  for (int i = 0, uu = 0, vv = 0; i < edges; ++i) {
    std::cin >> uu >> vv;
    --uu;
    --vv;
    adj[uu].push_back(vv);
    adj[vv].push_back(uu);
    edge_count[{std::min(uu, vv), std::max(uu, vv)}]++;
    help[{std::min(uu, vv), std::max(uu, vv)}] = i + 1;
  }

  for (int i = 0; i < vertexs; ++i) {
    if (!visited[i]) {
      graph.Dfs(visited, adj, edge_count, i);
    }
  }

  graph.Print(help);
  return 0;
}
