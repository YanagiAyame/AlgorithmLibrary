#include <vector>
#include <string>
#include <random>

#include <iostream>
#include <set>
#include <utility>

// Could get the hash of a substring.
// Constructor : O(n)
// get : O(1)
template <unsigned kMod>
class RollingHash
{
	using ull = unsigned long long;

  private:
	const int _length;
	std::vector<unsigned> _hash, _pow;
	unsigned _kBase;

  public:
	RollingHash(const std::string &s)
		: _length(s.size()), _hash(_length + 1), _pow(_length + 1, 1)
	{
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());
		const unsigned base = engine() % (kMod - 2) + 2;
		for (int i = 1; i <= _length; ++i)
		{
			_pow[i] = (unsigned)((ull)_pow[i - 1] * base % kMod);
			_hash[i] = (unsigned)(((ull)_hash[i - 1] * base + s[i - 1]) % kMod);
		}
	}

	// Gets the hash of the string[l, r).
	ull get(int l, int r)
	{
		return (_hash[r] - (ull)_hash[l] * _pow[r - l] % kMod + kMod) % kMod;
	}
};

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
// be checked by AOJ(2444).
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444