#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A"
#include <src/GraphAlgorithm/SpanningTree/kruskal.hpp>

#include <iostream>

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