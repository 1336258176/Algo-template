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
 *        时间复杂度: 平均O(nlogn) 最优O(nlogn) 最差O(n^2)
 *        空间复杂度: O(logn) 递归开销
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

/**
 * @brief 线性时间选择问题：给定一个序列，查找第k小元素
 *        时间复杂度：平均O(n) 最坏O(n^2) 通过二次取中的方法可以优化至O(n)
 * 
 * @param left 
 * @param right 
 * @param rk 第rk+1小元素（按照数组索引）
 * @return int 
 */
int find_kth(int left, int right, int rk) {
  if (left >= right) return d[left];
  int l = left;
  int r = right;
  int m = rand(right - left + 1) + left;
  const int pivot = d[m];
  std::swap(d[left], d[m]);
  while (l < r) {
    while (l < r && pivot <= d[r]) r--;
    while (l < r && d[l] <= pivot) l++;
    if (l < r) {
      std::swap(d[l], d[r]);
    }
  }
  std::swap(d[left], d[l]);

  if (rk < l)
    return find_kth(left, l - 1, rk);
  else if (rk > l)
    return find_kth(l + 1, right, rk);
  else
    return d[l];
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> d[i];
  }
  // qs(0, n - 1);
  // qs_plain(0, n - 1);
  // qs_threepart(0, n - 1);
  // for (int i = 0; i < n; i++) {
  //   std::cout << d[i] << ' ';
  // }

  int rk;
  std::cin >> rk;
  std::cout << find_kth(0, n-1, rk);

  return 0;
}