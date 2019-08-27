#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444"
#include <src/String/rolling_hash.hpp>

#include <iostream>
#include <set>
#include <utility>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::string s;
	std::cin >> s;
	RollingHash<1000000009> hashed_str1(s);
	RollingHash<1000000007> hashed_str2(s);
	int r = 1, l = 1;
	std::set<std::pair<unsigned, unsigned>> sub;
	for (int i = 0; i < m; ++i)
	{
		std::string q;
		std::cin >> q;
		if (q == "L++")
		{
			l++;
		}
		if (q == "L--")
		{
			l--;
		}
		if (q == "R++")
		{
			r++;
		}
		if (q == "R--")
		{
			r--;
		}
		sub.insert({hashed_str1.get(l - 1, r), hashed_str2.get(l - 1, r)});
	}
	std::cout << sub.size() << std::endl;
}