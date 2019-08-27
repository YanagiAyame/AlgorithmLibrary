#define PROBLEM "https://atcoder.jp/contests/wupc2019/tasks/wupc2019_e"
#include <src/Strng/manacher.hpp>

#include <iostream>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
	std::vector<int> h(n), w(m);
	for (int i = 0; i < n; ++i)
	{
		std::string s;
		std::cin >> s;
		for (int j = 0; j < m; ++j)
		{
			if (s[j] == '1')
			{
				dp[i][j] = 1;
				h[i]++;
			}
		}
	}
	Palindrome<int> p(h);
	int a = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		if (p.is(0, i + 1) && p.is(i + 1, n))
		{
			a++;
		}
	}
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (dp[j][i])
				w[i]++;
		}
	}
	Palindrome<int> q(w);
	int b = 0;
	for (int i = 0; i < m - 1; ++i)
	{
		if (q.is(0, i + 1) && q.is(i + 1, m))
		{
			b++;
		}
	}
	std::cout << a * b << std::endl;
}