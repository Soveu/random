#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

Graph reversed(const Graph& g) {
  Graph res(g.size());

  for(int i=0; i<g.size(); ++i) {
    for(const auto& children : g[i]) {
      res[children].push_back(i);
    }
  }

  return res;
}

std::vector<int> dfs(const Graph& g) {
  const auto grev = reversed(g);
  std::vector<int> res(g.size());

  for(int i=0; i<g.size(); ++i) {
    std::vector<bool> visited(g.size());
    std::vector<int> stack;

    stack.push_back(i);
    visited[i] = true;
    while(!stack.empty()) {
      auto n = stack.back(); stack.pop_back();

      for(const auto& child : grev[n]) {
        if(!visited[child]) {
          visited[child] = true;
          stack.push_back(child);
          res[child] += 1;
        }
      }
      for(const auto& child : g[n]) {
        if(!visited[child]) {
          stack.push_back(child);
          visited[child] = true;
          res[child] += 1;
        }
      }
    }
  }

  return res;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph g(n);
  for(int i=0; i<m; ++i) {
    int a, b;
    std::cin >> a >> b;
    g[a-1].push_back(b-1);
    g[b-1].push_back(a-1);
  }

  for(const auto x : dfs(g)) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  /*
  for(const auto x : dfs(reversed(g))) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
  */

  return 0;
}

