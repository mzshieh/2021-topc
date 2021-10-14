#include <bits/stdc++.h>
using namespace std;
#define K 16

using LL = long long;
using pii = pair<int, int>;
const LL INF = 1e12;
struct Dinic {
  struct Node : vector<int> { int d, p; };
  struct Edge { int u, v; LL f, c; };

  vector<Node> N; vector<Edge> E;

  void addNode() {
    N.emplace_back();
  }

  size_t numOfNode() const {
    return N.size();
  }

  void addEdge(int u, int v, LL c) {
    int m = E.size();
    E.emplace_back(u, v, 0, c); N[u].push_back(m++);
    E.emplace_back(v, u, 0, c); N[v].push_back(m++);
  }

  size_t numOfEdge() const {
    return E.size() >> 1;
  }

  void clear() {
    for (auto &e : E) e.f = 0;
  }

  bool bfs(int s, int t) {
    for (auto &v : N) v.d = -1, v.p = 0;
    queue<int> q; q.push(s); N[s].d = 0;
    while (q.size()) { int u = q.front(); q.pop();
      for (auto &e : N[u]) { int v = E[e].v;
        if (!~N[v].d && E[e].f < E[e].c)
          q.push(v), N[v].d = N[u].d + 1;
      }
    }
    return ~N[t].d;
  }

  LL dfs(int u, int t, LL a) {
    if (u == t || !a) return a; LL flow = 0;
    for (int &p = N[u].p; p < N[u].size(); p++) {
      auto e = N[u][p], v = E[e].v;
      if (N[u].d + 1 != N[v].d) continue;
      LL f = dfs(v, t, min(a, E[e].c - E[e].f));
      E[e].f += f; E[e ^ 1].f -= f; flow += f; a -= f;
      if (!a) break;
    }
    return flow;
  }

  LL run(int s, int t) {
    LL flow = 0; clear();
    while (bfs(s, t)) flow += dfs(s, t, INF);
    return flow;
  }
};

struct Q {
  int u, i, v, j;
};

int getBit(int u, int i) {
  return (u >> i) & 1;
}
#define encode(u, i) (i * n + u)
tuple<int, int, int, Dinic, vector<Q>, vector<int>> init() {
  int n, m; cin >> n >> m;

  auto solver = Dinic();
  for (int i = 0; i < K * n + 2; i++)
    solver.addNode();
  int s = K * n, t = K * n + 1;
  
  while (m--) {
    int u, v; cin >> u >> v;
    for (int i = 0; i < K; i++)
      solver.addEdge(encode(u, i), encode(v, i), 1);
  }

  vector<int> d(n * K);
  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    if (v == -1)
      continue;
    for (int j = 0; j < K; j++) {
      if (getBit(v, j) == 0)
        solver.addEdge(s, encode(i, j), INF), d[encode(i, j)] = -1;
      else
        solver.addEdge(encode(i, j), t, INF), d[encode(i, j)] = 1;
    }
  }

  vector<Q> qs;
  int q; cin >> q; while (q--) {
    int t, u, i, v, j;
    cin >> t >> u >> i >> v >> j;
    if (t == 0)
      solver.addEdge(encode(u, i), encode(v, j), INF);
    else
      qs.push_back({u, i, v, j});
  }

  return {n, s, t, solver, qs, d};
}

void gg() {
  cout << -1 << '\n';
  exit(0);
}

tuple<vector<int>, vector<int>> bipartite(auto &G, int s, auto &d, auto &vis) {
  queue<int> q; q.push(s); vis[s] = 1;
  if (d[s] == 0) d[s] = 1;
  vector<int> vec[2];
  while (q.size()) {
    int p = q.front(); q.pop();
    vec[d[p] == 1].push_back(p);
    for (auto &v : G[p]) {
      if (d[v] != 0) {
        if (d[v] == d[p])
          gg();
      } else {
        d[v] = -d[p];
        vis[v] = 1;
        q.push(v);
      }
    }
  }
  return {vec[0], vec[1]};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  auto [n, s, t, base, qs, d] = init();

  vector<vector<int>> G(n * K);
  for (auto &q : qs) {
    G[encode(q.u, q.i)].push_back(encode(q.v, q.j));
    G[encode(q.v, q.j)].push_back(encode(q.u, q.i));
  }

  vector<int> vis(n * K, 0);
  for (int i = 0; i < n * K; i++) {
    if (vis[i] or d[i] == 0 or G[i].empty())
      continue;

    auto [v1, v2] = bipartite(G, i, d, vis);
    for (auto &v : v1)
      base.addEdge(s, v, INF);
    for (auto &v : v2)
      base.addEdge(v, t, INF);
  }

  for (int i = 0; i < n * K; i++) {
    if (vis[i] or d[i] != 0 or G[i].empty())
      continue;

    auto [v1, v2] = bipartite(G, i, d, vis);
    auto c1 = base, c2 = base;
    for (auto &v : v1)
      c1.addEdge(s, v, INF), c2.addEdge(v, t, INF);
    for (auto &v : v2)
      c1.addEdge(v, t, INF), c2.addEdge(s, v, INF);

    auto f1 = c1.run(s, t);
    auto f2 = c2.run(s, t);
    if (min({INF, f1, f2}) == INF)
      gg();

    if (f1 < f2)
      base = c1;
    else
      base = c2;
    base.clear();
  }

  auto f = base.run(s, t);
  if (min(INF, f) == INF)
    gg();
  cout << f << '\n';
}
