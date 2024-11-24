/**
 * @file dijkstra-1.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 暴力Dijkstra
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
  int v, w;
};

int M, N;
int vis[MaxN];
int dis[MaxN];
std::vector<Edge> e[MaxN];

int dijkstra(int s, int t) {
  // init
  for (int i = 1; i <= M; i++) {
    dis[i] = INF;
    vis[i] = 0;
  }

  dis[s] = 0;
  for (int i = 1; i <= M; i++) {  // 由于有M个顶点，所以找到从源点到每个顶点的最短路需要M次遍历
    int u = 0;
    int mind = INF;

    // 遍历所有顶点，找到距离源点最短的顶点u
    for (int j = 1; j <= M; j++) {
      if (!vis[j] && dis[j] < mind) {
        u = j;
        mind = dis[j];
      }
    }

    vis[u] = 1;
    for (auto edge : e[u]) {  // 遍历顶点u的所有出边
      int v = edge.v;
      int w = edge.w;
      if (dis[v] > dis[u] + w) {  // 松弛
        dis[v] = dis[u] + w;
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

  std::cout << dijkstra(1, M) << '\n';
  
  return 0;
}
