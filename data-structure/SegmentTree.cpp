/**
 * @file Segment-Tree.cpp
 * @author LyBin (lybin1336258176@outlook.com)
 * @brief 线段树可以在 O(log N)
 * 的时间复杂度内实现单点修改、区间修改(只支持加法)、区间查询（区间求和，求区间最大值，求区间最小值）等操作。
 * @version 1.0
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

const int maxn = 5e5 + 10;
int n{};
int num[maxn]{};
long long tree[maxn << 2]{};
long long lazytag[maxn << 2]{};

/**
 * @brief 第p个节点的左子节点
 *
 * @param p
 * @return int
 */
inline int ls(const int p) { return p << 1; }

/**
 * @brief 第p个节点的右子节点
 *
 * @param p
 * @return int
 */
inline int rs(const int p) { return (p << 1) | 1; }  // 2*p+1

/**
 * @brief 向上传递区间和（即求和）
 *
 * @param p 第p个节点
 */
inline void pushup(const int p) { tree[p] = tree[ls(p)] + tree[rs(p)]; }

/**
 * @brief 为节点p添加懒惰标记
 *
 * @param p 第p个节点
 * @param l 节点p管辖的区间起始点
 * @param r 节点p管辖的区间结束点
 * @param k 节点p内每个值的变化量
 */
inline void addTag(const int p, const int l, const int r, const int k) {
  tree[p] += (r - l + 1) * k;
  lazytag[p] = k;
}

/**
 * @brief 建树
 *
 * @param p 根节点
 * @param l 目标数组的起始点
 * @param r 目标数组的结束点
 */
void build(const int p, const int l, const int r) {
  if (l == r) {
    tree[p] = num[l];
    return;
  }
  const int mid = (l + r) >> 1;
  build(ls(p), l, mid);
  build(rs(p), mid + 1, r);
  pushup(p);
}

/**
 * @brief 区间修改（区间加上某个值）
 *
 * @param p 节点p
 * @param l p管辖的区间起始点
 * @param r p管辖的区间结束点
 * @param ql 修改区间起始点
 * @param qr 修改区间结束点
 * @param k 变化量
 */
void update(const int p, const int l, const int r, const int ql, const int qr, const int k) {
  if (ql <= l && r <= qr) {
    addTag(p, l, r, k);
    return;
  }
  const int mid = (l + r) >> 1;
  if (lazytag[p]) {
    addTag(ls(p), l, mid, lazytag[p]);
    addTag(rs(p), mid + 1, r, lazytag[p]);
    lazytag[p] = 0;
  }
  if (ql <= mid) {
    update(ls(p), l, mid, ql, qr, k);
  }
  if (mid + 1 <= qr) {
    update(rs(p), mid + 1, r, ql, qr, k);
  }
  pushup(p);
}

/**
 * @brief 线段树的区间查询
 *
 * @param p 线段树的根节点
 * @param l 目标数组的起始点
 * @param r 目标数组的结束点
 * @param ql 待查区间的起始点
 * @param qr 待查区间的结束点
 * @return int
 */
int query(const int p, const int l, const int r, const int ql, const int qr) {
  if (ql <= l && qr >= r) return tree[p];
  int sum{};
  const int mid = (l + r) >> 1;
  if (lazytag[p]) {
    addTag(ls(p), l, mid, lazytag[p]);
    addTag(rs(p), mid + 1, r, lazytag[p]);
    lazytag[p] = 0;
  }
  if (ql <= mid) sum += query(ls(p), l, mid, ql, qr);
  if (mid + 1 <= qr) sum += query(rs(p), mid + 1, r, ql, qr);
  return sum;
}

int main() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> num[i];
  }
  build(1, 0, n - 1);
  for (int i = 1; i < 20; i++) {
    std::cout << tree[i] << " ";
  }
  std::cout << '\n';
  std::cout << query(1, 0, n - 1, 1, 3) << '\n';
  update(1, 0, n - 1, 1, 4, 2);
  for (int i = 1; i < 20; i++) {
    std::cout << tree[i] << " ";
  }
  std::cout << '\n';
  std::cout << query(1, 0, n - 1, 0, 3) << '\n';

  return 0;
}
