/**
 * @file BinarySearch.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 二分搜索
 * @version 1.0
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>

constexpr int MaxN = 1e4 + 10;
int d[MaxN]{};

/**
 * @brief 二分搜索（要求已知数组必须已排序）
 * 
 * @param l 
 * @param r 
 * @param target 目标数
 * @return int 返回目标数的索引
 */
int bs_find(int l, int r, int target) {
  if (l > r) return -1;

  int mid = (l + r) >> 1;
  if (d[mid] < target)
    return bs_find(mid + 1, r, target);
  else if (d[mid] > target)
    return bs_find(l, mid - 1, target);
  else
    return mid;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) std::cin >> d[i];
  int target;
  std::cin >> target;
  std::cout << bs_find(0, n - 1, target) << std::endl;

  return 0;
}