#pragma once

#include <vector>
#include <tuple>

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