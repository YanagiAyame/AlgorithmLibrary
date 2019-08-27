#pragma once
#include <src/GraphAlgorithm/graph_type.hpp>

#include <utility>
#include <vector>
#include <algorithm>

//再帰ラムダ用テンプレート
template <typename F>
class FixPoint : F
{
public:
	explicit constexpr FixPoint(F &&f) noexcept
		: F(std::forward<F>(f))
	{
	}

	template <typename... Args>
	constexpr decltype(auto)
	operator()(Args &&... args) const
	{
		return F::operator()(*this, std::forward<Args>(args)...);
	}
};

template <typename F>
static inline constexpr decltype(auto)
makeFixPoint(F &&f) noexcept
{
	return FixPoint<F>{std::forward<F>(f)};
}

//トポロジカル順序でソートされた、頂点集合の配列を返す
template <typename G>
auto TopologicalSort(const G &g)
{
	const int kSize = g.size();
	std::vector<int> sorted;
	sorted.reserve(kSize);
	std::vector<bool> visited(kSize, false);
	auto topo_dfs = makeFixPoint([&](auto f, int n) -> void {
		if (!visited[n])
		{
			visited[n] = true;
			for (const auto &e : g[n])
			{
				f(e.to);
			}
			sorted.push_back(n);
		}
	});
	for (int i = 0; i < kSize; ++i)
	{
		topo_dfs(i);
	}
	std::reverse(sorted.begin(), sorted.end());
	return sorted;
}