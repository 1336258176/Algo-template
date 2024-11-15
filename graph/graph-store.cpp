/**
 * @file graph-store.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 图的存储
 * @version 0.2
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

/* -------------------------------------------- 链式前向星 ------------------------------------------- */
namespace s1 {
const int MaxN = 1e4 + 10;

struct Edge {
  int to;    // 指向的节点
  int w;     // 权重
  int next;  // 该边起点的上一跳边
};

Edge e[MaxN];      // 边集
int head[MaxN]{};  // head[i]表示节点i的最后一个边序号
int cnt{1};        // 记录边数，边序号从1开始

void addEdge(int u, int v, int w) {
  e[cnt].to = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt++;
}
};  // namespace s1

int main() {
  int n, m;  // n个点 m条边
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    s1::addEdge(u, v, w);
  }

  // 链式前向星遍历图
  for (int i = 1; i <= n; i++) {
    printf("node-%d\n", i);
    for (int j = s1::head[i]; j != 0; j = s1::e[j].next) {
      printf("  %d->%d %d\n", i, s1::e[j].to, s1::e[j].w);
    }
    std::cout << std::endl;
  }

  return 0;
}