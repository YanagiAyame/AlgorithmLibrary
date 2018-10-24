#pragma once

#include <vector>

struct Edge {
  int src, dst;
  long long weight;
  Edge(int src, int dst, long long weight)
      : src(src), dst(dst), weight(weight) {}

  bool operator<(const Edge &e) const { return weight > e.weight; }
};

using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
