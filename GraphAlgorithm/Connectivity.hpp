#include <bits/stdc++.h>

using namespace std;

struct Edge
{
	int src, dst;
	Edge(int f, int t)
	{
		src = f;
		dst = t;
	}
};

using Edges = vector<Edge>;
using Graph = vector<Edges>;

//２重辺連結成分と橋のリストを求める
pair<vector<int>, Edges> bridge(const Graph &g)
{
	const int n = g.size();
	int idx = 0, s = 0, t = 0, k = 0;
	vector<int> ord(n, -1), onS(n), stk(n), roots(n), cmp(n);
	Edges brdg;
	function<void(int, int)> dfs = [&](int v, int u) {
		ord[v] = idx++;
		stk[s++] = v;
		onS[v] = true;
		roots[t++] = v;
		for (auto &e : g[v])
		{
			int w = e.dst;
			if (ord[w] == -1)
				dfs(w, v);
			else if (u != w && onS[w])
				while (ord[roots[t - 1]] > ord[w])
					--t;
		}
		if (v == roots[t - 1])
		{
			brdg.emplace_back(u, v);
			while (true)
			{
				int w = stk[--s];
				onS[w] = false;
				cmp[w] = k;
				if (v == w)
					break;
			}
			--t;
			++k;
		}
	};
	for (int u = 0; u < n; ++u)
	{
		if (ord[u] == -1)
		{
			dfs(u, n);
			brdg.pop_back();
		}
	}
	return make_pair(cmp, brdg);
}
/*
int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for (int i = 0; i < E; ++i) {
    int s, t;
    cin >> s >> t;
    g[s].emplace_back(s, t);
    g[t].emplace_back(t, s);
  }
  Edges es = bridge(g).second;
  vector<pair<int, int>> v;
  for (auto x : es) {
    if (x.from > x.to)
      v.push_back(pair<int, int>(x.to, x.from));
    else
      v.push_back(pair<int, int>(x.from, x.to));
  }
  sort(v.begin(), v.end());
  for (auto x : v) {
    cout << x.first << " " << x.second << endl;
  }
}*/

//関節点を求める
//関節点のリストである関節点uがk個の２重頂点連結成分をつないでいると、k-1個のuが入る
vector<int> ArticulationPoint(const Graph &g)
{
	int n = g.size(), idx = 0;
	vector<int> low(n), ord(n), art;
	function<void(int)> dfs = [&](int v) {
		low[v] = ord[v] = ++idx;
		for (auto &e : g[v])
		{
			int w = e.dst;
			if (ord[w] == 0)
			{
				dfs(w);
				low[v] = min(low[v], low[w]);
				if ((ord[v] == 1 && ord[w] != 2) || (ord[v] != 1 && low[w] >= ord[v]))
					art.push_back(v);
			}
			else
				low[v] = min(low[v], ord[w]);
		}
	};
	for (int u = 0; u < n; ++u)
	{
		if (ord[u] == 0)
		{
			idx = 0;
			dfs(u);
		}
	}
	return art;
}
/*
int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for (int i = 0; i < E; ++i) {
    int s, t;
    cin >> s >> t;
    g[s].emplace_back(s, t);
    g[t].emplace_back(t, s);
  }
  vector<int> v = ArticulationPoint(g);
  sort(v.begin(), v.end());
  int pre = -1;
  for (auto x : v) {
    if (pre == x) continue;
    cout << x << endl;
    pre = x;
  }
}*/

//強連結成分のリスト  ちゃんと縮小されている
vector<int> tarjan(const Graph &g)
{
	int n = g.size(), idx = 0, k = 0, s = 0;
	vector<int> ord(n, -1), low(n), onS(n), cmp(n), stk(n);
	function<void(int)> dfs;
	dfs = [&](int v) {
		ord[v] = low[v] = idx++;
		stk[s++] = v;
		onS[v] = true;
		for (auto &e : g[v])
		{
			int w = e.dst;
			if (ord[w] == -1)
			{
				dfs(w);
				low[v] = min(low[v], low[w]);
			}
			else if (onS[w])
			{
				low[v] = min(low[v], ord[w]);
			}
		}
		if (low[v] == ord[v])
		{
			while (1)
			{
				int w = stk[--s];
				onS[w] = false;
				cmp[w] = k;
				if (w == v)
					break;
			}
			++k;
		}
	};
	for (int v = 0; v < n; ++v)
		if (ord[v] == -1)
			dfs(v);
	return cmp;
}
/*
int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for (int i = 0; i < E; ++i) {
    int s, t;
    cin >> s >> t;
    g[s].emplace_back(s, t);
  }
  int Q;
  cin >> Q;
  vector<int> SCC = tarjan(g);
  for (int i = 0; i < Q; ++i) {
    int u, v;
    cin >> u >> v;
    // SCC[u]==SCC[v] => SCC[u]とSCC[v]が同じ強連結成分に含まれる
    cout << (SCC[u] == SCC[v]) << endl;
  }
}*/

// be checked by aoj GRL