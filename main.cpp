#include <iostream>

const int maxn = 5e5 + 10;
int n{};
int num[maxn]{};
long long tree[maxn << 2]{};
long long lazytag[maxn << 2]{};

inline int ls(const int p) { return p << 1; }

inline int rs(const int p) { return (p << 1) | 1; }

inline void pushup(const int p) { tree[p] = tree[ls(p)] + tree[rs(p)]; }

inline void addTag(const int p, const int l, const int r, const int k) {
  tree[p] += (r - l + 1) * k;
  lazytag[p] = k;
}

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
  int n, m;
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    std::cin >> num[i];
  }
  build(1, 0, n - 1);
  for (int i = 0; i < m; i++) {
    int op{};
    std::cin >> op;
    if (op == 1) {
      int x, y, k;
      std::cin >> x >> y >> k;
      update(1, 0, n - 1, x - 1, y - 1, k);
    } else {
      int x, y;
      std::cin >> x >> y;
      std::cout << query(1, 0, n - 1, x - 1, y - 1) << '\n';
    }
  }

  return 0;
}
