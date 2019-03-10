#include <vector>
#include <functional>

#include <iostream>
#include <utility>

// Segment tree with lazy propagation.
template <class Data, class Operator>
class LazySegmentTree
{
	int size_, height_;

	// (Data, F) is a monoid.
	std::vector<Data> data_;
	using F = std::function<Data(Data, Data)>;
	const F f_;
	const Data data_id_;

	// This is operation.
	using G = std::function<Data(Data, Operator)>;
	const G g_;

	// (Operator, H) is a monoid.
	std::vector<Operator> lazy_;
	using H = std::function<Operator(Operator, Operator)>;
	const H h_;
	const Operator operator_id_;

	void init(int num)
	{
		size_ = 1;
		height_ = 0;
		while (size_ < num)
		{
			size_ <<= 1;
			++height_;
		}
		data_.assign(size_ << 1, data_id_);
		lazy_.assign(size_ << 1, operator_id_);
	}

	inline Data reflect(int k)
	{
		if (lazy_[k] == operator_id_)
		{
			return data_[k];
		}
		else
		{
			return g_(data_[k], lazy_[k]);
		}
	}

	inline void eval(int k)
	{
		if (lazy_[k] == operator_id_)
			return;
		lazy_[(k << 1) | 0] = h_(lazy_[(k << 1) | 0], lazy_[k]);
		lazy_[(k << 1) | 1] = h_(lazy_[(k << 1) | 1], lazy_[k]);
		data_[k] = reflect(k);
		lazy_[k] = operator_id_;
	}

	inline void thrust(int k)
	{
		for (int i = height_; i > 0; --i)
		{
			eval(k >> i);
		}
	}

	inline void recalc(int k)
	{
		while (k >>= 1)
		{
			data_[k] = f_(reflect((k << 1) | 0), reflect((k << 1) | 1));
		}
	}

  public:
	LazySegmentTree(F f, G g, H h, Data data_id, Operator operator_id)
		: f_(f), data_id_(data_id), g_(g), h_(h), operator_id_(operator_id) {}

	void build(const std::vector<Data> &elements)
	{
		const int num = elements.size();
		init(num);
		for (int i = 0; i < num; ++i)
		{
			data_[size_ + i] = elements[i];
		}
		for (int i = size_ - 1; i > 0; --i)
		{
			data_[i] = f_(data_[(i << 1) | 0], data_[(i << 1) | 1]);
		}
	}

	void update(int a, int b, Operator x)
	{
		thrust(a += size_);
		thrust(b += size_ - 1);
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1)
			{
				lazy_[l] = h_(lazy_[l], x);
				++l;
			}
			if (r & 1)
			{
				--r;
				lazy_[r] = h_(lazy_[r], x);
			}
		}
		recalc(a);
		recalc(b);
	}

	void set(int a, Data x)
	{
		thrust(a += size_);
		data_[a] = x;
		lazy_[a] = operator_id_;
		recalc(a);
	}

	Data query(int a, int b)
	{
		thrust(a += size_);
		thrust(b += size_ - 1);
		Data vl = data_id_, vr = data_id_;
		for (int l = a, r = b + 1; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1)
			{
				vl = f_(vl, reflect(l++));
			}
			if (r & 1)
			{
				vr = f_(reflect(--r), vr);
			}
		}
		return f_(vl, vr);
	}
};

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
	// range update, range min
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
// be checked by AOJ(DSL-2-G).
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G