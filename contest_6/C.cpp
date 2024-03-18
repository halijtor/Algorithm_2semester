#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

void DoingDynamic(std::vector<std::vector<int>>& dp, int height, int planes,
                  int& ans) {
  for (int i = 1; i < height + 1; ++i) {
    for (int j = 1; j < planes + 1; ++j) {
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + 1;
    }
  }
  for (int i = 0; i < height + 1; ++i) {
    if (dp[i][planes] + 1 >= height) {
      ans = i;
      break;
    }
  }
}

int main() {
  int height;
  std::cin >> height;
  int planes;
  std::cin >> planes;
  planes = std::min(planes, static_cast<int>(std::log2(height)) + 1);
  std::vector<std::vector<int>> dp(height + 1, std::vector<int>(planes + 1));
  int ans = -1;
  DoingDynamic(dp, height, planes, ans);
  std::cout << ans << "\n";
  return 0;
}
