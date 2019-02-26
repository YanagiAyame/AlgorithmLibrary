#include <vector>
#include <iostream>
#include <cmath>

// Runs range sum queries only.
// Sum : O(1)
template <class Abel>
class CumulativeSum
{
	std::vector<Abel> sums_;

  public:
	CumulativeSum(const std::vector<Abel> &data) : sums_(data)
	{
		sums_.insert(sums_.begin(), Abel(0));
		for (int i = 1; i < (int)sums_.size(); ++i)
		{
			sums_[i] += sums_[i - 1];
		}
	}

	// Gets the sum of data[0, right)
	Abel Sum(int right) { return sums_[right]; }

	// Gets the sum of data[left, right)
	Abel Sum(int left, int right) { return Sum(right) - Sum(left); }
};

int main()
{
	int n;
	while (std::cin >> n, n)
	{
		std::vector<int> data(n);
		for (int i = 0; i < n; ++i)
		{
			std::cin >> data[i];
		}
		CumulativeSum<int> cumulative_sum(data);
		int ans = -1e9;
		for (int left = 0; left < n; ++left)
		{
			for (int right = left + 1; right <= n; ++right)
			{
				ans = std::max(ans, cumulative_sum.Sum(left, right));
			}
		}
		std::cout << ans << std::endl;
	}
}
// be checked by AOJ(0022)
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0022