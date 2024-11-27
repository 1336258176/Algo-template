/**
 * @file DisjointSet.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 并查集，支持查询、合并、删除、移动
 * @version 1.0
 * @date 2024-11-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>

class DisjointSet {
 private:
  // pa_[i] 表示节点i的父节点
  // size_[i] 表示节点i下的节点数量(包括自己)
  std::vector<int> pa_, size_;

 public:
  DisjointSet() = default;
  ~DisjointSet() = default;

  /**
   * @brief 构造并查集，size个元素，size个副本，以副本作为根节点
   *        副本本身只起到标识不同集合的作用，前半段size_数组本身没有实际意义
   * 
   * @param size 元素个数
   */
  explicit DisjointSet(size_t size) : pa_(size * 2), size_(size * 2, 1) {
    std::iota(pa_.begin(), pa_.begin() + size, size);
    std::iota(pa_.begin() + size, pa_.end(), size);
  }

  /**
   * @brief 查询元素x的根节点
   * 
   * @param x 
   * @return int 
   */
  inline int find(size_t x) {
    return pa_[x] == x ? x : pa_[x] = find(pa_[x]);  // 路径压缩：利用查询将节点直接连到根节点上，加快后续查询
  }

  /**
   * @brief 合并两个元素所属集合
   * 
   * @param x 要合并的节点x
   * @param y 要合并的节点y
   */
  inline void unite(size_t x, size_t y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (size_[x] < size_[y]) std::swap(x, y);  // 始终保证y是小集合，x是大集合
    pa_[y] = x;
    size_[x] += size_[y];
  }

  /**
   * @brief 删除元素x（通过将x的根节点设置为自己）
   * 
   * @param x 
   */
  inline void erase(size_t x) {
    pa_[x] = x;
    --size_[x];
  }

  /**
   * @brief 移动元素x到y所属集合
   * 
   * @param x 
   * @param y 
   */
  inline void move(size_t x, size_t y) {
    size_t px = find(x);
    size_t py = find(y);
    if (px == py) return;
    pa_[x] = py;
    --size_[px];
    ++size_[py];
  }
};

int main() {
  DisjointSet disjointset(5);
  disjointset.unite(1, 3);
  disjointset.erase(1);
  disjointset.move(3, 2);
  disjointset.unite(3, 4);
  for (int i = 0; i < 5; i++) {
    printf("%d ", disjointset.find(i));
  }

  return 0;
}