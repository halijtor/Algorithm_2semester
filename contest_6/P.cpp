#include <iostream>
#include <vector>

const int kMod = 1e9 + 7;

std::vector<int> make_mask(int curr_mask, int size_n) {
  int ans = 0;
  int index = -1;
  for (int i = 1; i < size_n; ++i) {
    int rem = ((curr_mask >> i) & 1) + ((curr_mask >> (i - 1)) & 1);
    if (rem == 0) {
      ans = (ans | (1 << i)) | (1 << (i - 1));
    }
    index = (rem != 1) ? i : index;
  }

  if (index == -1) {
    for (int i = 0; i < size_n; ++i) {
      ans |= (((curr_mask >> i) & 1) ^ 1) << i;
    }
    return {ans, curr_mask};
  }

  bool flag = true;
  for (int i = index + 1; i < size_n; ++i) {
    int rem = ((curr_mask >> i) & 1) + ((curr_mask >> (i - 1)) & 1) +
              ((ans >> (i - 1)) & 1);
    if (rem == 1) {
      ans |= 1 << i;
    } else if (rem != 2) {
      flag = false;
      break;
    }
  }

  for (int i = index - 2; i >= 0; --i) {
    int rem = ((curr_mask >> i) & 1) + ((curr_mask >> (i + 1)) & 1) +
              ((ans >> (i + 1)) & 1);
    if (rem == 1) {
      ans |= (1 << i);
    } else if (rem != 2) {
      flag = false;
      break;
    }
  }

  if (flag) {
    return {ans};
  }
  return {};
}

bool is_valid(int mask, int size_n,
             const std::vector<std::vector<char>>& city_map, int col) {
  for (int i = 0; i < size_n; ++i) {
    if ((city_map[i][col] == '+' && (mask & (1 << i)) == 0) ||
        (city_map[i][col] == '-' && (mask & (1 << i)) != 0)) {
      return false;
    }
  }
  return true;
}

bool is_compatible(int mask1, int mask2, int size_n) {
  for (int i = 0; i < size_n - 1; ++i) {
    int count = (mask1 >> i & 1) + (mask1 >> (i + 1) & 1) + (mask2 >> i & 1) +
                (mask2 >> (i + 1) & 1);
    if (count != 2) {
      return false;
    }
  }
  return true;
}

void doing_dynamic(int size_n, int size_m, int& result,
                  std::vector<std::vector<char>>& city_map,
                  std::vector<std::vector<int>>& dp_table) {
  int max_mask = 1 << size_n;
  for (int mask = 0; mask < max_mask; ++mask) {
    if (is_valid(mask, size_n, city_map, 0)) {
      dp_table[0][mask] = 1;
    }
  }

  for (int j = 1; j < size_m; ++j) {
    for (int curr_mask = 0; curr_mask < max_mask; ++curr_mask) {
      if (!is_valid(curr_mask, size_n, city_map, j)) {
        continue;
      }
      std::vector<int> prev = make_mask(curr_mask, size_n);
      for (size_t i = 0; i < prev.size(); ++i) {
        if (is_compatible(curr_mask, prev[i], size_n)) {
          dp_table[j][curr_mask] =
              (dp_table[j][curr_mask] + dp_table[j - 1][prev[i]]) % kMod;
        }
      }
    }
  }

  for (int mask = 0; mask < max_mask; ++mask) {
    result = (result + dp_table[size_m - 1][mask]) % kMod;
  }
}

int main() {
  int size_n = 0;
  int size_m = 0;
  std::cin >> size_n >> size_m;
  std::vector<std::vector<char>> city_map(size_n, std::vector<char>(size_m));
  for (int i = 0; i < size_n; ++i) {
    for (int j = 0; j < size_m; ++j) {
      std::cin >> city_map[i][j];
    }
  }

  int max_mask = 1 << size_n;
  std::vector<std::vector<int>> dp_table(size_m, std::vector<int>(max_mask, 0));
  int result = 0;
  doing_dynamic(size_n, size_m, result, city_map, dp_table);
  std::cout << result << std::endl;
  return 0;
}
