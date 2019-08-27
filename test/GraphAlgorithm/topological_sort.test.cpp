#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B"
#include <src/GraphAlgorithm/graph_type.hpp>
#include <src/GraphAlgorithm/topological_sort.hpp>

#include <iostream>

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