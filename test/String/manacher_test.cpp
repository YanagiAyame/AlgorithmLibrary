#include <string>
#include <vector>
#include <cassert>

#include <iostream>

template <typename T>
class Palindrome
{
	const int size_;
	std::vector<int> manacher_data_;

	std::vector<T> insert_doll(const auto &str)
	{
		const int str_size = str.size();
		if (str_size <= 1)
		{
			return str;
		}
		std::vector<T> res;
		res.push_back(str[0]);
		for (int i = 1; i < str_size; i++)
		{
			res.push_back('$');
			res.push_back(str[i]);
		}
		return res;
	}

	std::vector<int> manacher(const auto &str)
	{
		const int str_size = str.size();
		std::vector<int> res(str_size + 1);
		for (int i = 0, j = 0; i < str_size;)
		{
			while (i - j >= 0 && i + j < str_size && str[i - j] == str[i + j])
				j++;
			res[i] = j;
			int k = 1;
			while (i - k >= 0 && i + k < str_size && k + res[i - k] < j)
			{
				res[i + k] = res[i - k];
				k++;
			}
			i += k;
			j -= k;
		}
		return res;
	}

  public:
	Palindrome(const std::vector<T> &str) : size_(str.size()), manacher_data_(manacher(insert_doll(str))) {}

	// Gets whether S[i, j) is a palindrome.
	bool is(int i, int j)
	{
		assert(0 <= i && i < j && j <= size_);
		return manacher_data_[i + j - 1] >= j - i;
	}
};

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
// verified
// https://atcoder.jp/contests/wupc2019/tasks/wupc2019_e