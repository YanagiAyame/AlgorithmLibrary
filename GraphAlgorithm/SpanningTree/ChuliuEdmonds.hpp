#pragma once

#include "template.hpp"

constexpr int INF = 1e8;

long long ChuLiu_Edmonds(const Graph &g, int root) {
  const int V = g.size();
  Edges mins(V, Edge(-1, -1, INF));
  //各頂点に対し入ってくる最小の辺を選ぶ
  for (auto es : g) {
    for (auto e : es) {
      if (e.weight < mins[e.dst].weight) {
        mins[e.dst] = e;
      }
    }
  }
  mins[root] = Edge(-1, -1, -1);
  /*for(auto e:mins){
      if(e.weight==INF)return -1;
  }*/
  std::vector<int> group(V, 0);
  std::vector<bool> isCycle(V, false);
  int count = 0;
  std::vector<bool> used(V, false);
  //グループ分け
  for (int i = 0; i < V; ++i) {
    if (used[i])
      continue;
    std::vector<int> chain;
    int cursor = i;
    //親をたどっていく
    while (cursor != -1 && !used[cursor]) {
      used[cursor] = true;
      chain.push_back(cursor);
      cursor = mins[cursor].src;
    }
    //閉路の可能性あり
    if (cursor != -1) {
      bool inCycle = false;
      for (int j = 0; j < chain.size(); ++j) {
        group[chain[j]] = count;
        if (chain[j] == cursor) {
          isCycle[count] = true;
          inCycle = true;
        }
        if (!inCycle)
          ++count;
      }
      if (inCycle)
        ++count;
    } else { //閉路でない
      for (int j = 0; j < chain.size(); ++j) {
        group[chain[j]] = count++;
      }
    }
  }
  //グループ分け終了
  //閉路がないとき
  if (count == V) {
    long long ans = 1;
    for (int i = 0; i < V; ++i) {
      ans += mins[i].weight;
    }
    return ans;
  }
  //縮約した閉路のコスト合計
  long long res = 0;
  for (int i = 0; i < V; ++i) {
    if (i != root && isCycle[group[i]]) {
      res += mins[i].weight;
    }
  }
  //閉路を１つの頂点にしてグラフを組みなおす
  Graph ng(count);
  for (auto es : g) {
    for (auto e : es) {
      int to = e.dst;
      int gfrom = group[e.src];
      int gto = group[e.dst];
      if (gfrom == gto) {
        continue;
      } else if (isCycle[gto]) {
        ng[gfrom].emplace_back(gfrom, gto, e.weight - mins[to].weight);
      } else {
        ng[gfrom].emplace_back(gfrom, gto, e.weight);
      }
    }
  }
  return res + ChuLiu_Edmonds(ng, group[root]);
}
