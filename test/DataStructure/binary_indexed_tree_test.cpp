#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <../../src/DataStructure/binary_indexed_tree.hpp>

#include <vector>
#include <iostream>

// Runs add queries and range sum queries.
// Add : O(log n)
// Sum : O(log n)
template <class Abel>
class BinaryIndexedTree
{
	const int size_;
	std::vector<Abel> data_;

public:
	BinaryIndexedTree(int size) : size_(size), data_(size + 1, 0) {}

	// data[target] += num
	void Add(int target, Abel num)
	{
		for (int index = target + 1; index <= size_; index += index & -index)
			data_[index] += num;
	}

	// Gets the sum of data[0, right)
	Abel Sum(int right)
	{
		Abel sum = 0;
		for (int index = right; index > 0; index -= index & -index)
			sum += data_[index];
		return sum;
	}

	// Gets the sum of data[left, right)
	Abel Sum(int left, int right) { return Sum(right) - Sum(left); }
};

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