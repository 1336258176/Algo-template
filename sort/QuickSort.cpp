/**
 * @file QuickSort.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 快排的三种实现方式
 * @version 1.0
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <random>

constexpr int MaxN = 1e4 + 10;
int d[MaxN]{};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> random(0, MaxN);

inline int rand(int len) { return random(gen) % len; }

/**
 * @brief 未优化的快速排序（以最左边的元素为基准数）
 * 
 * @param left 
 * @param right 
 */
void qs(int left, int right) {
  if (left >= right) return;
  int l = left;
  int r = right;
  const int pivot = d[left];
  while (l < r) {
    while (l < r && pivot <= d[r]) r--;
    while (l < r && d[l] <= pivot) l++;
    if (l < r) std::swap(d[l], d[r]);
  }
  std::swap(d[left], d[l]);
  qs(left, l - 1);
  qs(l + 1, right);
}

/**
 * @brief 朴素优化后的快速排序（随机选取一个基准数）
 * 
 * @param left 
 * @param right 
 */
void qs_plain(int left, int right) {
  if (left >= right) return;
  int l = left;
  int r = right;
  int m = rand(right - left + 1) + left;
  const int pivot = d[m];
  std::swap(d[left], d[m]);
  while (l < r) {
    while (l < r && pivot <= d[r]) r--;
    while (l < r && d[l] <= pivot) l++;
    if (l < r) std::swap(d[l], d[r]);
  }
  std::swap(d[left], d[l]);
  qs_plain(left, l - 1);
  qs_plain(l + 1, right);
}

/**
 * @brief 三路快排，将数组分为小于、等于和大于基准数的三部分
 * 
 * @param left 
 * @param right 
 */
void qs_threepart(int left, int right) {
  if (left >= right) return;
  int i = 0;
  int j = 0;
  int k = right;
  const int pivot = d[rand(right - left + 1) + left];

  while (j < k) {
    if (d[i] < pivot) {
      std::swap(d[i++], d[j++]);
    } else if (d[i] > pivot) {
      std::swap(d[i], d[k--]);
    } else {
      i++;
    }
  }

  qs_threepart(left, j - 1);
  qs_threepart(k + 1, right);
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> d[i];
  }
  // qs(0, n - 1);
  // qs_plain(0, n - 1);
  qs_threepart(0, n - 1);
  for (int i = 0; i < n; i++) {
    std::cout << d[i] << ' ';
  }

  return 0;
}