/**
 * @file dijkstra-2.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 优先队列实现dijkstra算法
 * @version 1.0
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>

constexpr int MaxN = 1e5;
constexpr int INF = 0x4fffffff;

struct Edge {
  int v_{};  // 目标点
  int w_{};  // 权值
};

struct Node {
  int dis_{};  // 源点到目标点的路径长度
  int u_{};    // 该节点所表示图上的顶点编号

  bool operator>(const Node& x) const { return dis_ > x.dis_; }
};

int M, N;                   // 顶点数 边数
int vis[MaxN]{};            // 从源点到目标点的最短路长度是否已知
int dis[MaxN]{};            // 记录从源点到目标点的最短路长度
std::vector<Edge> e[MaxN];  // 存储目标点的所有出边
std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q{};  // 基于路径长度的最小堆

/**
 * @brief dijkstra算法
 *
 * @param s 起点
 * @param t 终点
 * @return int 最短路长度
 */
int dijkstra(int s, int t) {
  // init
  for (int i = 1; i <= M; i++) {
    dis[i] = INF;
    vis[i] = 0;
  }

  dis[s] = 0;
  q.emplace(0, s);
  while (!q.empty()) {
    int u = q.top().u_;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (const auto edge : e[u]) {  // 遍历顶点u的所有出边
      int v = edge.v_;
      int w = edge.w_;
      if (dis[v] > dis[u] + w) {  // 松弛
        dis[v] = dis[u] + w;
        q.emplace(dis[v], v);
      }
    }
  }
  return dis[t];
}

int main() {
  std::cin >> M >> N;
  for (int i = 0; i < N; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    e[u].emplace_back(v, w);
  }

  std::cout << dijkstra(1, M) << std::endl;
  
  return 0;
}
