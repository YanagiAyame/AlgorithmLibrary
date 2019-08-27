#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"
#include <src/DataStructure/union_find.hpp>

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
// Kruskal's algorithm
// Finds a minimum-spanning-tree.
// Returns the sum of the tree's cost and the edges of the tree.
// Complexity : O(E log V)
template <class... Args>
auto Kruskal(const auto &g)
{
	const int n = g.size();
	UnionFind uf(n);
	std::priority_queue<Edge<Args...>> q;
	for (int i = 0; i < n; ++i)
	{
		for (const auto &e : g[i])
		{
			if (i < e.to)
			{
				q.push(e);
			}
		}
	}
	Weight total_cost = 0;
	Graph<Args...> forest(n);
	int forest_size = 0;
	while (forest_size < n - 1 && !q.empty())
	{
		auto e = q.top();
		q.pop();
		if (uf.unite(e.from, e.to))
		{
			forest.AddEdge(e);
			forest_size++;
			total_cost += std::get<0>(e.values);
		}
	}
	return std::make_pair(total_cost, forest);
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	Graph<Weight> g(n);
	for (int i = 0; i < m; ++i)
	{
		int u, v, cost;
		std::cin >> u >> v >> cost;
		g.AddEdge(u, v, cost);
		g.AddEdge(v, u, cost);
	}
	std::cout << Kruskal<Weight>(g).first << std::endl;
}