#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const short cSize = 16;
const long long cHelp1 = 2654435769;
const int cHelp2 = 6;
const short cN = 4;
const std::vector<std::pair<short, char>> cMoves = {
    {1, 'L'}, {-1, 'R'}, {cN, 'U'}, {-cN, 'D'}};

struct ArrayHasher {
  std::size_t operator()(const std::array<short, cSize>& array) const {
    std::size_t seed = 0;
    for (int i : array) {
      seed ^= std::hash<int>{}(i) + cHelp1 + (seed << cHelp2) + (seed >> 2);
    }
    return seed;
  }
};

struct State {
  std::array<short, cSize> board;
  short zero_idx;
  int g;
  std::string path;

  bool operator>(const State& other) const {
    return (g + Heuristic()) > (other.g + other.Heuristic());
  }

  static int LinearConflict(const std::array<short, cSize>& board) {
    int conflict = 0;
    for (int row = 0; row < cN; ++row) {
      for (int i = row * cN; i < (row + 1) * cN - 1; ++i) {
        for (int j = i + 1; j < (row + 1) * cN; ++j) {
          if (board[i] > 0 && board[j] > 0 && (board[i] - 1) / cN == row &&
              (board[j] - 1) / cN == row && board[i] > board[j]) {
            conflict += 2;
          }
        }
      }
    }

    for (int col = 0; col < cN; ++col) {
      for (int i = col; i < cSize; i += cN) {
        for (int j = i + cN; j < cSize; j += cN) {
          if (board[i] > 0 && board[j] > 0 && (board[i] - 1) % cN == col &&
              (board[j] - 1) % cN == col && board[i] > board[j]) {
            conflict += 2;
          }
        }
      }
    }
    return conflict;
  }

  int Heuristic() const {
    int h = 0;
    for (short i = 0; i < cSize; i++) {
      if (board[i] == 0) {
        continue;
      }
      int target_x = (board[i] - 1) / cN;
      int target_y = (board[i] - 1) % cN;
      int x = i / cN;
      int y = i % cN;
      h += abs(x - target_x) + abs(y - target_y);
    }
    h += LinearConflict(board);
    return h;
  }

  bool IsGoal() const {
    for (size_t i = 0; i < board.size() - 1; i++) {
      if (board[i] != static_cast<short>(i + 1)) {
        return false;
      }
    }
    return board[board.size() - 1] == 0;
  }
};

bool IsSolvable(const std::array<short, cSize>& board) {
  int inversions = 0;
  for (int i = 0; i < cSize; i++) {
    for (int j = i + 1; j < cSize; j++) {
      if (board[i] > board[j] && board[i] != 0 && board[j] != 0) {
        inversions++;
      }
    }
  }
  int zero_row =
      (std::find(board.begin(), board.end(), 0) - board.begin()) / cN;
  return (inversions + zero_row) % 2 == 1;
}

std::string Solve(std::array<short, cSize> board) {
  if (!IsSolvable(board)) {
    return "-1";
  }

  short zero_idx = std::find(board.begin(), board.end(), 0) - board.begin();
  State start{board, zero_idx, 0, ""};
  std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
  std::unordered_map<std::array<short, cSize>, int, ArrayHasher> visited;
  pq.push(start);

  // Algorithm A-star
  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    if (current.IsGoal()) {
      return std::to_string(current.g) + "\n" + current.path;
    }

    if (visited.contains(current.board) && visited[current.board] < current.g) {
      continue;
    }
    visited[current.board] = current.g;

    for (const auto& move : cMoves) {
      int new_zero_idx = current.zero_idx + move.first;
      if (new_zero_idx >= 0 && new_zero_idx < cSize &&
          (current.zero_idx % cN != 0 || move.first != -1) &&
          (current.zero_idx % cN != cN - 1 || move.first != 1) &&
          ((new_zero_idx % cN == current.zero_idx % cN) ||
           (new_zero_idx / cN == current.zero_idx / cN))) {
        std::swap(current.board[current.zero_idx], current.board[new_zero_idx]);
        State new_state = current;
        new_state.zero_idx = new_zero_idx;
        new_state.g++;
        new_state.path += move.second;
        if (!visited.contains(new_state.board) ||
            visited[new_state.board] >
                static_cast<int>(current.path.size()) + 1) {
          pq.push(new_state);
          visited[new_state.board] = new_state.g;
        }
        std::swap(current.board[current.zero_idx], current.board[new_zero_idx]);
      }
    }
  }
  return "-1";
}

int main() {
  std::array<short, cSize> board;
  for (short i = 0; i < cSize; ++i) {
    std::cin >> board[i];
  }

  std::cout << Solve(board) << std::endl;
  return 0;
}
