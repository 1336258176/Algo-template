/**
 * @file MergeSort.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 归并排序与统计逆序对
 * @version 1.0
 * @date 2024-11-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>

/* -------------------------------------------- 归并排序 -------------------------------------------- */
template <typename T>
void merge(std::vector<T>& d, int l, int m, int r) {
  std::vector<T> tmp;
  int i = l;      // 滑动前半段数组
  int j = m + 1;  // 滑动后半段数组
  while (i <= m && j <= r) {
    if (d[i] <= d[j]) {
      tmp.push_back(d[i++]);
    } else {
      tmp.push_back(d[j++]);
    }
  }
  while (i <= m) {
    tmp.push_back(d[i++]);
  }
  while (j <= r) {
    tmp.push_back(d[j++]);
  }
  for (int i = l; i <= r; i++) {  // 将排好序的数组赋值给原数组,注意不能从0开始
    d[i] = tmp[i - l];
  }
}

template <typename T>
void merge_sort(std::vector<T>& d, int l, int r) {
  if (l >= r) return;
  int m = l + ((r - l) >> 1);  // 取中间位置（防止溢出）
  merge_sort(d, l, m);
  merge_sort(d, m + 1, r);
  merge(d, l, m, r);
}

/* -------------------------------------------- 逆序对 -------------------------------------------- */
template <typename T>
int count(std::vector<T>& d, int l, int m, int r) {
  std::vector<T> tmp;
  int i = l;
  int j = m + 1;
  int count = 0;
  while (i <= m && j <= r) {
    if (d[i] <= d[j]) {
      tmp.push_back(d[i++]);
    } else {
      count += m - i + 1; // 统计逆序对
      tmp.push_back(d[j++]);
    }
  }
  while (i <= m) {
    tmp.push_back(d[i++]);
  }
  while (j <= r) {
    tmp.push_back(d[j++]);
  }
  for (int i = l; i <= r; i++) {  // 将排好序的数组赋值给原数组,注意不能从0开始
    d[i] = tmp[i - l];
  }
  return count;
}

template <typename T>
int merge_count(std::vector<T>& d, int l, int r) {
  if (l >= r) return 0;
  int m = l + ((r - l) >> 1);
  int count_l = merge_count(d, l, m);
  int count_r = merge_count(d, m + 1, r);
  int count_m = count(d, l, m, r);
  return count_l + count_r + count_m;
}

int main() {
  int n{};
  std::cin >> n;
  std::vector<int> d{};
  for (int i = 0; i < n; i++) {
    int num{};
    std::cin >> num;
    d.push_back(num);
  }
  // std::cout << merge_count(d, 0, n - 1) << std::endl;
  merge_sort(d, 0, n - 1);
  for (const auto& num : d) {
    std::cout << num << " ";
  }

  return 0;
}