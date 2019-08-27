#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <src/DataStructure/binary_indexed_tree.hpp>

#include <iostream>

int main()
{
	int n, q;
	std::cin >> n >> q;
	BinaryIndexedTree<int> binary_indexed_tree(n);
	for (int i = 0; i < q; ++i)
	{
		int com, x, y;
		std::cin >> com >> x >> y;
		x--;
		if (com)
		{
			std::cout << binary_indexed_tree.Sum(x, y) << std::endl;
		}
		else
		{
			binary_indexed_tree.Add(x, y);
		}
	}
}