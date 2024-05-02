#include <iostream>
#include <queue>
#include <vector>

const int cInf = 2009000999;

void Dijkstra(int start,
              const std::vector<std::vector<std::pair<int, int>>>& graph,
              std::vector<int>& dist) {
  int n = graph.size();
  dist.assign(n, cInf);
  dist[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  pq.push({0, start});

  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();
    if (d > dist[u]) {
      continue;
    }
    for (const auto& edge : graph[u]) {
      int v = edge.first;
      int weight = edge.second;
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
}

int main() {
  int k = 0;
  std::cin >> k;
  for (int p = 0; p < k; ++p) {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> graph(n);

    for (int i = 0; i < m; i++) {
      int u = 0;
      int v = 0;
      int w = 0;
      std::cin >> u >> v >> w;
      graph[u].push_back({v, w});
      graph[v].push_back({u, w});
    }

    int start = 0;
    std::cin >> start;

    std::vector<int> dist;
    Dijkstra(start, graph, dist);

    for (int i = 0; i < n; i++) {
      std::cout << dist[i] << " ";
    }
  }
  return 0;
}
