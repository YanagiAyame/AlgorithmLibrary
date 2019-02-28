#include <vector>
#include <tuple>
#include <queue>
#include <utility>
#include <iostream>

// Graph template (start)
template <class... Args>
struct Edge
{
	int from, to;
	std::tuple<Args...> values;
	Edge(int from, int to, Args... values)
		: from(from), to(to), values(values...) {}
};

template <class E>
auto operator<(const E &e, const E &f)
{
	return e.values > f.values;
}

template <class... Args>
class Graph
{
	using Edges = std::vector<Edge<Args...>>;
	std::vector<Edges> graph_;

  public:
	Graph(int n) : graph_(n) {}
	std::size_t size() { return graph_.size(); };
	std::size_t size() const { return graph_.size(); };
	auto &operator[](unsigned int x) { return graph_[x]; }
	const auto &operator[](unsigned int x) const { return graph_[x]; }
	void AddEdge(int s, int t, Args... v) { graph_[s].emplace_back(s, t, v...); }
	void AddEdge(Edge<Args...> e) { graph_[e.from].push_back(e); }
};
// Graph template (end)

using Weight = long long;
constexpr long long kWEIGHT_INF = 1e18;

template <class... Args>
auto Dijkstra(const auto &g, int s)
{
	const int n = g.size();
	std::vector<Weight> dist(n, kWEIGHT_INF); //各点における始点sからの距離が入る
	std::vector<int> prev(n, -1);			  //各点における最短路の親が入る
	dist[s] = 0;
	std::priority_queue<Edge<Weight>> q;
	q.emplace(-2, s, dist[s]);
	while (!q.empty())
	{
		auto now = q.top();
		q.pop();
		int parent = now.from, u = now.to;
		if (prev[u] != -1)
		{
			continue;
		}
		else
		{
			prev[u] = parent;
		}
		for (const auto &e : g[u])
		{
			int v = e.to;
			auto cost = std::get<0>(e.values);
			if (dist[v] > dist[u] + cost)
			{
				dist[v] = dist[u] + cost;
				q.emplace(u, v, dist[v]);
			}
		}
	}
	return std::make_pair(dist, prev);
}

int main()
{
	int n, m, root;
	std::cin >> n >> m >> root;
	Graph<Weight> g(n);
	for (int i = 0; i < m; ++i)
	{
		int s, t;
		Weight d;
		std::cin >> s >> t >> d;
		g.AddEdge(s, t, d);
	}
	auto dist = Dijkstra(g, root).first;
	for (int i = 0; i < n; ++i)
	{
		if (dist[i] == kWEIGHT_INF)
			std::cout << "INF" << std::endl;
		else
			std::cout << dist[i] << std::endl;
	}
}
// be checked by AOJ(GRL-1-A).
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A