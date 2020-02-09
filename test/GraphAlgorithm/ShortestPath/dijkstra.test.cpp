#ifdef __clang__
#define IGNORE
#else
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"
#endif
#include <src/GraphAlgorithm/ShortestPath/dijkstra.hpp>

#include <iostream>

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