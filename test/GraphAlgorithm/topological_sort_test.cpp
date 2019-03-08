#include <vector>
#include <tuple>

#include <utility>
#include <algorithm>
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

//再帰ラムダ用テンプレート
template <typename F>
class FixPoint : F
{
  public:
	explicit constexpr FixPoint(F &&f) noexcept
		: F(std::forward<F>(f))
	{
	}

	template <typename... Args>
	constexpr decltype(auto)
	operator()(Args &&... args) const
	{
		return F::operator()(*this, std::forward<Args>(args)...);
	}
};

template <typename F>
static inline constexpr decltype(auto)
makeFixPoint(F &&f) noexcept
{
	return FixPoint<F>{std::forward<F>(f)};
}

//トポロジカル順序でソートされた、頂点集合の配列を返す
template <typename G>
auto TopologicalSort(const G &g)
{
	const int kSize = g.size();
	std::vector<int> sorted;
	sorted.reserve(kSize);
	std::vector<bool> visited(kSize, false);
	auto topo_dfs = makeFixPoint([&](auto f, int n) -> void {
		if (!visited[n])
		{
			visited[n] = true;
			for (const auto &e : g[n])
			{
				f(e.to);
			}
			sorted.push_back(n);
		}
	});
	for (int i = 0; i < kSize; ++i)
	{
		topo_dfs(i);
	}
	std::reverse(sorted.begin(), sorted.end());
	return sorted;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	Graph<> g(n);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		std::cin >> u >> v;
		g.AddEdge(u, v);
	}
	auto ans = TopologicalSort(g);
	for (auto x : ans)
	{
		std::cout << x << std::endl;
	}
}
// be checked by AOJ(GRL-4-B).
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B