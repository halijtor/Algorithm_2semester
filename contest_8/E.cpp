#include <iostream>
#include <limits>
#include <vector>

const int cInf = 100000;

void FloidWarshall(int n, std::vector<std::vector<int>>& dist,
                   std::vector<std::vector<int>>& next) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (dist[i][j] < cInf) {
        next[i][j] = j;
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] < cInf && dist[k][j] < cInf &&
            dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }
}

void FindNegativeCycle(const std::vector<std::vector<int>>& graph, int n) {
  std::vector<std::vector<int>> dist = graph;
  std::vector<std::vector<int>> next(n, std::vector<int>(n, -1));
  FloidWarshall(n, dist, next);

  int current = -1;
  int rem = 0;
  for (int i = 0; i < n; ++i) {
    if (dist[i][i] < 0) {
      std::cout << "YES\n";
      current = i;
      rem = i;
      break;
    }
  }
  if (current == -1) {
    std::cout << "NO\n";
    return;
  }
  std::vector<int> cycle;
  std::vector<bool> visited(n, false);
  while (!visited[current]) {
    visited[current] = true;
    current = next[current][rem];
  }

  int start = current;
  cycle.push_back(start);
  current = next[start][rem];
  while (current != start) {
    cycle.push_back(current);
    current = next[current][rem];
  }
  cycle.push_back(start);

  std::cout << cycle.size() << std::endl;
  for (int vertex : cycle) {
    std::cout << vertex + 1 << " ";
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int>> graph(n, std::vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> graph[i][j];
    }
  }

  FindNegativeCycle(graph, n);
  return 0;
}
