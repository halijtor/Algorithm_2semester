#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int kMax = 2e9;

void base(std::vector<std::vector<std::vector<int>>>& dp, std::string& str1,
          std::string& str2, int num_k) {
  int num_n = str1.size();
  int num_m = str2.size();

  for (int i = 0; i <= num_n; ++i) {
    for (int kt = i; kt <= num_k; ++kt) {
      if ((kt - i) % 2 != 0) {
        continue;
      }
      dp[i][0][kt] = 0;
    }
  }

  for (int i = 0; i <= num_m; ++i) {
    for (int kt = i; kt <= num_k; ++kt) {
      if ((kt - i) % 2 != 0) {
        continue;
      }
      dp[0][i][kt] = 0;
    }
  }

  for (int i = 1; i <= std::min(num_m, num_n); ++i) {
    dp[i][i][0] = dp[i - 1][i - 1][0];
    if (str1[i - 1] != str2[i - 1]) {
      ++dp[i][i][0];
    }
  }
}

void doing_dynamic(std::vector<std::vector<std::vector<int>>>& dp, int num_k,
                  const std::string& str1, const std::string& str2, int& ans) {
  int num_n = str1.size();
  int num_m = str2.size();

  for (int i = 1; i <= num_n; ++i) {
    for (int j = 1; j <= num_m; ++j) {
      for (int kt = 1; kt <= num_k; ++kt) {
        dp[i][j][kt] = std::min(dp[i][j][kt], dp[i - 1][j][kt - 1]);
        dp[i][j][kt] = std::min(dp[i][j][kt], dp[i][j - 1][kt - 1]);
        dp[i][j][kt] = std::min(dp[i][j][kt], dp[i - 1][j - 1][kt] != kMax
                                                  ? dp[i - 1][j - 1][kt] + 1
                                                  : kMax);
        if (str1[i - 1] == str2[j - 1]) {
          dp[i][j][kt] = std::min(dp[i][j][kt], dp[i - 1][j - 1][kt]);
        }
      }
    }
  }

  for (int kt = 0; kt <= num_k; ++kt) {
    if (dp[num_n][num_m][kt] - (num_k - kt) < ans) {
      ans = dp[num_n][num_m][kt] - (num_k - kt);
    }
  }
  ans = std::max(ans, 0);
}

int main() {
  std::string str1 = "";
  std::string str2 = "";
  int num_k = 0;
  std::cin >> str1 >> str2 >> num_k;
  int num_n = str1.length();
  int num_m = str2.length();

  std::vector<std::vector<std::vector<int>>> dp(
      num_n + 1, std::vector<std::vector<int>>(
                     num_m + 1, std::vector<int>(num_k + 1, kMax)));
  base(dp, str1, str2, num_k);

  int ans = kMax;
  doing_dynamic(dp, num_k, str1, str2, ans);

  if (std::abs(num_n - num_m) > num_k) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }
  return 0;
}
