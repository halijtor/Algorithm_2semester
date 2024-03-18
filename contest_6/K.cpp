#include <algorithm>
#include <iostream>
#include <vector>

void DoingDynamic(std::vector<int>& weight, std::vector<int>& price,
                  std::vector<std::vector<int>>& dp) {
  for (size_t i = 1; i < dp.size(); ++i) {
    for (size_t j = 0; j < dp[i].size(); ++j) {
      if (weight[i - 1] <= static_cast<int>(j)) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + price[i - 1]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
}

void RecoveringAnswer(std::vector<int>& ans, std::vector<int>& weight,
                      std::vector<std::vector<int>>& dp) {
  for (size_t i = dp.size() - 1, j = dp[0].size() - 1;;) {
    if (dp[i][j] == 0) {
      break;
    }
    if (dp[i][j] == dp[i - 1][j]) {
      --i;
    } else {
      j -= weight[i - 1];
      ans.push_back(i);
      --i;
    }
  }
  std::sort(ans.begin(), ans.end());
}

int main() {
  int amount;
  std::cin >> amount;
  int max_weight;
  std::cin >> max_weight;
  std::vector<int> weight(amount);
  for (int i = 0; i < amount; ++i) {
    std::cin >> weight[i];
  }
  std::vector<int> price(amount);
  for (int i = 0; i < amount; ++i) {
    std::cin >> price[i];
  }
  std::vector<std::vector<int>> dp(amount + 1,
                                   std::vector<int>(max_weight + 1, 0));
  DoingDynamic(weight, price, dp);
  std::vector<int> ans;
  RecoveringAnswer(ans, weight, dp);
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i] << "\n";
  }
  return 0;
}
