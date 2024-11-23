/**
 * @file 0-1bag.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 分支限界法解决0/1背包问题
 *        分支限界法常以广度优先或以最小耗费（最大效益）优先的方式搜索问题的解空间树(子集树、排列树)
 * @version 1.0
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>

struct Item {
  int value_{};   // 价值
  int weight_{};  // 重量

  bool operator>(const Item& x) const {
    return (value_ * 1.0 / weight_) > (x.value_ * 1.0 / x.weight_);
  }
};

struct Node {
  int cw_{};        // 当前重量
  int cv_{};        // 当前价值
  int cl_{};        // 当前节点所处的层数，最上层为0
  double bound_{};  // 该节点的上界值
};

int M{};  // 物品数量
int C{};  // 背包容量
std::vector<Item> items{};

/**
 * @brief 上界函数：用于评估当前节点（部分解）是否有可能得到问题的最优解
 *
 * @param i 要装入的物品索引
 * @param cw 当前重量
 * @param cv 当前价值
 * @return double 上界值
 */
double bound(int i, int cw, int cv) {
  double res = cv;
  int left = C - cw;
  while (items[i].weight_ <= left && i < M) {
    res += items[i].value_;
    left -= items[i].weight_;
    i++;
  }
  if (i < M) {
    res += left * (items[i].value_ * 1.0 / items[i].weight_);
  }
  return res;
}

/**
 * @brief 约束函数：用于判断当前部分解是否满足基本的约束条件
 *
 * @param i 要装入的物品索引
 * @param cw 当前重量
 * @return true 满足约束函数，可以装入目标物品
 * @return false 不满足约束函数，不能装入目标物品
 */
bool constraint(int i, int cw) { return cw + items[i].weight_ <= C; }

// 优先队列的分支限界法
namespace s1 {

struct compare {
  bool operator()(const Node& n1, const Node& n2) const { return n1.bound_ < n2.bound_; }
};

// 基于节点价值上界比较的优先队列
std::priority_queue<Node, std::vector<Node>, compare> q{};

int solve() {
  int bestValue{0};
  q.emplace(0, 0, 0, bound(0, 0, 0));  // 根节点压入队列
  while (!q.empty()) {
    Node node = q.top();
    q.pop();
    if (node.cl_ == M) {  // 叶子节点
      bestValue = std::max(bestValue, node.cv_);
    } else {              // 非叶子节点
      int nxt_item = node.cl_;                                  // 待装入物品的序号
      double bound1 = bound(nxt_item, node.cw_, node.cv_);      // 装入下个物品的上界值
      double bound0 = bound(nxt_item + 1, node.cw_, node.cv_);  // 不装入下个物品的上界值
      // 装入下个物品
      if (constraint(nxt_item, node.cw_) && bound1 > bestValue) {
        q.emplace(node.cw_ + items[nxt_item].weight_, node.cv_ + items[nxt_item].value_,
                  node.cl_ + 1, bound1);
      }
      // 不装入下个物品
      if (bound0 > bestValue) {
        q.emplace(node.cw_, node.cv_, node.cl_ + 1, bound0);
      }
    }
  }
  return bestValue;
}
};  // namespace s1

namespace s2{
struct compare{
  bool operator()(const Node& n1, const Node& n2) const {
    return n1.cv_ < n2.cv_;
  }
};

// 基于当前价值比较的优先级队列
std::priority_queue<Node, std::vector<Node>, compare> q{};

int solve() {
  int bestValue{0};
  q.emplace(0, 0, 0, bound(0, 0, 0));  // 根节点压入队列
  while (!q.empty()) {
    Node node = q.top();
    q.pop();
    if (node.cl_ == M) {  // 叶子节点
      bestValue = std::max(bestValue, node.cv_);
    } else {              // 非叶子节点
      int nxt_item = node.cl_;                                  // 待装入物品的序号
      double bound1 = bound(nxt_item, node.cw_, node.cv_);      // 装入下个物品的上界值
      double bound0 = bound(nxt_item + 1, node.cw_, node.cv_);  // 不装入下个物品的上界值
      // 装入下个物品
      if (constraint(nxt_item, node.cw_) && bound1 > bestValue) {
        q.emplace(node.cw_ + items[nxt_item].weight_, node.cv_ + items[nxt_item].value_,
                  node.cl_ + 1, bound1);
      }
      // 不装入下个物品
      if (bound0 > bestValue) {
        q.emplace(node.cw_, node.cv_, node.cl_ + 1, bound0);
      }
    }
  }
  return bestValue;
}
};

int main() {
  std::cin >> C >> M;
  for (int i = 0; i < M; i++) {
    int w, v;
    std::cin >> w >> v;
    items.emplace_back(v, w);
  }
  std::sort(items.begin(), items.end(), std::greater<Item>());
  std::cout << s1::solve() << '\n';
}