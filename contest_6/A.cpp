#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
  int vertex;
  int tl;
  int tr;
  Node(int vertex, int tl, int tr) : vertex(vertex), tl(tl), tr(tr) {}
};

class MaxTree {
 public:
  MaxTree(int val) : tree_(4 * val) {}

  void build_tree(std::vector<int64_t>& numbers, Node node) {
    if (node.tl == node.tr) {
      tree_[node.vertex] = {numbers[node.tl], node.tl};
      return;
    }
    int tm = node.tl + (node.tr - node.tl) / 2;
    Node left_son = {2 * node.vertex + 1, node.tl, tm};
    build_tree(numbers, left_son);
    Node right_son = {2 * node.vertex + 2, tm + 1, node.tr};
    build_tree(numbers, right_son);
    if (tree_[2 * node.vertex + 1].first >= tree_[2 * node.vertex + 2].first) {
      tree_[node.vertex] = tree_[2 * node.vertex + 1];
    } else {
      tree_[node.vertex] = tree_[2 * node.vertex + 2];
    }
  }

  void update(Node node, int pos, int val) {
    if (node.tl == node.tr) {
      tree_[node.vertex] = {val, node.tl};
      return;
    }
    int tm = node.tl + (node.tr - node.tl) / 2;
    if (pos <= tm) {
      Node left_son = {2 * node.vertex + 1, node.tl, tm};
      update(left_son, pos, val);
    } else {
      Node right_son = {2 * node.vertex + 2, tm + 1, node.tr};
      update(right_son, pos, val);
    }
    if (tree_[2 * node.vertex + 1].first >= tree_[2 * node.vertex + 2].first) {
      tree_[node.vertex] = tree_[2 * node.vertex + 1];
    } else {
      tree_[node.vertex] = tree_[2 * node.vertex + 2];
    }
  }

  std::pair<int64_t, int64_t> get_ans(Node node, int left, int right) {
    if (node.tl == left && node.tr == right) {
      return tree_[node.vertex];
    }
    int tm = node.tl + (node.tr - node.tl) / 2;
    Node left_son = {2 * node.vertex + 1, node.tl, tm};
    Node right_son = {2 * node.vertex + 2, tm + 1, node.tr};
    if (right <= tm) {
      return get_ans(left_son, left, right);
    }
    if (left >= tm + 1) {
      return get_ans(right_son, left, right);
    }
    std::pair<int64_t, int64_t> left_son_ans = get_ans(left_son, left, tm);
    std::pair<int64_t, int64_t> right_son_ans =
        get_ans(right_son, tm + 1, right);
    if (left_son_ans.first >= right_son_ans.first) {
      return left_son_ans;
    }
    return right_son_ans;
  }

 private:
  std::vector<std::pair<int64_t, int64_t>> tree_;
};

bool cmp(std::pair<int64_t, int64_t> first,
         std::pair<int64_t, int64_t> second) {
  return first.first > second.first ||
         (first.first == second.first && first.second < second.second);
}

int main() {
  int amount_of_numbers = 0;
  std::cin >> amount_of_numbers;
  std::vector<int64_t> help(amount_of_numbers);
  std::vector<std::pair<int64_t, int64_t>> numbers(amount_of_numbers);
  for (int i = 0; i < amount_of_numbers; ++i) {
    std::cin >> help[i];
    numbers[i] = {help[i], i};
  }

  std::vector<int64_t> dp(amount_of_numbers);
  std::vector<int64_t> res(amount_of_numbers);

  MaxTree tree(amount_of_numbers);
  Node root = {0, 0, amount_of_numbers - 1};
  tree.build_tree(dp, root);
  std::sort(numbers.begin(), numbers.end(), cmp);

  for (int i = 0; i < amount_of_numbers; ++i) {
    std::pair<int64_t, int64_t> ans = tree.get_ans(root, 0, numbers[i].second);
    dp[numbers[i].second] = ans.first + 1;
    res[numbers[i].second] = ans.second;
    tree.update(root, numbers[i].second, dp[numbers[i].second]);
  }

  int max_length = 0;
  int pos_max_length = -1;
  for (int i = 0; i < amount_of_numbers; ++i) {
    if (dp[i] > max_length) {
      max_length = dp[i];
      pos_max_length = i;
    }
  }

  std::vector<int64_t> ans;
  for (int i = pos_max_length;; i = res[i]) {
    ans.push_back(i);
    if (static_cast<int>(ans.size()) >= max_length) {
      break;
    }
  }

  std::cout << max_length << "\n";
  for (int i = max_length - 1; i >= 0; --i) {
    std::cout << ans[i] + 1 << " ";
  }
  return 0;
}
