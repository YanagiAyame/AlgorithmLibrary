#ifdef __clang__
#define IGNORE
#else
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"
#endif
#include <src/DataStructure/lazy_segment_tree.hpp>

#include <iostream>
#include <utility>

int main()
{
	int n, q;
	std::cin >> n >> q;
	// range add, range sum
	using ll = long long;
	using P = std::pair<ll, ll>;
	auto f = [](P a, P b) {
		return P(a.first + b.first, a.second + b.second);
	};
	auto g = [](P a, ll b) {
		return P(a.first + b * a.second, a.second);
	};
	auto h = [](ll a, ll b) { return a + b; };
	LazySegmentTree<P, ll> seg_tree(f, g, h, P(0, 0), 0);
	seg_tree.build(std::vector<P>(n, P(0, 1)));
	/*
	// range add, range min
	auto f = [](ll a, ll b) {
		return std::min(a, b);
	};
	auto g = [](ll a, ll b) {
		return a + b;
	};
	auto h = [](ll a, ll b) { return a + b; };
	LazySegmentTree<ll, ll> seg_tree(f, g, h, 1e12, 0);
	seg_tree.build(std::vector<ll>(n, 0));
	*/
	/*
	// range update, range min
	auto f = [](ll a, ll b) {
		return std::min(a, b);
	};
	auto g = [](ll a, ll b) {
		if (b == 1e12)
			return a;
		else
			return b;
	};
	auto h = [](ll a, ll b) { return b; };
	LazySegmentTree<ll, ll> seg_tree(f, g, h, 1LL << 31, 1LL << 31);
	seg_tree.build(std::vector<ll>(n, (1LL << 31) - 1));
	*/
	for (int i = 0; i < q; ++i)
	{
		int c, s, t;
		ll x;
		std::cin >> c;
		if (c)
		{
			std::cin >> s >> t;
			std::cout << seg_tree.query(s - 1, t).first << std::endl;
		}
		else
		{
			std::cin >> s >> t >> x;
			seg_tree.update(s - 1, t, x);
		}
	}
}
// (cf.)
// RAQ, RMQ
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H
// RUQ, RMQ
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F