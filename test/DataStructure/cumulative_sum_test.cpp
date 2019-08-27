#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0022"
#include <src/DataStructure/cumulative_sum.hpp>

#include <iostream>

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