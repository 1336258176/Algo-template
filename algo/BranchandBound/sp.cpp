/**
 * @file sp.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 使用分支限界法求解单源最短路径问题
 * @version 1.0
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <bits/stdc++.h>

constexpr int INF = 0x4fffffff;  // 无穷大
constexpr int MaxN = 1e4;        // 最大允许的顶点数
int G[MaxN][MaxN]{};             // 邻接矩阵存图
int M, N;                        // 顶点数 边数

struct Node {
  int cl_{};   // 从源点到当前顶点的长度
  int idx_{};  // 当前顶点编号
  bool operator>(const Node& x) const { return cl_ > x.cl_; }
};

// 模拟最小堆
std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q{};

int solve() {
  int minPath{INF};
  q.emplace(0, 1);      // 压入根节点
  while (!q.empty()) {  // 广度优先搜索
    Node node = q.top();
    q.pop();
    if (node.idx_ == M) {  // 叶子节点
      minPath = std::min(minPath, node.cl_);
    } else {  // 非叶子节点
      for (int i = 1; i <= M; i++) {  // 遍历所有相邻顶点
        int l = G[node.idx_][i];
        if (l < INF && l + node.cl_ < minPath) {  // 剪枝
          q.emplace(node.cl_ + l, i);
        }
      }
    }
  }
  return minPath;
}

int main() {
  // 输入默认第一个顶点为起点，最后一个顶点为终点
  std::cin >> M >> N;
  for (int i = 0; i <= M; i++) {
    for (int j = 0; j <= M; j++) {
      G[i][j] = INF;
    }
  }
  for (int i = 0; i < N; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    G[u][v] = w;
  }

  std::cout << solve() << '\n';

  return 0;
}